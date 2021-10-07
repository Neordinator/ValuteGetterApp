#ifndef VALUTEDATA_H
#define VALUTEDATA_H

#include <QObject>

class ValuteData
{
    //Q_OBJECT
    Q_PROPERTY(QString charCode READ getCharCode WRITE setCharCode NOTIFY charCodeChanged)
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(int nominal READ getNominal WRITE setNominal NOTIFY nominalChanged)
    Q_PROPERTY(double value READ getValue WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(double course READ getCourse WRITE setCourse NOTIFY courseChanged)

public:
    //explicit ValuteData(QObject *parent = nullptr);
    ValuteData();

    Q_INVOKABLE QString getCharCode();
    Q_INVOKABLE QString getName();
    Q_INVOKABLE int getNominal();
    Q_INVOKABLE bool getIsAdded();
    Q_INVOKABLE double getValue();
    Q_INVOKABLE double getCourse();

    void setCharCode(QString);
    void setName(QString);
    void setNominal(int);
    void setIsAdded(bool);
    void setValue(double);
    void setCourse(double);

signals:
    void charCodeChanged();

public slots:

private:
    QString m_charCode;
    QString m_name;
    int m_nominal;
    bool isAdded;
    double m_value;
    double m_course;
};

#endif // VALUTEDATA_H
