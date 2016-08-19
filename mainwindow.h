#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "settingshandler.h"
#include "appcore.h"
#include "mydialog.h"
#include <QFileDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QString InputPath;
    QString OutputPath;
    QStringList InputText;
    QStringList Patterns;
    QList<QPair<QString, QString>> Points;
    SettingsHandler Settings;

public slots:
    void onButtonOpenClick(void);
    void onButtonSaveClick(void);
    void onButtonDialog(void);

    void onDialogAccept(QString Str, int I);

};

#endif // MAINWINDOW_H
