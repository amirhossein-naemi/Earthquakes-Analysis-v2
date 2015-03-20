//---------------------------------------------------------------------------
//
// Earthquakes' Events Analysis
// By Amirhossein Naemi
// March, 2015
// GIT: https://github.com/amirhossein-naemi/Earthquakes-Analysis-v2
// This program reads in one integer from a amir.in file and returns the
//
//---------------------------------------------------------------------------

#include "earthquake.h"

int str2int(const std::string& str)
{
    int result = 0;

    std::string::const_iterator i = str.begin();

    if (i == str.end())
        return false;

    bool negative = false;

    if (*i == '-')
    {
        negative = true;
        ++i;

        if (i == str.end())
            return false;
    }

    result = 0;

    for (; i != str.end(); ++i)
    {
        if (*i < '0' || *i > '9')
            return false;

        result *= 10;
        result += *i - '0';
    }

    if (negative)
        result = -result;

    return result;
}

string mnth_enum2str(months mnth) {
    switch (mnth) {
    case January:
        return "January";
        break;
    case February:
        return "February";
        break;
    case March:
        return "March";
        break;
    case April:
        return "April";
        break;
    case May:
        return "May";
        break;
    case June:
        return "June";
        break;
    case July:
        return "July";
        break;
    case August:
        return "August";
        break;
    case September:
        return "September";
        break;
    case October:
        return "October";
        break;
    case November:
        return "November";
        break;
    case December:
        return "December";
        break;
    }
}

months mnth_str2enum(string mnth) {

    int imnth = str2int(mnth);
    months ret = January;
    
    switch (imnth) {
    case 1:
        ret = January;
        break;
    case 2:
        ret =  February;
        break;
    case 3:
        ret =  March;
        break;
    case 4:
        ret =  April;
        break;
    case 5:
        ret =  May;
        break;
    case 6:
        ret =  June;
        break;
    case 7:
        ret =  July;
        break;
    case 8:
        ret =  August;
        break;
    case 9:
        ret =  September;
        break;
    case 10:
        ret =  October;
        break;
    case 11:
        ret =  November;
        break;
    case 12:
        ret =  December;
        break;
    }
    
    return ret;
}
