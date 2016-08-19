#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    if(AppCore::getInstance() == nullptr)
    {
        QMessageBox::warning(this, "Error", "Core dosen't work");
        return;
    }

    Settings.loadSettings();

    Points = Settings.getPointsTypesList();
    for(const auto & ref : Points)
        ui->PointsComboBox->addItem(ref.first);

    Patterns = Settings.getPatternsList();
    ui->PatternComboBox->addItems(Patterns);

    ui->PatternComboBox->setCurrentText(Settings.getLastPattern());
    ui->PointsComboBox->setCurrentText(Settings.getLastPointsType().first);
    connect(ui->BeepButton, &QPushButton::clicked, [] (void) -> void{ qApp->beep();});

    connect(ui->RevievEditBox, &QPlainTextEdit::textChanged, [this] (void) -> void
    {
        this->ui->SaveButton->setEnabled( !this->ui->RevievEditBox->toPlainText().isEmpty()  && !this->ui->OutputPathBox->text().isEmpty() );
    });

    connect(ui->OutputPathBox, &QLineEdit::textChanged, [this] (void) -> void
    {
        this->ui->SaveButton->setEnabled( !this->ui->RevievEditBox->toPlainText().isEmpty()  && !this->ui->OutputPathBox->text().isEmpty() );
    });


}

MainWindow::~MainWindow()
{
    Settings.saveNewLastPattern(Patterns[ui->PatternComboBox->currentIndex()]),
    Settings.saveNewLastPoint(Points[ui->PointsComboBox->currentIndex()]);

    delete ui;
}

void MainWindow::onButtonOpenClick(void)
{
    InputPath = QFileDialog::getOpenFileName(this, "Choose file to open", QString(), "All files (*)");
    if( InputPath.isNull() )
        return;

    ui->OutputPathBox->setText(InputPath+".wsd");
    ui->InputPathBox->setText(InputPath);

    if( !AppCore::getInstance()->readFile(InputPath) )
    {
        QMessageBox::warning(this, "Error", "Cannot load file");
        return;
    }    

    InputText = AppCore::getInstance()->getLoadedData();
    ui->RevievEditBox->clear();
    ui->RevievEditBox->setPlainText(InputText.join('\n'));

}

void MainWindow::onButtonSaveClick(void)
{
   OutputPath = ui->OutputPathBox->text();
   QString Kerg;

   if(ui->KergCheckBox->isChecked())
       Kerg = ui->KergEdit->text();

   QStringList Output  = AppCore::getInstance()->convert(ui->RevievEditBox->toPlainText().split('\n'),
                                          Points[ui->PointsComboBox->currentIndex()],
                                          Patterns[ui->PatternComboBox->currentIndex()],
                                          Kerg
                                         );

   if( AppCore::getInstance()->writeFile(OutputPath, Output) )
   {
       QMessageBox::information(this, "Success", "File saved");
       ui->RevievEditBox->setPlainText(Output.join('\n'));
   }
   else
       QMessageBox::warning(this, "Error", "Cannot save file");

}


void MainWindow::onButtonDialog()
{
    MyDialog * Dialog = new MyDialog(this);
    connect(Dialog, &MyDialog::accepted, Dialog, &MyDialog::deleteLater); //potrzebe do wywalenia wskaznika
    connect(Dialog, &MyDialog::rejected, Dialog, &MyDialog::deleteLater); //potrzebne do wywalenia wskaznika
    connect(Dialog, &MyDialog::DialogAccepted, this, &MainWindow::onDialogAccept);
    Dialog->open();
}

void MainWindow::onDialogAccept(QString Str, int I)
{
    if(I==1)
    {
        QPair<QString,QString> Pair = Settings.stringToPoint(Str);
        Settings.saveNewPoint(Pair);
        Points.push_back(Pair);
        ui->PointsComboBox->addItem(Pair.first);
        ui->PointsComboBox->setCurrentIndex(ui->PointsComboBox->count()-1);
    }

    if(I==2)
    {
        Settings.saveNewPattern(Str);
        Patterns.push_back(Str);
        ui->PatternComboBox->addItem(Str);
        ui->PatternComboBox->setCurrentIndex(ui->PatternComboBox->count()-1);

    }

}

