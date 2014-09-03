#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ftptools.h"
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{    
    ui->setupUi(this);
    editor = new CLineEditor(this);
    setCentralWidget(editor);
    createLangButtons();
    setWindowIcon(QIcon(":/icons/cle.png"));
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showMessageInStatusBar(QString txt)
{
    ui->statusBar->showMessage(txt);
    QTimer::singleShot(3000, this, SLOT(clearStatusBar()));
}

void MainWindow::clearStatusBar()
{
    ui->statusBar->clearMessage();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    editor->close();
}

void MainWindow::createLangButtons()
{
    QIcon fr(":/icons/fr.png");
    QIcon de(":/icons/de.png");
    QIcon it(":/icons/it.png");
    QIcon gb(":/icons/gb.png");

    btnFrench = new QPushButton(fr,"");
    btnGerman = new QPushButton(de,"");
    btnItalian = new QPushButton(it,"");
    btnEnglish = new QPushButton(gb,"");

    btnFrench->setFixedSize(fr.actualSize(QSize(100,100)));
    btnGerman->setFixedSize(de.actualSize(QSize(100,100)));
    btnItalian->setFixedSize(it.actualSize(QSize(100,100)));
    btnEnglish->setFixedSize(gb.actualSize(QSize(100,100)));

    ui->statusBar->addPermanentWidget(btnEnglish);
    ui->statusBar->addPermanentWidget(btnFrench);
  //ui->statusBar->addPermanentWidget(btnItalian);
  //ui->statusBar->addPermanentWidget(btnGerman);

    connect(btnFrench, &QPushButton::clicked, editor, &CLineEditor::setLangFr);
    connect(btnEnglish, &QPushButton::clicked, editor, &CLineEditor::setLangEn);
}
