#ifndef SETTINGSHANDLER_H
#define SETTINGSHANDLER_H

#include <QObject>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QPair>
#include <QRegExp>
#include <QSettings>
#include <QTextCodec>

#define APP_NAME "Generator wsadow"

class SettingsHandler : public QObject
{
    Q_OBJECT
public:
    SettingsHandler(void);

    void loadSettings();

    void saveNewLastPattern(const QString &NewLastPattern);
    void saveNewLastPoint(const QPair<QString, QString> &NewLastPointsType);

    void saveNewPoint(const QPair<QString, QString> &NewPoint);
    void saveNewPattern(const QString &NewPattern);
    QPair<QString, QString> stringToPoint(const QString & Str, bool * Bool = nullptr);

    void returnDefaultValues();

    QStringList &getPatternsList();
    void setPatternsList(const QStringList &value);

    QList<QPair<QString, QString> > &getPointsTypesList();
    void setPointsTypesList(const QList<QPair<QString, QString> > &value);


    QPair<QString, QString> &getLastPointsType();
    void setLastPointsType(const QPair<QString, QString> &value);

    QString &getLastPattern();
    void setLastPattern(const QString &value);

private:
    QStringList PatternsList;
    QList<QPair<QString, QString>> PointsTypesList;
    QPair<QString, QString> LastPointsType;
    QString LastPattern;


private:
    const static QStringList DefaultPatternsList;
    const static QList<QPair<QString, QString>> DefaultPointsTypes;

    void loadPointsTypes();
    void loadPatterns();

};


#endif // SETTINGSHANDLER_H
