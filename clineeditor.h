#ifndef CLINEEDITOR_H
#define CLINEEDITOR_H

#include "cline.h"
#include "clinetablemodel.h"
#include "ftptools.h"
#include <QWidget>
#include <QTranslator>

class MainWindow;

namespace Ui {
class CLineEditor;
}

class CLineEditor : public QWidget
{
    Q_OBJECT
    
public:
    explicit CLineEditor(QWidget *parent = 0);
    ~CLineEditor();

protected:
    void closeEvent(QCloseEvent *event);
    
public slots:
    void addCLine();
    void removeCLine();
    void saveCLines();
    void loadCLines();
    void clearCLines();
    void ftpConnected();
    void ftpDisconnected();
    void fileDownloaded(QString path);
    void fileUploaded(QString path);
    void connectToFTP();    

    void setLangFr();
    void setLangDe();
    void setLangIt();
    void setLangEn();

private:
    void init();
    void enableOrDisableWidgets();
    void saveSettings();
    void loadSettings();
    void createCCcamFile();

    QTranslator *translator;
    MainWindow *w;
    bool connected;
    QString remoteFileName;
    QString remoteFilePath;
    FTPTools* ftp;
    CLineTableModel *model;
    Ui::CLineEditor *ui;

    static const QString CLINE_EDITOR_HEADER;

    static const QString FTP_SERVER_KEY;
    static const QString FTP_PORT_KEY;
    static const QString FTP_USERNAME_KEY;
    static const QString FTP_PASSWORD_KEY;
};

#endif // CLINEEDITOR_H
