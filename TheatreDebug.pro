#-------------------------------------------------
#
# Project created by QtCreator 2016-02-18T12:20:22
#
#-------------------------------------------------

QT       += core gui widgets network
CONFIG += c++14

TARGET = TheatreDebug
TEMPLATE = app


SOURCES += main.cpp \
 TMainWindow.cpp \
 \
 request/TParams.cpp \
 request/TResponse.cpp \
 request/TRest.cpp \
 request/TUrl.cpp \
 \
 utils/TConfig.cpp \
 utils/TDB.cpp \
 utils/TDLogin.cpp \
 utils/TDump.cpp \
 utils/TJson.cpp \
 \
 widgets/TComboBox.cpp \
 widgets/TComboDialog.cpp \
 widgets/TTextDialog.cpp


HEADERS  += TMainWindow.h \
 \
 request/TParams.h \
 request/TResponse.h \
 request/TRest.h \
 request/TUrl.h \
 \
 utils/TConfig.h \
 utils/TDB.h \
 utils/TDLogin.h \
 utils/TDump.h \
 utils/TJson.h \
 \
 widgets/TComboBox.h \
 widgets/TComboDialog.h \
 widgets/TTextDialog.h

RESOURCES += res/res.qrc

# RC_FILE = res.rc
