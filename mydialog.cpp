#include "mydialog.h"
#include "ui_mydialog.h"

MyDialog::MyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyDialog)
{
    ui->setupUi(this);
}

MyDialog::~MyDialog()
{
    delete ui;
}

void MyDialog::accept()
{
    bool BPooint;
    bool BPattern;

    if( BPooint = validatePoint() && ui->PointRadio->isChecked())
        emit DialogAccepted(ui->EditBox->text(), 1);
    if( BPattern = validatePattern() && ui->PatternRadio->isChecked())
        emit DialogAccepted(ui->EditBox->text(), 2);

    if(BPooint || BPattern)
        QDialog::accept();
    else
        QMessageBox::warning(this, "Error", "Invalid format");
}

bool MyDialog::validatePoint()
{
    QRegExp RegExp("\w*, .*");

    return RegExp.indexIn(ui->EditBox->text()) != -1;
}

bool MyDialog::validatePattern()
{
    return !( ui->EditBox->text().isEmpty() || ui->EditBox->text().contains(' ') );
}
