#include "settingshandler.h"

const QStringList SettingsHandler::DefaultPatternsList =
{ "_NUMBER;_X;_Y;_H",
  "_NUMBER;_Y;_X;_H"
};

const QList<QPair<QString, QString>> SettingsHandler::DefaultPointsTypes =
{
    { "GSPINN", "Punkty sytuacyjne" },
    { "GEPINN", "Punkty ewidencyjne"}
};


SettingsHandler::SettingsHandler(void) :
    QObject(nullptr)
{

}

void SettingsHandler::loadPointsTypes()
{
    QFile File("points_types.ini");
    QTextStream Stream(&File);    

    if( !File.open(QFile::ReadOnly | QFile::Text) )
    {
        PointsTypesList = DefaultPointsTypes;

        if(File.open(QFile::WriteOnly | QFile::Text))
        {

            if( !PointsTypesList.contains(LastPointsType) )
                PointsTypesList.push_back(LastPointsType);

            for(const auto & ref : PointsTypesList)
            {

                Stream << ref.first;
                Stream << ", ";
                Stream << ref.second;
                Stream << '\n';
            }           

            File.close();
        }

        return;
    }

    bool Bool;
    QString Line;
    while( !Stream.atEnd() )
    {
        Line = Stream.readLine();
        QPair<QString,QString> Point = stringToPoint(Line, &Bool);
        if( Bool )
           PointsTypesList.push_back(Point);
    }

    File.close();
}

void SettingsHandler::loadPatterns()
{
    QFile File("patterns.ini");
    QTextStream Stream(&File);

    if( !File.open(QFile::ReadOnly | QFile::Text) )
    {
        PatternsList = DefaultPatternsList;

        bool SouldAddLast = true;

        if( File.open(QFile::WriteOnly | QFile::Text) )
        {

            if( !PatternsList.contains(LastPattern) )
                PatternsList.push_back(LastPattern);

            for(const auto & ref : PatternsList)
            {
                Stream << ref << '\n';
            }

            File.close();
        }
        return;
    }

    QString Line;
    while( !Stream.atEnd() )
    {
        Line = Stream.readLine();
        PatternsList.push_back(Line);
    }

    File.close();
}

void SettingsHandler::loadSettings()
{
    QString Line = QSettings(APP_NAME).value("LastPointsTypes", DefaultPointsTypes[0].first + ", " + DefaultPointsTypes[0].second).toString();
    LastPattern = QSettings(APP_NAME).value("LastPattern", DefaultPatternsList[0]).toString();

    LastPointsType = stringToPoint(Line);

    loadPatterns();
    loadPointsTypes();    
}

void SettingsHandler::returnDefaultValues()
{
    PatternsList = DefaultPatternsList;
    PointsTypesList = DefaultPointsTypes;
    LastPattern = PatternsList[0];
    LastPointsType = PointsTypesList[0];
}
QStringList &SettingsHandler::getPatternsList()
{
    return PatternsList;
}

void SettingsHandler::setPatternsList(const QStringList &value)
{
    PatternsList = value;
}
QList<QPair<QString, QString> > &SettingsHandler::getPointsTypesList()
{
    return PointsTypesList;
}

void SettingsHandler::setPointsTypesList(const QList<QPair<QString, QString> > &value)
{
    PointsTypesList = value;
}
QPair<QString, QString> &SettingsHandler::getLastPointsType()
{
    return LastPointsType;
}

void SettingsHandler::setLastPointsType(const QPair<QString, QString> &value)
{
    LastPointsType = value;
}
QString &SettingsHandler::getLastPattern()
{
    return LastPattern;
}

void SettingsHandler::setLastPattern(const QString &value)
{
    LastPattern = value;
}


void SettingsHandler::saveNewPoint(const QPair<QString, QString> &NewPoint)
{
    QFile File("points_types.ini");

    if( !File.open(QFile::Append | QFile::WriteOnly | QFile::Text))
        return;

    QTextStream Stream(&File);

    Stream << NewPoint.first;
    Stream << ", ";
    Stream << NewPoint.second;    
    Stream << '\n';

    File.close();

    return;
}

void SettingsHandler::saveNewPattern(const QString &NewPattern)
{
    QFile File("patterns.ini");
    if( !File.open(QFile::Append | QFile::WriteOnly | QFile::Text) )
        return;

    QTextStream Stream(&File);

    Stream << NewPattern;    
    Stream << '\n';

    File.close();

    return;
}

QPair<QString,QString> SettingsHandler::stringToPoint(const QString & Str, bool *Bool)
{
    QRegExp RegExp("(.*), (.*)");

    if( RegExp.indexIn(Str) == -1)
    {
        if( Bool != nullptr)
            *Bool = false;

        return QPair<QString,QString>();
    }

    if( Bool )
        *Bool = true;

    return QPair<QString,QString>(RegExp.capturedTexts()[1], RegExp.capturedTexts()[2]);

}

void SettingsHandler::saveNewLastPoint(const QPair<QString, QString> &NewLastPointsType)
{
    QSettings(APP_NAME).setValue("LastPointsTypes", NewLastPointsType.first + ", " + NewLastPointsType.second);
}

void SettingsHandler::saveNewLastPattern(const QString &NewLastPattern)
{
    QSettings(APP_NAME).setValue("LastPatternType", NewLastPattern);
}



















