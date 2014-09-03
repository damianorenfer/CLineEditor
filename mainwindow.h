#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "cline.h"
#include "clinetablemodel.h"
#include "clineeditor.h"
#include <QtWidgets>
#include <QList>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void showMessageInStatusBar(QString txt);
    void clearStatusBar();    

protected:
    void closeEvent(QCloseEvent *event);
    void createLangButtons();
    
private:    
    CLineEditor *editor;

    QPushButton *btnFrench;
    QPushButton *btnEnglish;
    QPushButton *btnItalian;
    QPushButton *btnGerman;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
