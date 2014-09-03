#include "clineeditor.h"
#include "ui_clineeditor.h"
#include "clinefileparser.h"
#include "mainwindow.h"
#include <QFileInfo>
#include <QInputDialog>
#include <QMessageBox>
#include <QSettings>

const QString CLineEditor::CLINE_EDITOR_HEADER = "#Added with CLine Editor";
const QString CLineEditor::FTP_SERVER_KEY   = "ftpServer";
const QString CLineEditor::FTP_PORT_KEY     = "ftpPort";
const QString CLineEditor::FTP_USERNAME_KEY = "ftpUsername";
const QString CLineEditor::FTP_PASSWORD_KEY = "ftpPassword";

CLineEditor::CLineEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CLineEditor)
{
    ui->setupUi(this);
    loadSettings();
    init();
}

CLineEditor::~CLineEditor()
{
    delete ui;
}

void CLineEditor::closeEvent(QCloseEvent *event)
{    
    saveSettings();
}

void CLineEditor::init()
{
    model = new CLineTableModel(this);
    ui->twCLines->setModel(model);
    ftp = 0;
    connected = false;

    w = dynamic_cast<MainWindow*>(parent());
    translator = new QTranslator(this);
}

void CLineEditor::enableOrDisableWidgets()
{
    ui->twCLines->setEnabled(connected);
    ui->btnAdd->setEnabled(connected);
    ui->btnRemove->setEnabled(connected);
    ui->btnClear->setEnabled(connected);
    ui->btnLoad->setEnabled(connected);

    if(connected)
    {
        ui->btnConnect->setText(tr("disconnect"));
    }
    else
    {
        ui->btnConnect->setText(tr("connect"));
        ui->btnSave->setEnabled(false);
    }
}

void CLineEditor::saveSettings()
{
    QSettings settings(QSettings::UserScope, "Damiano Renfer", "CLine Editor", this);
    settings.beginGroup("ftp");
    settings.setValue(FTP_SERVER_KEY, ui->leServerAddress->text());
    settings.setValue(FTP_PORT_KEY, ui->sbServerPort->value());
    settings.setValue(FTP_USERNAME_KEY, ui->leUsername->text());
    settings.setValue(FTP_PASSWORD_KEY, ui->lePassword->text());
    settings.endGroup();
}

void CLineEditor::loadSettings()
{
    QSettings settings(QSettings::UserScope, "Damiano Renfer", "CLine Editor", this);
    settings.beginGroup("ftp");
    ui->leServerAddress->setText(settings.value(FTP_SERVER_KEY, "DM800").toString());
    ui->sbServerPort->setValue(settings.value(FTP_PORT_KEY, 21).toInt());
    ui->leUsername->setText(settings.value(FTP_USERNAME_KEY, "root").toString());
    ui->lePassword->setText(settings.value(FTP_PASSWORD_KEY, "dreambox").toString());
    settings.endGroup();
}

void CLineEditor::createCCcamFile()
{
    QFile src(remoteFileName + ".bak");
    QFile dst(remoteFileName);
    if(!src.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(0,tr("Open fail"), tr("Failed to open : %1").arg(src.fileName()));
        return;
    }
    if(!dst.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::critical(0,tr("Open fail"), tr("Failed to open : %1").arg(dst.fileName()));
        return;
    }

    QTextStream out(&dst);

    while (!src.atEnd())
    {
        QString line = src.readLine().trimmed();
        CLine cline = CLineFileParser::parseCLine(line);

        if(cline.getServer().isEmpty() && line != CLINE_EDITOR_HEADER)
            out << line << "\n";
    }

    if(model->getClines().size() > 0)
        out << CLINE_EDITOR_HEADER << "\n";

    foreach (const CLine &cline, model->getClines())
        out << cline.toString() << "\n";


    src.close();
    dst.close();
}

void CLineEditor::addCLine()
{
    QString txt = QInputDialog::getText(this, tr("New CLine"), tr("Insert a CLine : \"C: server port user pass\"\nExample : \"C: server.org 12000 c9nypo abc123\""));

    if(txt != "")
    {
        CLine cline = CLineFileParser::parseCLine(txt);
        if(!cline.getServer().isEmpty())
            model->addCline(cline);
    }
}

void CLineEditor::removeCLine()
{
    QItemSelectionModel* selection = ui->twCLines->selectionModel();
    QModelIndexList rows = selection->selectedRows();

    foreach(const QModelIndex &index, rows)
    {        
        int row = index.row();
        model->removeRow(row, QModelIndex());
    }
}

void CLineEditor::saveCLines()
{
    ui->btnLoad->setEnabled(true);
    ui->btnSave->setEnabled(true);
    createCCcamFile();
    ftp->uploadFile(remoteFileName, remoteFilePath);
}

void CLineEditor::loadCLines()
{        
    model->clear();
    ui->btnLoad->setEnabled(false);
    ui->btnSave->setEnabled(false);
    remoteFilePath = ui->leFilePath->text();
    remoteFileName = QFileInfo(remoteFilePath).fileName();

    ftp->downloadFile(remoteFilePath, remoteFileName + ".bak");
}

void CLineEditor::clearCLines()
{
    model->clear();    
}

void CLineEditor::ftpConnected()
{
    connected = true;
    enableOrDisableWidgets();
    w->showMessageInStatusBar(tr("FTP connection successful"));
}

void CLineEditor::ftpDisconnected()
{
    connected = false;
    enableOrDisableWidgets();
    w->showMessageInStatusBar(tr("FTP disconnected"));
}

void CLineEditor::fileDownloaded(QString path)
{    
    ui->btnLoad->setEnabled(true);
    ui->btnSave->setEnabled(true);

    QList<CLine> listClines = CLineFileParser::getCLines(path);
    foreach(CLine cline, listClines)    
        model->addCline(cline);    

    w->showMessageInStatusBar(tr("Remote file downloaded : %1").arg(remoteFilePath));
}

void CLineEditor::fileUploaded(QString path)
{
    ui->btnLoad->setEnabled(true);
    ui->btnSave->setEnabled(true);

    w->showMessageInStatusBar(tr("Remote file uploaded : %1").arg(remoteFilePath));
}

void CLineEditor::connectToFTP()
{    
    if(connected)
    {
        ftp->disconnectFromHost();
        model->clear();
    }
    else
    {
        delete ftp;
        ftp = 0;
        QString server = ui->leServerAddress->text();
        QString username = ui->leUsername->text();
        QString password = ui->lePassword->text();
        int port = ui->sbServerPort->value();
        ftp = new FTPTools(server, port, username, password, this);
        ftp->connectToHost();
        connect(ftp, &FTPTools::connected, this, &CLineEditor::ftpConnected);
        connect(ftp, &FTPTools::disconnected, this, &CLineEditor::ftpDisconnected);
        connect(ftp, &FTPTools::fileDownloaded, this, &CLineEditor::fileDownloaded);
    }
}

void CLineEditor::setLangFr()
{
    saveSettings();
    translator->load(":/i18n/clineeditor_fr");
    qApp->installTranslator(translator);
    ui->retranslateUi(this);
    loadSettings();
}

void CLineEditor::setLangDe()
{
    saveSettings();
    translator->load(":/i18n/clineeditor_de");
    qApp->installTranslator(translator);
    ui->retranslateUi(this);
    loadSettings();
}

void CLineEditor::setLangIt()
{
    saveSettings();
    translator->load(":/i18n/clineeditor_it");
    qApp->installTranslator(translator);
    ui->retranslateUi(this);
    loadSettings();
}

void CLineEditor::setLangEn()
{
    saveSettings();
    translator->load(":/i18n/clineeditor_en");
    qApp->installTranslator(translator);
    ui->retranslateUi(this);
    loadSettings();
}
