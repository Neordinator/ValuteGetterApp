#include "valutegetter.h"
#include "customFunctions.h"
#include <QTextCodec>

ValuteGetter::ValuteGetter(QObject *parent) : QObject(parent)
{
    valuteCodes = {"USD", "AUD", "AZN", "GBP", "AMD", "BYN", "BGN", "BRL", "HUF", "HKD", "DKK", "EUR", "INR", "KZT", "CAD", "KGS", "CNY",
                   "MDL", "NOK", "PLN", "RON", "XDR", "SGD", "TJS", "TRY", "TMT", "UZS", "UAH", "CZK", "SEK", "CHF", "ZAR", "KRW", "JPY"
                  };
    sourceURL = "http://www.cbr.ru/scripts/XML_daily.asp";
    userNominal = 100;
    manager = new QNetworkAccessManager();
    valuteTimer = new QTimer(this);
    period = 60;

    QObject::connect(valuteTimer, SIGNAL(timeout()), this, SLOT(updateValuteData()));
    QObject::connect(manager, &QNetworkAccessManager::finished, this, [=](QNetworkReply *reply)
    {
        if (reply->error())
        {
            qDebug() << reply->errorString();
            return;
        }
        sourceXML = QString::fromLocal8Bit(reply->readAll());
        ValuteGetter::collectAllDataFromXML();
        emit digitsGlobalCompare();
    });
    QObject::connect(this, &ValuteGetter::rightTimeToGetReply, this, &ValuteGetter::getReply);

    request.setUrl(QUrl(sourceURL));
    manager->get(request);
    valuteTimer->start(period * 1000);
}
void ValuteGetter::getReply()
{
    request.setUrl(QUrl(sourceURL));
    manager->get(request);
}
void ValuteGetter::collectAllDataFromXML()
{
    for (unsigned int i = 0; i < valuteCodes.size(); i++) {
        valutesData.push_back(collectData(valuteCodes[i]));
    }
}
ValuteData ValuteGetter::collectData(QString charCode)
{
    ValuteData data;

    data.setCharCode(charCode);
    data.setName(ValuteGetter::collectName(sourceXML, charCode));
    data.setNominal(ValuteGetter::collectNominal(sourceXML, charCode));
    data.setValue(ValuteGetter::collectValue(sourceXML, charCode));
    data.setCourse(data.getNominal() / data.getValue());

    return data;
}
ValuteData ValuteGetter::getSpecificValuteData(QString charCode)
{
    for(unsigned int i = 0; i < valutesData.size(); i++)
    {
        if(valutesData[i].getCharCode() == charCode)
        {
            return valutesData[i];
        }
    }
    return valutesData[0]; //если нужной валюты нет, возвращаем доллар
}

void ValuteGetter::constructNotAddedValutesGrid()
{
    for(unsigned int i = 0; i < valutesData.size(); i++)
    {
        if(valutesData[i].getIsAdded() == false)
        {
            emit valuteChecked(i, ValuteGetter::getCharCodeByIndex(i), ValuteGetter::getNameByIndex(i));
        }
    }
}

QString ValuteGetter::getCharCodeByIndex(unsigned int index)
{
    return ValuteGetter::getByIndex(index).getCharCode();
}

QString ValuteGetter::getNameByIndex(unsigned int index)
{
    return ValuteGetter::getByIndex(index).getName();
}

int ValuteGetter::getNominalByIndex(unsigned int index)
{
    return ValuteGetter::getByIndex(index).getNominal();
}

bool ValuteGetter::getIsAddedByIndex(unsigned int index)
{
    return ValuteGetter::getByIndex(index).getIsAdded();
}

double ValuteGetter::getValueByIndex(unsigned int index)
{
    return ValuteGetter::getByIndex(index).getValue();
}

double ValuteGetter::getCourseByIndex(unsigned int index)
{
    return ValuteGetter::getByIndex(index).getCourse();
}

void ValuteGetter::setIsAddedByIndex(unsigned int index, bool state)
{
    valutesData[index].setIsAdded(state);
}
void ValuteGetter::setUserNominal(double nominal)
{
    userNominal = nominal;
    emit digitsCompare();
}
QString ValuteGetter::countCourse(unsigned int index)
{
    return QString::number(ValuteGetter::getCourseByIndex(index) * userNominal, 'f', 4);
}

int ValuteGetter::collectNominal(QString& sourceXML, QString charCode)
{
    unsigned int firstValuteIndex = sourceXML.indexOf(charCode);

    QString buffer = "";
    for (unsigned int i = firstValuteIndex; i < sourceXML.size() - 10; i++)
    {
        buffer.push_back(sourceXML[i]);
        if (substr(sourceXML, i + 1, 10) == "</Nominal>") { break; }
    }
    unsigned int start = buffer.indexOf("<Nominal>") + 9;
    unsigned int range = buffer.size() - start;
    buffer = substr(buffer, start, range);
    return buffer.toInt();
}
QString ValuteGetter::collectValueWithComma(QString& sourceXML, QString charCode)
{
    unsigned int firstValuteIndex = sourceXML.indexOf(charCode);

    QString buffer = "";
    for (unsigned int i = firstValuteIndex; i < sourceXML.size() - 8; i++)
    {
        buffer.push_back(sourceXML[i]);
        if (substr(sourceXML, i + 1, 8) == "</Value>") { break; }
    }
    unsigned int start = buffer.indexOf("<Value>") + 7;
    unsigned int range = buffer.size() - start;

    return substr(buffer, start, range);
}

QString ValuteGetter::collectName(QString& sourceXML, QString charCode)
{
    unsigned int firstValuteIndex = sourceXML.indexOf(charCode);

    QString buffer = "";
    for (unsigned int i = firstValuteIndex; i < sourceXML.size() - 8; i++)
    {
        buffer.push_back(sourceXML[i]);
        if (substr(sourceXML, i + 1, 7) == "</Name>") { break; }
    }
    unsigned int start = buffer.indexOf("<Name>") + 6;
    unsigned int range = buffer.size() - start;

    return substr(buffer, start, range);
}
double ValuteGetter::collectValue(QString& sourceXML, QString charCode)
{
    QString tempString = ValuteGetter::collectValueWithComma(sourceXML, charCode);
    commaToDot(tempString);

    return tempString.toDouble();
}

QVector<QString> ValuteGetter::getAllCharCodes(QString& sourceXML)
{
    QVector<QString> allCharCodes;
    QString buffer = "";
    for (unsigned int i = 0; i < sourceXML.size() - 10; i++)
    {

        if (substr(sourceXML, i, 10) == "<CharCode>")
        {
            for (unsigned int t = i + 10; substr(sourceXML, t, 2) != "</"; t++)
            {
                buffer.push_back(sourceXML[t]);
            }
            allCharCodes.push_back(buffer);
            buffer.clear();
        }
    }
    return allCharCodes;
}

void ValuteGetter::updateValuteData()
{
    qDebug() << Q_FUNC_INFO;
    emit rightTimeToGetReply();
}
ValuteData& ValuteGetter::getByIndex(unsigned int index)
{
    return valutesData[index];
}
