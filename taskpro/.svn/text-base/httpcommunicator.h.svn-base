#ifndef HTTPCOMMUNICATOR_H
#define HTTPCOMMUNICATOR_H

#include <QObject>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QTimer>
class QNetworkReply;
class QNetworkRequest;
class QIODevice;
class QFile;
//for re connecting again and again to the network
static int m_connectCount;
static QString m_connecturl;

class HttpCommunicator : public QObject
{
  Q_OBJECT
public:
  typedef enum {
    HttpRequestTypeGet,
    HttpRequestTypePost,
    HttpRequestTypeDelete,
    HttpRequestTypePut,
    HttpRequestTypeHead
  }HttpRequestType;
  HttpCommunicator(HttpRequestType requestType, const QString url,
             const QByteArray postData,
             QList<QPair<QByteArray, QByteArray> > customHeaders,
             bool saveResponseToFile);
  HttpCommunicator(HttpRequestType requestType, const QString url,
             QIODevice* postData,
             QList<QPair<QByteArray, QByteArray> > customHeaders,
             bool saveResponseToFile);
  ~HttpCommunicator();
  void makeRequest();
  const QNetworkReply* networkReply() const;
  const QString networkReplyBody() const;
  static void textForHttpRequestType(int requestType, QString& text);
  static HttpRequestType httpRequestTypeForText(const QString& text);
  int downloadProgress() const;
  int uploadProgress() const;
  static bool splitIntoHeaders(const QString& linearHeader,
                               QList<QPair<QByteArray, QByteArray> >& headerList);
  static QString saveFileName(const QUrl &url);
    QTimer* connectTimer;
  void setBackupvariable(QString qstr);
  QString getBackupvariable();
signals:
  void finishedRequest();
private slots:
  virtual void finishedSlot(QNetworkReply* reply);
  virtual void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
  virtual void uploadProgress(qint64 bytesSent, qint64 bytesTotal);
  virtual void downloadReadyRead();
  virtual void construct2();
private:
  void construct(const QString url);
  void appendHeaders();
  QFile* prepareFile(const QString& fileName) const;
  bool saveToFile(QByteArray bytes);
  static void encodeQueryItems(QUrl& url);
private:
  QNetworkAccessManager m_networkAccessManager;
  QNetworkRequest* m_networkRequest;
  QNetworkReply* m_networkReply;
  const HttpRequestType m_requestType;
  QUrl m_url;
  QString m_networkReplyBody;
  QIODevice* m_postData;
  QList<QPair<QByteArray, QByteArray> > m_customHeaders;
  int m_downloadProgress;
  int m_uploadProgress;
  bool m_saveResponseToFile;
  QFile* m_outputFile;
  QString m_backupHelper;
};

#endif // HTTPCOMMUNICATOR_H
