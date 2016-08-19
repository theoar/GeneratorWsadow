#include "mainwindow.h"
#include <QApplication>
#include "settingshandler.h"
#include <QDebug>
#include <appcore.h>

int main(int argc, char *argv[])
{
    AppCore Core;
    QApplication a(argc, argv);

    if ( a.arguments().size() > 1 )
    {
        SettingsHandler S;
        S.loadSettings();

        QString Path = a.arguments().at(1);

        if( !Core.readFile(a.arguments().at(1)) )
        {
            qCritical() << "Cannot read file";
            return -1;
        }

        QStringList List = Core.convert(Core.getLoadedData(), S.getLastPointsType(), S.getLastPattern(), QString());
        if ( !Core.writeFile(Path+".wsd", List) )
        {
            qCritical() << "Cannot write file";
            return -1;
        }

        qDebug() << "Job done";

        return 0;
    }

    MainWindow w;
    w.show();

    return a.exec();
}
