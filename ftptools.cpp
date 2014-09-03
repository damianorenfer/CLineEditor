#include "ftptools.h"
#include <QDebug>
#include <QMessageBox>

FTPTools::FTPTools(QString address, int port, QString username, QString password, QObject *parent) : QObject(parent)
{
    this->address = address;
    this->port = port;
    this->username = username;
    this->password = password;

    downloadedFile = 0;
    ftp = new QFtp();
    connect(ftp, &QFtp::commandFinished, this, &FTPTools::commandFinished);
    connect(ftp, &QFtp::stateChanged, this, &FTPTools::stateChanged);
}

FTPTools::~FTPTools()
{        
    delete downloadedFile;
    delete ftp;
}

void FTPTools::connectToHost()
{
    ftp->setTransferMode(QFtp::Active);
    ftp->connectToHost(address, port);
    ftp->login(username, password);
}

void FTPTools::disconnectFromHost()
{
    ftp->close();
}

void FTPTools::downloadFile(QString src, QString dst)
{    
    downloadedFile = new QFile(dst);
    if(!downloadedFile->open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::critical(0,tr("Download fail"), tr("Failed to open : %1").arg(downloadedFile->fileName()));
        delete downloadedFile;
        downloadedFile = 0;
        return;
    }

    downloadQueue.enqueue(dst);
    ftp->get(src, downloadedFile);
}

void FTPTools::uploadFile(QString src, QString dst)
{
    uploadedFile = new QFile(src);
    if(!uploadedFile->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(0,tr("Upload fail"), tr("Failed to open : %1").arg(uploadedFile->fileName()));
        delete uploadedFile;
        uploadedFile = 0;
        return;
    }
    ftp->put(uploadedFile, dst);
    uploadQueue.enqueue(src);
}

void FTPTools::commandFinished(int id, bool error)
{
    if(ftp->currentCommand() == QFtp::Get)
    {        
        downloadedFile->close();
        delete downloadedFile;
        downloadedFile = 0;

        if(!error)
        {            
            QString dlFile = downloadQueue.dequeue();
            emit fileDownloaded(dlFile);
        }
        else
        {
            qDebug() << "error"<<ftp->errorString();
        }
    }
    else if(ftp->currentCommand() == QFtp::Put)
    {
        uploadedFile->close();
        delete uploadedFile;
        uploadedFile = 0;

        if(!error)
        {            
            QString ulFile = uploadQueue.dequeue();
            emit fileUploaded(ulFile);
        }
        else
        {
            qDebug() << "error"<<ftp->errorString();
        }
    }
}

void FTPTools::stateChanged(int state)
{
    if(state == QFtp::Connected) emit connected();
    else if(state == QFtp::Unconnected) emit disconnected();
}
