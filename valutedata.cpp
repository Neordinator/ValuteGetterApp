#include "valutedata.h"

/*ValuteData::ValuteData(QObject *parent) : QObject(parent)
{
    isAdded = false;
}*/
ValuteData::ValuteData()
{
    isAdded = false;
}

QString ValuteData::getCharCode()
{
    return m_charCode;
}
QString ValuteData::getName()
{
    return m_name;
}
int ValuteData::getNominal()
{
    return m_nominal;
}
bool ValuteData::getIsAdded()
{
    return isAdded;
}
double ValuteData::getValue()
{
    return m_value;
}
double ValuteData::getCourse()
{
    return m_course;
}

void ValuteData::setCharCode(QString newCharCode)
{
    if(m_charCode != newCharCode)
    {
        m_charCode = newCharCode;
    }
}
void ValuteData::setName(QString newName)
{
    if(m_name != newName)
    {
        m_name = newName;
    }
}
void ValuteData::setNominal(int newNominal)
{
    if(m_nominal != newNominal)
    {
        m_nominal = newNominal;
    }
}
void ValuteData::setIsAdded(bool newBool)
{
    isAdded = newBool;
}
void ValuteData::setValue(double newValue)
{
    if(m_value != newValue)
    {
        m_value = newValue;
    }
}
void ValuteData::setCourse(double newCourse)
{
    if(m_course != newCourse)
    {
        m_course = newCourse;
    }
}
