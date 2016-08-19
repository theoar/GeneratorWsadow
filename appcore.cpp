#include "appcore.h"

AppCore *AppCore::THIS = nullptr;

AppCore::AppCore(void) :
    QObject(nullptr)
{
    THIS = this;
}

AppCore::~AppCore() {}

QStringList AppCore::convert(const QStringList &Text,
                             const QPair<QString, QString> &PointType,
                             const QString &Pattern,
                             const QString &Kerg)
{
    int Offset = 0;
    int Atributes_count = 0;
    int Atributes_required = 0;

    QStringList InputList = Text;

    QStringList OutputList;
    OutputList.push_back(HeaderString);
    OutputList.push_back("# ");
    OutputList.push_back("#"+ PointType.second + OptionsString + (Kerg.isEmpty() == true ? Pattern : Pattern + Separator + KergCode) );

    Atributes_required = (Pattern.split(Separator, QString::SplitBehavior::SkipEmptyParts)).size();

    InputList.removeAll("");

    QRegExp RegExp("\\b((?:\\w|[^\\s;])+)\\b");
    QString OutputLine;

    for(auto & Line : InputList)
    {

        Atributes_count = 0;

        OutputLine=PointType.first;
        OutputLine+=Separator;

        while( Atributes_count < Atributes_required && ( Offset = RegExp.indexIn( Line, Offset ) ) != -1 )
        {
            Atributes_count++;
            Offset+= RegExp.matchedLength();
            OutputLine+=RegExp.capturedTexts()[1];

            OutputLine+=Separator;
        }

        for(Atributes_count; Atributes_count < Atributes_required; Atributes_count++ )
            OutputLine+=Separator;

        if( !Kerg.isEmpty() )
            OutputLine+=Kerg+Separator;


        OutputList.push_back(OutputLine);
        Offset = 0;
    }

    OutputList.push_back(EndString);

    return OutputList;
}


bool AppCore::readFile(const QString &FileName)
{
    QFile File(FileName);

    if( !File.open(QFile::ReadOnly | QFile::Text) )
        return false;

    LoadedData.clear();

    QTextStream Stream(&File);
    while( !Stream.atEnd() )
        LoadedData.push_back(Stream.readLine());

    File.close();

    return true;
}

bool AppCore::writeFile(const QString &FileName, const QStringList & Text)
{
    QFile File(FileName);

    if( !File.open(QFile::WriteOnly | QFile::Text) )
        return false;

    QTextStream Stream(&File);

    for(const auto & ref : Text)
        Stream << ref << '\n';

    return true;
}

QStringList AppCore::getLoadedData() const
{
    return LoadedData;
}

void AppCore::setLoadedData(const QStringList &value)
{
    LoadedData = value;
}

AppCore * AppCore::getInstance()
{
    return THIS;
}





















