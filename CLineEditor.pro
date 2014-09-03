#-------------------------------------------------
#
# Project created by QtCreator 2013-07-03T11:48:49
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CLineEditor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cline.cpp \
    clinetablemodel.cpp \
    clineeditor.cpp \
    ftptools.cpp \
    clinefileparser.cpp \
    qftp/qurlinfo.cpp \
    qftp/qftp.cpp

HEADERS  += mainwindow.h \
    cline.h \
    clinetablemodel.h \
    clineeditor.h \
    ftptools.h \
    clinefileparser.h \
    qftp/qurlinfo.h \
    qftp/qftp.h

FORMS    += mainwindow.ui \
    clineeditor.ui

RESOURCES += \
    ressources.qrc

RC_FILE += "clineeditor.rc"

TRANSLATIONS = clineeditor_en.ts clineeditor_fr.ts clineeditor_de.ts clineeditor_it.ts
