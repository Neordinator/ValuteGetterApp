#ifndef CUSTOMFUNCTIONS_H
#define CUSTOMFUNCTIONS_H

#include <QString>
QString substr(QString &string, unsigned int startSubstr, unsigned int range)
{
    if ((string.isEmpty() == true) || (string.size() < range)) return "";
    if ((range == 0) || (range == 1)) return string[startSubstr];
    QString tempSubstr = "";
    for(unsigned int i = startSubstr; i < (startSubstr + range); i++)
    {
        tempSubstr.push_back(string[i]);
    }
    return tempSubstr;
}
void commaToDot(QString &valueString)
{
    for (unsigned int i = 0; i < valueString.size(); i++)
    {
        if (valueString[i] == ',')
        {
            valueString[i] = '.';
            break;
        }
    }
}

#endif // CUSTOMFUNCTIONS_H
