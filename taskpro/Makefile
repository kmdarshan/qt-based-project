#############################################################################
# Makefile for building: taskpro
# Generated by qmake (2.01a) (Qt 4.7.3) on: Mon Jun 6 21:06:51 2011
# Project:  taskpro.pro
# Template: app
# Command: f:\qtsdk\symbian\sdks\symbian1qt473\bin\qmake.exe -spec ..\..\..\QtSDK\Symbian\SDKs\Symbian1Qt473\mkspecs\symbian-abld CONFIG+=release -after  OBJECTS_DIR=obj MOC_DIR=moc UI_DIR=ui RCC_DIR=rcc -o bld.inf taskpro.pro
#############################################################################

MAKEFILE          = Makefile
QMAKE             = f:\qtsdk\symbian\sdks\symbian1qt473\bin\qmake.exe
DEL_FILE          = del 2> NUL
DEL_DIR           = rmdir
MOVE              = move
CHK_DIR_EXISTS    = if not exist
MKDIR             = mkdir
XCOPY             = xcopy /d /f /h /r /y /i
ABLD              = ABLD.BAT
DEBUG_PLATFORMS   = winscw gcce armv5 armv6
RELEASE_PLATFORMS = gcce armv5 armv6
MAKE              = make

ifeq (WINS,$(findstring WINS, $(PLATFORM)))
ZDIR=$(EPOCROOT)epoc32\release\$(PLATFORM)\$(CFG)\z
else
ZDIR=$(EPOCROOT)epoc32\data\z
endif

DEFINES	 = -DSYMBIAN -DUNICODE -DQT_KEYPAD_NAVIGATION -DQT_SOFTKEYS_ENABLED -DQT_USE_MATH_H_FLOATS -DONE_PLUGIN_PATH="c:/resource/qt/plugins/oneplugin.qtplugin" -DQT_NO_DEBUG -DQT_WEBKIT_LIB -DQT_GUI_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB
INCPATH	 =  -I"F:/QtSDK/Symbian/SDKs/Symbian1Qt473/include/QtCore" -I"F:/QtSDK/Symbian/SDKs/Symbian1Qt473/include/QtCore/tmp" -I"F:/QtSDK/Symbian/SDKs/Symbian1Qt473/include/QtNetwork" -I"F:/QtSDK/Symbian/SDKs/Symbian1Qt473/include/QtNetwork/tmp" -I"F:/QtSDK/Symbian/SDKs/Symbian1Qt473/include/QtGui" -I"F:/QtSDK/Symbian/SDKs/Symbian1Qt473/include/QtGui/tmp" -I"F:/QtSDK/Symbian/SDKs/Symbian1Qt473/include/QtWebKit" -I"F:/QtSDK/Symbian/SDKs/Symbian1Qt473/include/QtWebKit/tmp" -I"F:/QtSDK/Symbian/SDKs/Symbian1Qt473/include" -I"F:/QtSDK/Symbian/SDKs/Symbian1Qt473/include/tmp" -I"F:/QtSDK/Symbian/SDKs/Symbian1Qt473/mkspecs/common/symbian" -I"F:/QtSDK/Symbian/SDKs/Symbian1Qt473/mkspecs/common/symbian/tmp" -I"F:/QtSDK/Symbian/SDKs/Symbian1Qt473/epoc32/include" -I"F:/QtSDK/Symbian/SDKs/Symbian1Qt473/epoc32/include/osextensions/stdapis" -I"F:/QtSDK/Symbian/SDKs/Symbian1Qt473/epoc32/include/osextensions/stdapis/sys" -I"F:/QtSDK/Symbian/SDKs/Symbian1Qt473/epoc32/include/stdapis" -I"F:/QtSDK/Symbian/SDKs/Symbian1Qt473/epoc32/include/stdapis/sys" -I"F:/QtSDK/Symbian/SDKs/Symbian1Qt473/epoc32/include/oem" -I"F:/QtSDK/Symbian/SDKs/Symbian1Qt473/epoc32/include/middleware" -I"F:/QtSDK/Symbian/SDKs/Symbian1Qt473/epoc32/include/domain/middleware" -I"F:/QtSDK/Symbian/SDKs/Symbian1Qt473/epoc32/include/osextensions" -I"F:/QtSDK/Symbian/SDKs/Symbian1Qt473/epoc32/include/domain/osextensions" -I"F:/QtSDK/Symbian/SDKs/Symbian1Qt473/epoc32/include/applications" -I"F:/QtSDK/Symbian/SDKs/Symbian1Qt473/epoc32/include/domain/applications" -I"F:/QtSDK/Symbian/SDKs/Symbian1Qt473/epoc32/include/domain/osextensions/loc" -I"F:/QtSDK/Symbian/SDKs/Symbian1Qt473/epoc32/include/domain/middleware/loc" -I"F:/QtSDK/Symbian/SDKs/Symbian1Qt473/epoc32/include/domain/applications/loc" -I"F:/QtSDK/Symbian/SDKs/Symbian1Qt473/epoc32/include/domain/osextensions/loc/sc" -I"F:/QtSDK/Symbian/SDKs/Symbian1Qt473/epoc32/include/domain/middleware/loc/sc" -I"F:/QtSDK/Symbian/SDKs/Symbian1Qt473/epoc32/include/domain/applications/loc/sc" -I"F:/QtSDK/Symbian/SDKs/Symbian1Qt473/epoc32/include/middleware/ovinotifications" -I"F:/QtSDK/Symbian/SDKs/Symbian1Qt473/epoc32/include/osextensions/stdapis/stlport" -I"F:/QtSDK/Symbian/SDKs/Symbian1Qt473/epoc32/include/stdapis/stlport" -I"F:/QtSDK/Symbian/SDKs/Symbian1Qt473/include/QtXmlPatterns" -I"F:/QtSDK/Symbian/SDKs/Symbian1Qt473/include/QtXmlPatterns/tmp" -I"F:/Projects/qt/taskpro/moc" -I"F:/Projects/qt/taskpro/moc/tmp" -I"F:/Projects/qt/taskpro/ui" -I"F:/Projects/qt/taskpro/ui/tmp" -I"F:/Projects/qt/taskpro" -I"F:/Projects/qt/taskpro/tmp" -I"F:/Projects/qt/taskpro/rcc" -I"F:/Projects/qt/taskpro/rcc/tmp"
first: default
default: debug-winscw
all: debug release

qmake:
	$(QMAKE) "F:/Projects/qt/taskpro/taskpro.pro"  -spec ..\..\..\QtSDK\Symbian\SDKs\Symbian1Qt473\mkspecs\symbian-abld CONFIG+=release -after  OBJECTS_DIR=obj MOC_DIR=moc UI_DIR=ui RCC_DIR=rcc

bld.inf: F:/Projects/qt/taskpro/taskpro.pro
	$(QMAKE) "F:/Projects/qt/taskpro/taskpro.pro"  -spec ..\..\..\QtSDK\Symbian\SDKs\Symbian1Qt473\mkspecs\symbian-abld CONFIG+=release -after  OBJECTS_DIR=obj MOC_DIR=moc UI_DIR=ui RCC_DIR=rcc

$(ABLD): bld.inf
	bldmake bldfiles

f:\Projects\qt\taskpro\taskpro.loc: 
	$(QMAKE) "F:/Projects/qt/taskpro/taskpro.pro"  -spec ..\..\..\QtSDK\Symbian\SDKs\Symbian1Qt473\mkspecs\symbian-abld CONFIG+=release -after  OBJECTS_DIR=obj MOC_DIR=moc UI_DIR=ui RCC_DIR=rcc

debug: f:\Projects\qt\taskpro\taskpro.loc $(ABLD)
	$(ABLD) build winscw udeb
	$(ABLD) build gcce udeb
	$(ABLD) build armv5 udeb
	$(ABLD) build armv6 udeb

release: f:\Projects\qt\taskpro\taskpro.loc $(ABLD)
	$(ABLD) build gcce urel
	$(ABLD) build armv5 urel
	$(ABLD) build armv6 urel

debug-winscw: f:\Projects\qt\taskpro\taskpro.loc $(ABLD)
	$(ABLD) build winscw udeb
debug-gcce: f:\Projects\qt\taskpro\taskpro.loc $(ABLD)
	$(ABLD) build gcce udeb
debug-armv5: f:\Projects\qt\taskpro\taskpro.loc $(ABLD)
	$(ABLD) build armv5 udeb
debug-armv6: f:\Projects\qt\taskpro\taskpro.loc $(ABLD)
	$(ABLD) build armv6 udeb
release-gcce: f:\Projects\qt\taskpro\taskpro.loc $(ABLD)
	$(ABLD) build gcce urel
release-armv5: f:\Projects\qt\taskpro\taskpro.loc $(ABLD)
	$(ABLD) build armv5 urel
release-armv6: f:\Projects\qt\taskpro\taskpro.loc $(ABLD)
	$(ABLD) build armv6 urel

export: $(ABLD)
	$(ABLD) export

cleanexport: $(ABLD)
	$(ABLD) cleanexport

check: first

${ZDIR}\resource\apps\taskpro.mif: icon_1.svg
	mifconv ${ZDIR}\resource\apps\taskpro.mif /c32 icon_1.svg

run:
	call /QtSDK/Symbian/SDKs/Symbian1Qt473/epoc32/release/winscw/udeb/taskpro.exe $(QT_RUN_OPTIONS)

runonphone: sis
	runonphone $(QT_RUN_ON_PHONE_OPTIONS) --sis taskpro.sis taskpro.exe $(QT_RUN_OPTIONS)

taskpro_template.pkg: F:/Projects/qt/taskpro/taskpro.pro
	$(MAKE) -f $(MAKEFILE) qmake

taskpro_installer.pkg: F:/Projects/qt/taskpro/taskpro.pro
	$(MAKE) -f $(MAKEFILE) qmake

taskpro_stub.pkg: F:/Projects/qt/taskpro/taskpro.pro
	$(MAKE) -f $(MAKEFILE) qmake

sis: taskpro_template.pkg
	$(if $(wildcard .make.cache), $(MAKE) -f $(MAKEFILE) ok_sis MAKEFILES=.make.cache , $(if $(QT_SIS_TARGET), $(MAKE) -f $(MAKEFILE) ok_sis , $(MAKE) -f $(MAKEFILE) fail_sis_nocache ) )

ok_sis:
	createpackage $(QT_SIS_OPTIONS) taskpro_template.pkg $(QT_SIS_TARGET) $(QT_SIS_CERTIFICATE) $(QT_SIS_KEY) $(QT_SIS_PASSPHRASE)

unsigned_sis: taskpro_template.pkg
	$(if $(wildcard .make.cache), $(MAKE) -f $(MAKEFILE) ok_unsigned_sis MAKEFILES=.make.cache , $(if $(QT_SIS_TARGET), $(MAKE) -f $(MAKEFILE) ok_unsigned_sis , $(MAKE) -f $(MAKEFILE) fail_sis_nocache ) )

ok_unsigned_sis:
	createpackage $(QT_SIS_OPTIONS) -o taskpro_template.pkg $(QT_SIS_TARGET)

taskpro.sis:
	$(MAKE) -f $(MAKEFILE) sis

installer_sis: taskpro_installer.pkg sis
	$(MAKE) -f $(MAKEFILE) ok_installer_sis

ok_installer_sis: taskpro_installer.pkg
	createpackage $(QT_SIS_OPTIONS) taskpro_installer.pkg - $(QT_SIS_CERTIFICATE) $(QT_SIS_KEY) $(QT_SIS_PASSPHRASE)

unsigned_installer_sis: taskpro_installer.pkg unsigned_sis
	$(MAKE) -f $(MAKEFILE) ok_unsigned_installer_sis

ok_unsigned_installer_sis: taskpro_installer.pkg
	createpackage $(QT_SIS_OPTIONS) -o taskpro_installer.pkg

fail_sis_nocache:
	$(error Project has to be built or QT_SIS_TARGET environment variable has to be set before calling 'SIS' target)

stub_sis: taskpro_stub.pkg
	$(if $(wildcard .make.cache), $(MAKE) -f $(MAKEFILE) ok_stub_sis MAKEFILES=.make.cache , $(if $(QT_SIS_TARGET), $(MAKE) -f $(MAKEFILE) ok_stub_sis , $(MAKE) -f $(MAKEFILE) fail_sis_nocache ) )

ok_stub_sis:
	createpackage -s $(QT_SIS_OPTIONS) taskpro_stub.pkg $(QT_SIS_TARGET) $(QT_SIS_CERTIFICATE) $(QT_SIS_KEY) $(QT_SIS_PASSPHRASE)

store_build:
	@echo # ============================================================================== > .make.cache && echo # This file is generated by make and should not be modified by the user >> .make.cache && echo # Name : .make.cache >> .make.cache && echo # Part of : lineedits >> .make.cache && echo # Description : This file is used to cache last build target for >> .make.cache && echo # make sis target. >> .make.cache && echo # Version : >> .make.cache && echo # >> .make.cache && echo # ============================================================================== >> .make.cache && echo QT_SIS_TARGET ?= $(QT_SIS_TARGET) >> .make.cache

deploy: sis
	call taskpro.sis

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc\moc_mainwindow.cpp moc\moc_finddialog.cpp moc\moc_errordialog.cpp moc\moc_emaildialog.cpp moc\moc_httpcommunicator.cpp moc\moc_httpcommunicator.cpp moc\moc_dialog.cpp moc\moc_synctabwidget.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc\moc_mainwindow.cpp moc\moc_finddialog.cpp moc\moc_errordialog.cpp moc\moc_emaildialog.cpp moc\moc_httpcommunicator.cpp moc\moc_httpcommunicator.cpp moc\moc_dialog.cpp moc\moc_synctabwidget.cpp
moc\moc_mainwindow.cpp: mainwindow.h
	F:\QtSDK\Symbian\SDKs\Symbian1Qt473\bin\moc.exe $(DEFINES) $(INCPATH) -DSYMBIAN mainwindow.h -o moc\moc_mainwindow.cpp

moc\moc_finddialog.cpp: finddialog.h
	F:\QtSDK\Symbian\SDKs\Symbian1Qt473\bin\moc.exe $(DEFINES) $(INCPATH) -DSYMBIAN finddialog.h -o moc\moc_finddialog.cpp

moc\moc_errordialog.cpp: errordialog.h
	F:\QtSDK\Symbian\SDKs\Symbian1Qt473\bin\moc.exe $(DEFINES) $(INCPATH) -DSYMBIAN errordialog.h -o moc\moc_errordialog.cpp

moc\moc_emaildialog.cpp: emaildialog.h
	F:\QtSDK\Symbian\SDKs\Symbian1Qt473\bin\moc.exe $(DEFINES) $(INCPATH) -DSYMBIAN emaildialog.h -o moc\moc_emaildialog.cpp

moc\moc_httpcommunicator.cpp: httpcommunicator.h
	F:\QtSDK\Symbian\SDKs\Symbian1Qt473\bin\moc.exe $(DEFINES) $(INCPATH) -DSYMBIAN httpcommunicator.h -o moc\moc_httpcommunicator.cpp

moc\moc_httpcommunicator.cpp: httpcommunicator.h
	F:\QtSDK\Symbian\SDKs\Symbian1Qt473\bin\moc.exe $(DEFINES) $(INCPATH) -DSYMBIAN httpcommunicator.h -o moc\moc_httpcommunicator.cpp

moc\moc_dialog.cpp: dialog.h
	F:\QtSDK\Symbian\SDKs\Symbian1Qt473\bin\moc.exe $(DEFINES) $(INCPATH) -DSYMBIAN dialog.h -o moc\moc_dialog.cpp

moc\moc_synctabwidget.cpp: synctabwidget.h
	F:\QtSDK\Symbian\SDKs\Symbian1Qt473\bin\moc.exe $(DEFINES) $(INCPATH) -DSYMBIAN synctabwidget.h -o moc\moc_synctabwidget.cpp

compiler_rcc_make_all: rcc\qrc_donelogo.cpp
compiler_rcc_clean:
	-$(DEL_FILE) rcc\qrc_donelogo.cpp
rcc\qrc_donelogo.cpp: donelogo.qrc \
		search.png \
		red.png \
		myappico.ico \
		Done.png \
		Incomplete.gif \
		clock.png
	f:\QtSDK\Symbian\SDKs\Symbian1Qt473\bin\rcc.exe -name donelogo donelogo.qrc -o rcc\qrc_donelogo.cpp

compiler_image_collection_make_all: ui\qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) ui\qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui\ui_mainwindow.h ui\ui_finddialog.h ui\ui_errordialog.h ui\ui_emaildialog.h ui\ui_dialog.h ui\ui_synctabwidget.h
compiler_uic_clean:
	-$(DEL_FILE) ui\ui_mainwindow.h ui\ui_finddialog.h ui\ui_errordialog.h ui\ui_emaildialog.h ui\ui_dialog.h ui\ui_synctabwidget.h
ui\ui_mainwindow.h: mainwindow.ui
	f:\QtSDK\Symbian\SDKs\Symbian1Qt473\bin\uic.exe mainwindow.ui -o ui\ui_mainwindow.h

ui\ui_finddialog.h: finddialog.ui
	f:\QtSDK\Symbian\SDKs\Symbian1Qt473\bin\uic.exe finddialog.ui -o ui\ui_finddialog.h

ui\ui_errordialog.h: errordialog.ui
	f:\QtSDK\Symbian\SDKs\Symbian1Qt473\bin\uic.exe errordialog.ui -o ui\ui_errordialog.h

ui\ui_emaildialog.h: emaildialog.ui
	f:\QtSDK\Symbian\SDKs\Symbian1Qt473\bin\uic.exe emaildialog.ui -o ui\ui_emaildialog.h

ui\ui_dialog.h: dialog.ui
	f:\QtSDK\Symbian\SDKs\Symbian1Qt473\bin\uic.exe dialog.ui -o ui\ui_dialog.h

ui\ui_synctabwidget.h: synctabwidget.ui
	f:\QtSDK\Symbian\SDKs\Symbian1Qt473\bin\uic.exe synctabwidget.ui -o ui\ui_synctabwidget.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_rcc_clean compiler_uic_clean 

create_temps:
	-@ if not exist "F:\QtSDK\Symbian\SDKs\Symbian1Qt473\include\QtCore\tmp" mkdir "F:\QtSDK\Symbian\SDKs\Symbian1Qt473\include\QtCore\tmp"
	-@ if not exist "F:\QtSDK\Symbian\SDKs\Symbian1Qt473\include\QtNetwork\tmp" mkdir "F:\QtSDK\Symbian\SDKs\Symbian1Qt473\include\QtNetwork\tmp"
	-@ if not exist "F:\QtSDK\Symbian\SDKs\Symbian1Qt473\include\QtGui\tmp" mkdir "F:\QtSDK\Symbian\SDKs\Symbian1Qt473\include\QtGui\tmp"
	-@ if not exist "F:\QtSDK\Symbian\SDKs\Symbian1Qt473\include\QtWebKit\tmp" mkdir "F:\QtSDK\Symbian\SDKs\Symbian1Qt473\include\QtWebKit\tmp"
	-@ if not exist "F:\QtSDK\Symbian\SDKs\Symbian1Qt473\include\tmp" mkdir "F:\QtSDK\Symbian\SDKs\Symbian1Qt473\include\tmp"
	-@ if not exist "F:\QtSDK\Symbian\SDKs\Symbian1Qt473\mkspecs\common\symbian\tmp" mkdir "F:\QtSDK\Symbian\SDKs\Symbian1Qt473\mkspecs\common\symbian\tmp"
	-@ if not exist "F:\QtSDK\Symbian\SDKs\Symbian1Qt473\include\QtXmlPatterns\tmp" mkdir "F:\QtSDK\Symbian\SDKs\Symbian1Qt473\include\QtXmlPatterns\tmp"
	-@ if not exist "F:\Projects\qt\taskpro\moc\tmp" mkdir "F:\Projects\qt\taskpro\moc\tmp"
	-@ if not exist "F:\Projects\qt\taskpro\ui\tmp" mkdir "F:\Projects\qt\taskpro\ui\tmp"
	-@ if not exist "F:\Projects\qt\taskpro\tmp" mkdir "F:\Projects\qt\taskpro\tmp"
	-@ if not exist "F:\Projects\qt\taskpro\rcc\tmp" mkdir "F:\Projects\qt\taskpro\rcc\tmp"

extension_clean: compiler_clean
	-@ if EXIST "F:\QtSDK\Symbian\SDKs\Symbian1Qt473\include\QtCore\tmp" rmdir /s /q  "F:\QtSDK\Symbian\SDKs\Symbian1Qt473\include\QtCore\tmp"
	-@ if EXIST "F:\QtSDK\Symbian\SDKs\Symbian1Qt473\include\QtNetwork\tmp" rmdir /s /q  "F:\QtSDK\Symbian\SDKs\Symbian1Qt473\include\QtNetwork\tmp"
	-@ if EXIST "F:\QtSDK\Symbian\SDKs\Symbian1Qt473\include\QtGui\tmp" rmdir /s /q  "F:\QtSDK\Symbian\SDKs\Symbian1Qt473\include\QtGui\tmp"
	-@ if EXIST "F:\QtSDK\Symbian\SDKs\Symbian1Qt473\include\QtWebKit\tmp" rmdir /s /q  "F:\QtSDK\Symbian\SDKs\Symbian1Qt473\include\QtWebKit\tmp"
	-@ if EXIST "F:\QtSDK\Symbian\SDKs\Symbian1Qt473\include\tmp" rmdir /s /q  "F:\QtSDK\Symbian\SDKs\Symbian1Qt473\include\tmp"
	-@ if EXIST "F:\QtSDK\Symbian\SDKs\Symbian1Qt473\mkspecs\common\symbian\tmp" rmdir /s /q  "F:\QtSDK\Symbian\SDKs\Symbian1Qt473\mkspecs\common\symbian\tmp"
	-@ if EXIST "F:\QtSDK\Symbian\SDKs\Symbian1Qt473\include\QtXmlPatterns\tmp" rmdir /s /q  "F:\QtSDK\Symbian\SDKs\Symbian1Qt473\include\QtXmlPatterns\tmp"
	-@ if EXIST "F:\Projects\qt\taskpro\moc\tmp" rmdir /s /q  "F:\Projects\qt\taskpro\moc\tmp"
	-@ if EXIST "F:\Projects\qt\taskpro\ui\tmp" rmdir /s /q  "F:\Projects\qt\taskpro\ui\tmp"
	-@ if EXIST "F:\Projects\qt\taskpro\tmp" rmdir /s /q  "F:\Projects\qt\taskpro\tmp"
	-@ if EXIST "F:\Projects\qt\taskpro\rcc\tmp" rmdir /s /q  "F:\Projects\qt\taskpro\rcc\tmp"

pre_targetdeps: \
	generated_sources \
	all_source_deps \
	${ZDIR}\resource\apps\taskpro.mif \
	ui\ui_mainwindow.h \
	ui\ui_finddialog.h \
	ui\ui_errordialog.h \
	ui\ui_emaildialog.h \
	ui\ui_dialog.h \
	ui\ui_synctabwidget.h

generated_sources: \
	moc\moc_mainwindow.cpp \
	moc\moc_finddialog.cpp \
	moc\moc_errordialog.cpp \
	moc\moc_emaildialog.cpp \
	moc\moc_httpcommunicator.cpp \
	moc\moc_dialog.cpp \
	moc\moc_synctabwidget.cpp \
	rcc\qrc_donelogo.cpp

all_source_deps: \
	mainwindow.h \
	ui\ui_mainwindow.h \
	finddialog.h \
	dialog.h \
	httpcommunicator.h \
	MainWindow.h \
	emaildialog.h \
	ui\ui_finddialog.h \
	errordialog.h \
	ui\ui_errordialog.h \
	ui\ui_emaildialog.h \
	ui\ui_dialog.h \
	synctabwidget.h \
	ui\ui_synctabwidget.h

finalize:

winscw_deployment:

winscw_deployment_clean:

deployment:

deployment_clean:

dodistclean:
	-@ if EXIST "f:\Projects\qt\taskpro\taskpro_template.pkg" $(DEL_FILE)  "f:\Projects\qt\taskpro\taskpro_template.pkg"
	-@ if EXIST "f:\Projects\qt\taskpro\taskpro_stub.pkg" $(DEL_FILE)  "f:\Projects\qt\taskpro\taskpro_stub.pkg"
	-@ if EXIST "f:\Projects\qt\taskpro\taskpro_installer.pkg" $(DEL_FILE)  "f:\Projects\qt\taskpro\taskpro_installer.pkg"
	-@ if EXIST "f:\Projects\qt\taskpro\Makefile" $(DEL_FILE)  "f:\Projects\qt\taskpro\Makefile"
	-@ if EXIST "f:\Projects\qt\taskpro\Makefile_taskpro_exe.mk" $(DEL_FILE)  "f:\Projects\qt\taskpro\Makefile_taskpro_exe.mk"
	-@ if EXIST "f:\Projects\qt\taskpro\taskpro_exe.mmp" $(DEL_FILE)  "f:\Projects\qt\taskpro\taskpro_exe.mmp"
	-@ if EXIST "f:\Projects\qt\taskpro\taskpro_reg.rss" $(DEL_FILE)  "f:\Projects\qt\taskpro\taskpro_reg.rss"
	-@ if EXIST "f:\Projects\qt\taskpro\taskpro.rss" $(DEL_FILE)  "f:\Projects\qt\taskpro\taskpro.rss"
	-@ if EXIST "f:\Projects\qt\taskpro\taskpro.loc" $(DEL_FILE)  "f:\Projects\qt\taskpro\taskpro.loc"
	-@ if EXIST "f:\Projects\qt\taskpro\bld.inf" $(DEL_FILE)  "f:\Projects\qt\taskpro\bld.inf"
	-@ if EXIST "f:\Projects\qt\taskpro\${ZDIR}\resource\apps\taskpro.mif" $(DEL_FILE)  "f:\Projects\qt\taskpro\${ZDIR}\resource\apps\taskpro.mif"

distclean: clean dodistclean

clean: $(ABLD)
	-$(ABLD) reallyclean
	-bldmake clean

clean-debug: $(ABLD)
	$(ABLD) reallyclean winscw udeb
	$(ABLD) reallyclean gcce udeb
	$(ABLD) reallyclean armv5 udeb
	$(ABLD) reallyclean armv6 udeb

clean-release: $(ABLD)
	$(ABLD) reallyclean gcce urel
	$(ABLD) reallyclean armv5 urel
	$(ABLD) reallyclean armv6 urel

clean-debug-winscw: $(ABLD)
	$(ABLD) reallyclean winscw udeb
clean-debug-gcce: $(ABLD)
	$(ABLD) reallyclean gcce udeb
clean-debug-armv5: $(ABLD)
	$(ABLD) reallyclean armv5 udeb
clean-debug-armv6: $(ABLD)
	$(ABLD) reallyclean armv6 udeb
clean-release-gcce: $(ABLD)
	$(ABLD) reallyclean gcce urel
clean-release-armv5: $(ABLD)
	$(ABLD) reallyclean armv5 urel
clean-release-armv6: $(ABLD)
	$(ABLD) reallyclean armv6 urel

freeze: $(ABLD)
	$(ABLD) freeze

freeze-debug: freeze

freeze-release: freeze

freeze-debug-winscw: $(ABLD)
	$(ABLD) freeze winscw
freeze-debug-gcce: $(ABLD)
	$(ABLD) freeze gcce
freeze-debug-armv5: $(ABLD)
	$(ABLD) freeze armv5
freeze-debug-armv6: $(ABLD)
	$(ABLD) freeze armv6
freeze-release-gcce: $(ABLD)
	$(ABLD) freeze gcce
freeze-release-armv5: $(ABLD)
	$(ABLD) freeze armv5
freeze-release-armv6: $(ABLD)
	$(ABLD) freeze armv6

