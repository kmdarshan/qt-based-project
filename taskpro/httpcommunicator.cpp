#include "httpcommunicator.h"

#include <QCryptographicHash>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QStringList>
#include <QBuffer>
#include <QDesktopServices>
#include <QFileInfo>
#include <QDir>
#include <QMessageBox>
#include "QDebug"
const QString headerSep(":");

HttpCommunicator::HttpCommunicator(HttpRequestType requestType, const QString url,
                                   const QByteArray postData,
                                   QList<QPair<QByteArray, QByteArray> > customHeaders,
                                   bool saveResponseToFile) :
m_networkAccessManager(this), m_networkRequest(NULL),m_networkReply(NULL),
m_requestType(requestType), m_customHeaders(customHeaders),
m_downloadProgress(0), m_uploadProgress(0),
m_saveResponseToFile(saveResponseToFile), m_outputFile(NULL)
{
  QBuffer* buffer = new QBuffer(this);
  buffer->setData(postData);
  m_postData = buffer;
  construct(url);
}

HttpCommunicator::HttpCommunicator(HttpRequestType requestType, const QString url,
                                   QIODevice* postData,
                                   QList<QPair<QByteArray, QByteArray> > customHeaders,
                                   bool saveResponseToFile) :
m_networkAccessManager(this), m_networkRequest(NULL),m_networkReply(NULL),
m_requestType(requestType), m_postData(postData), m_customHeaders(customHeaders),
m_downloadProgress(0), m_uploadProgress(0),
m_saveResponseToFile(saveResponseToFile), m_outputFile(NULL)
{
  //qDebug()<<"Construst url"<<url;
  construct(url);
}

void HttpCommunicator::construct(const QString url) {

    //qDebug()<<"Inside construcotr "<<m_connectCount;
    connectTimer = new QTimer(this);
    m_connecturl=url;
    m_connectCount=0;
    m_backupHelper="";
  QObject::connect(&m_networkAccessManager, SIGNAL(finished(QNetworkReply*)),
                   this, SLOT(finishedSlot(QNetworkReply*)));
  //qDebug()<<"Construct "<<url;
  m_url.setUrl(url, QUrl::StrictMode);
  encodeQueryItems(m_url);
}

void HttpCommunicator::construct2() {

  QObject::connect(&m_networkAccessManager, SIGNAL(finished(QNetworkReply*)),
                   this, SLOT(finishedSlot(QNetworkReply*)));
  //qDebug()<<"Construct 2 "<<m_connecturl;
  //qDebug()<<"Inside construcotr 2 "<<m_connectCount;
  m_url.setUrl(m_connecturl, QUrl::StrictMode);
  encodeQueryItems(m_url);
  if(m_connectCount < 4)
  {
      m_connectCount=m_connectCount+1;
      //qDebug()<<"Increased timer"<<m_connectCount;
  }else
  {
      connectTimer->stop();
      QMessageBox msgBox;
          msgBox.setText("Sorry!! Network error try again");
          msgBox.setStandardButtons(QMessageBox::Ok);
          msgBox.exec();
  }
}

HttpCommunicator::~HttpCommunicator() {
  delete m_networkRequest;
  m_networkRequest = NULL;
  if (m_networkReply != NULL) {
    m_networkReply->deleteLater();
    m_networkReply = NULL;
  }
  delete m_postData;
  if (m_outputFile) {
    m_outputFile->close();
    delete m_outputFile;
    m_outputFile = NULL;
  }
}


HttpCommunicator::HttpRequestType HttpCommunicator::httpRequestTypeForText(
    const QString& text)
{
  HttpCommunicator::HttpRequestType httpRequestType = HttpCommunicator::HttpRequestTypeGet;
  if (text == QString("GET")) {
    httpRequestType = HttpCommunicator::HttpRequestTypeGet;
  }
  else if (text == QString("DELETE")) {
    httpRequestType = HttpCommunicator::HttpRequestTypeDelete;
  }
  else if (text == QString("POST")) {
    httpRequestType = HttpCommunicator::HttpRequestTypePost;
  }
  else if (text == QString("PUT")) {
    httpRequestType = HttpCommunicator::HttpRequestTypePut;
  }
  else if (text == QString("HEAD")) {
    httpRequestType = HttpCommunicator::HttpRequestTypeHead;
  }
  else {
    Q_ASSERT(false);
  }
  return httpRequestType;
}

void HttpCommunicator::textForHttpRequestType(int requestType,
                                              QString& text)
{
  switch (requestType) {
  case HttpRequestTypeGet:
    text.append("GET");
    break;
  case HttpRequestTypePost:
    text.append("POST");
    break;
  case HttpRequestTypeDelete:
    text.append("DELETE");
    break;
  case HttpRequestTypePut:
    text.append("PUT");
    break;
  case HttpRequestTypeHead:
    text.append("HEAD");
    break;
  default:
    Q_ASSERT(false);
    text.append("GET");
    break;
  }
}

void HttpCommunicator::appendHeaders() {
  //  m_networkRequest->setRawHeader("Accept-Encoding", "application/x-www-form-urlencoded");
  //  m_networkRequest->setRawHeader("User-Agent", "MyOwnBrowser 1.0");
  for (int i = 0; i < m_customHeaders.count(); i++) {
    const QPair<QByteArray, QByteArray> headerPair = m_customHeaders[i];
    m_networkRequest->setRawHeader(headerPair.first, headerPair.second);
  }
}

void HttpCommunicator::makeRequest()
{
  m_downloadProgress = 0;
  m_uploadProgress = 0;
  if (m_networkRequest != NULL) {
    delete m_networkRequest;
    m_networkRequest = NULL;
  }

  if (m_networkRequest == NULL) {
    if (m_networkReply != NULL) {
      m_networkReply->deleteLater();
      m_networkReply = NULL;
    }
    m_networkReplyBody = "";
    m_networkRequest = new QNetworkRequest;
    m_networkRequest->setUrl(m_url);
    appendHeaders();
    if (m_requestType == HttpRequestTypeGet) {
      m_networkReply = m_networkAccessManager.get(*m_networkRequest);
    }
    else if (m_requestType == HttpRequestTypePost){
      m_networkReply = m_networkAccessManager.post(*m_networkRequest, m_postData);
    }
    else if (m_requestType == HttpRequestTypeDelete) {
      m_networkReply = m_networkAccessManager.deleteResource(*m_networkRequest);
    }
    else if (m_requestType == HttpRequestTypePut) {
      m_networkReply = m_networkAccessManager.put(*m_networkRequest, m_postData);
    }
    else if (m_requestType == HttpRequestTypeHead) {
      m_networkReply = m_networkAccessManager.head(*m_networkRequest);
    }
    else {
      Q_ASSERT(false);
    }
    QObject::connect(m_networkReply, SIGNAL(downloadProgress(qint64,qint64)), this,
                     SLOT(downloadProgress(qint64,qint64)));
    QObject::connect(m_networkReply, SIGNAL(readyRead()), this,
                     SLOT(downloadReadyRead()));
    QNetworkReply::NetworkError networkError = m_networkReply->error();
    networkError = networkError;
    // NOTE: Store QNetworkReply pointer (maybe into caller).
    // When this HTTP request is finished you will receive this same
    // QNetworkReply as response parameter.
    // By the QNetworkReply pointer you can identify request and response.
  }
}

void HttpCommunicator::downloadReadyRead()
{
  QByteArray bytes = m_networkReply->readAll();  // bytes
  m_networkReplyBody = m_networkReplyBody + bytes; // string
  if (m_saveResponseToFile) {
    QString location = saveFileName(m_url);
    if (saveToFile(bytes)) {
      m_networkReplyBody = tr("File saved at ") + location;
    }
    else {
      m_networkReplyBody = tr("Write Error ") + location;
    }
  }
}

void HttpCommunicator::finishedSlot(QNetworkReply* reply) {
    //qDebug()<<"Communicator finished slot";
  // We receive ownership of the reply object
  // and therefore need to handle deletion.
  Q_ASSERT(m_networkReply == reply);
  // Reading attributes of the reply
  // e.g. the HTTP status code
  QVariant statusCodeV =
      reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
  // Or the target URL if it was a redirect:
  QVariant redirectionTargetUrl =
      reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
  // see CS001432 on how to handle this

  QNetworkReply::NetworkError error = reply->error();
  // no error received?
  if (error == QNetworkReply::NoError) {
  }
  // Some http error received
  else {
    connect(connectTimer, SIGNAL(timeout()), this, SLOT(construct2()));
        connectTimer->start(1000);
        m_connectCount=m_connectCount+1;

    // handle errors here
      //qDebug()<<"Error here finished slot";

  }
  emit finishedRequest();
  delete m_postData;
  m_postData = NULL;
  if (m_outputFile) {
    m_outputFile->close();
    delete m_outputFile;
    m_outputFile = NULL;
  }
}

bool HttpCommunicator::saveToFile(QByteArray bytes)
{
  if (m_outputFile == NULL) {
    QString location = saveFileName(m_url);
    m_outputFile = new QFile(location);
    if (!m_outputFile->open(QIODevice::Append)) {
      delete m_outputFile;
      m_outputFile = NULL;
      return false;
    }
  }
  if (m_outputFile) {
    m_outputFile->write(bytes);
  }
  return true;
}

const QNetworkReply* HttpCommunicator::networkReply() const {
  return m_networkReply;
}

const QString HttpCommunicator::networkReplyBody() const {
  return m_networkReplyBody;
}

void HttpCommunicator::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
  if (bytesTotal > 0) {
    m_downloadProgress = 100 * bytesReceived/ bytesTotal;
  }
  else {
    m_downloadProgress = 0;
  }
}

int HttpCommunicator::downloadProgress() const
{
  return m_downloadProgress;
}

void HttpCommunicator::uploadProgress(qint64 bytesSent, qint64 bytesTotal)
{
  if (bytesTotal > 0) {
    m_uploadProgress = 100 * bytesSent/ bytesTotal;
  }
  else {
    m_uploadProgress = 0;
  }
}

int HttpCommunicator::uploadProgress() const
{
  return m_uploadProgress;
}

bool HttpCommunicator::splitIntoHeaders(const QString& linearHeader,
                                        QList<QPair<QByteArray, QByteArray> >& headerList)
{
    //qDebug()<<"Linear Header"<<linearHeader;
  // linearHeader = "Content-Range=0-100/200\nAccept-Encoding=gzip, deflate\nContent-Type=image/png"
  if (linearHeader.length() > 0) {
    QStringList stickyHdrList = linearHeader.split("\n");
    for (int i = 0; i < stickyHdrList.count(); i++) {
      QString stickyHdr = stickyHdrList[i].trimmed();
      if (stickyHdr.length() > 0) {
        QStringList headerValue = stickyHdr.trimmed().split(headerSep);
        if (headerValue.first().length() > 0) {
          if (headerValue.count() != 2) {
            return false;
          }
          else {
            QPair<QByteArray, QByteArray> headerValuePair(headerValue[0].toAscii(),
                                                          headerValue[1].toAscii());
            headerList.append(headerValuePair);
          }
        }
      }
    }
  }
  return true;
}

QString HttpCommunicator::saveFileName(const QUrl &url)
{
  QString path = url.path();
  QString dataLoc = QDesktopServices::storageLocation(
      QDesktopServices::DesktopLocation);
  QString basename = dataLoc + QDir::separator() + QFileInfo(path).fileName();

  if (basename.isEmpty())
    basename = "download";

  if (QFile::exists(basename)) {
    // already exists, don't overwrite
    int i = 0;
    basename += '.';
    while (QFile::exists(basename + QString::number(i)))
      ++i;

    basename += QString::number(i);
  }

  return basename;
}

void HttpCommunicator::encodeQueryItems(QUrl& url) {
  QList<QPair<QString, QString> > queryList = url.queryItems();
  for (int i = 0; i  < queryList.count(); i++) {
    QPair<QString, QString> pair = queryList[i];
    QByteArray leftEncoded = QUrl::toPercentEncoding(pair.first);
    QByteArray rightEncoded = QUrl::toPercentEncoding(pair.second);
    url.removeQueryItem(pair.first);
    url.addEncodedQueryItem(leftEncoded, rightEncoded);
  }
  //qDebug()<<"encode "<<url;
}

void HttpCommunicator::setBackupvariable(QString qstr)
{
    m_backupHelper=qstr;
}

QString HttpCommunicator::getBackupvariable()
{
    return m_backupHelper;
}

