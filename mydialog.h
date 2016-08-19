#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class MyDialog;
}

class MyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MyDialog(QWidget *parent = 0);
    ~MyDialog();

private:
    Ui::MyDialog *ui;

    bool validatePoint();
    bool validatePattern();

public slots:
    void accept();

signals:
    void DialogAccepted(QString, int);
};

#endif // MYDIALOG_H
