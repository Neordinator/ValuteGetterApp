#ifndef VALUTEGETTER_H
#define VALUTEGETTER_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QVector>
#include <QQuickItem>
#include <QTimer>
#include <QTimer>

#include "valutedata.h"

class ValuteGetter : public QObject
{
    Q_OBJECT
public:
    explicit ValuteGetter(QObject *parent = nullptr);
    ~ValuteGetter(){}

    void collectAllDataFromXML();
    //QVector<ValuteData> collectAllDataFromXML();
    ValuteData getSpecificValuteData(QString charCode);
    Q_INVOKABLE void constructNotAddedValutesGrid();
    Q_INVOKABLE QString getCharCodeByIndex(unsigned int);
    Q_INVOKABLE QString getNameByIndex(unsigned int);
    Q_INVOKABLE int getNominalByIndex(unsigned int);
    Q_INVOKABLE bool getIsAddedByIndex(unsigned int);
    Q_INVOKABLE double getValueByIndex(unsigned int);
    Q_INVOKABLE double getCourseByIndex(unsigned int);
    Q_INVOKABLE void setIsAddedByIndex(unsigned int, bool);
    Q_INVOKABLE void setUserNominal(double);
    Q_INVOKABLE QString countCourse(unsigned int);

signals:
    void rightTimeToGetReply();
    void valuteChecked(unsigned int, QString, QString);
    void digitsGlobalCompare();
    void digitsCompare();

public slots:
    void getReply();
    QVector<QString> getAllCharCodes(QString&);
    void updateValuteData();

private:
    QNetworkAccessManager *manager;
    QNetworkRequest request;
    QString sourceXML;
    QVector<QString> valuteCodes;
    QVector<ValuteData> valutesData;
    QString sourceURL;
    QTimer *valuteTimer;
    int period;
    double userNominal;

    QString collectValueWithComma(QString&, QString);
    QString collectName(QString&, QString);
    ValuteData collectData(QString);
    ValuteData& getByIndex(unsigned int);
    int collectNominal(QString&, QString);
    double collectValue(QString&, QString);

};

#endif // VALUTEGETTER_H
