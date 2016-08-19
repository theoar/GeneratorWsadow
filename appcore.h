#ifndef APPCORE_H
#define APPCORE_H

#include <QObject>
#include "settingshandler.h"
#include <QStringList>
#include <QChar>

class AppCore : public QObject
{

    Q_OBJECT

public:

    AppCore(void);
    ~AppCore(void);

    static AppCore * getInstance(void);

    QStringList convert(const QStringList &Text,
                        const QPair<QString, QString> &PointType,
                        const QString &Pattern,
                        const QString &Kerg);

    bool readFile(const QString &FileName);
    bool writeFile(const QString &FileName, const QStringList &Text);


    QStringList getLoadedData() const;
    void setLoadedData(const QStringList &value);

private:
    QStringList LoadedData;

signals:

public slots:

private:
    static AppCore *THIS;

    const QString HeaderString = "# Wywernerowane przez generator herbaty";
    const QString OptionsString = "=_code;";
    const QString EndString = "#KONIEC";
    const QChar Separator = ';';
    const QString KergCode = "KRG.n";

};


#endif // APPCORE_H
