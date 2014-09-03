#ifndef FTPTOOLS_H
#define FTPTOOLS_H

#include "qftp/qftp.h"
#include <QFile>
#include <QString>
#include <QThread>
#include <QQueue>

class FTPTools : public QObject
{
    Q_OBJECT
public:
    FTPTools(QString address, int port, QString username, QString password, QObject *parent);
    virtual ~FTPTools();    
    void connectToHost();
    void disconnectFromHost();
    void downloadFile(QString src, QString dst);
    void uploadFile(QString src, QString dst);

public slots:
    void commandFinished(int id, bool error);
    void stateChanged(int state);

signals:
    void connected();
    void disconnected();
    void fileDownloaded(QString path);
    void fileUploaded(QString path);

private:
    QString address;
    QString username;
    QString password;
    int port;

    QQueue<QString> downloadQueue;
    QQueue<QString> uploadQueue;
    QFile *downloadedFile;
    QFile *uploadedFile;
    QFtp *ftp;
};

#endif // FTPTOOLS_H
