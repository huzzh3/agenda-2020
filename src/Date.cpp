#include <iostream>
#include <string>
#include <time.h>
#include <sstream>
#include "../include/Date.hpp"
using namespace std;

Date::Date() {

    this->m_year = 0;
    this->m_month = 0;
    this->m_day = 0;
    this->m_hour = 0;
    this->m_minute = 0;
}

Date::Date(int t_year, int t_month, int t_day, int t_hour, int t_minute) {

    this->m_year = t_year;
    this->m_month = t_month;
    this->m_day = t_day;
    this->m_hour = t_hour;
    this->m_minute = t_minute;
}
bool isValidyearStr(char str[]){
    for (int i = 0; i < 4; i++) {
        if (str[i] == 'a') {
            return false;
        }
    }
    return true;
}
bool isValidStr(char str[]){
    for (int i = 0; i < 2; i++) {
        if (str[i] == 'a') {
            return false;
        }
    }
    return true;
}
bool isValidString(const string& dateString) {
    char yearStr[20]={'a','a','a','a'}; 
    char monthStr[20]={'a','a'};
    char dayStr[20]={'a','a'}; 
    char hourStr[20]={'a','a'};
    char minuteStr[20]={'a','a'};
    string model = "year";
    int j = 0;
    for(int i = 0; i < dateString.length(); i++) {
        if(dateString[i] >= '0' && dateString[i] <= '9') {
            if (model == "year") {
                yearStr[j++] = dateString[i];
            }
            else if (model == "month") {
                monthStr[j++] = dateString[i];
            }
            else if (model == "day") {
                dayStr[j++] = dateString[i];
            }
            else if (model == "hour") {
                hourStr[j++] = dateString[i];
            }
            else if (model == "minute") {
                minuteStr[j++] = dateString[i];
            }
        }
        else if(dateString[i] == '-') {
            if(model == "year") {
                model = "month";
                j = 0;
            }
            else if(model == "month") {
                model = "day";
                j = 0;
            }
        }
        else if(dateString[i] == '/') {
            model = "hour";
            j = 0;
        }
        else if(dateString[i] == ':') {
            model = "minute";
            j = 0;
        }
    }


    if(!isValidyearStr(yearStr))
        return false;
    else if(!isValidStr(monthStr))
        return false;
    else if(!isValidStr(dayStr))
        return false;
    else if(!isValidStr(hourStr))
        return false;
    else if(!isValidStr(minuteStr))
        return false;

    return true;
    /*char *cha = (char*)dateString.data();

    char yearStr[4], monthStr[2], dayStr[2], hourStr[2], minuteStr[2];
    sscanf(cha, "%s-%s-%s/%s:%s", &yearStr, &monthStr, &dayStr
            , &hourStr, &minuteStr);

    if (monthStr[1] == '\0' || dayStr[1] == '\0' || hourStr[1] == '\0' ||
        minuteStr[1] == '\0' || yearStr[1] == '\0' || yearStr[2] == '\0' ||
        yearStr[3] == '\0') {
        return false;
    }

    return true;*/
}
Date::Date(const std::string &dateString){
    if(!isValidString(dateString)) {

        this->m_year = 0;
        this->m_month = 0;
        this->m_day = 0;
        this->m_hour = 0;
        this->m_minute = 0;
    }
    else {
        char *cha = (char*)dateString.data();

        sscanf(cha, "%d-%d-%d/%d:%d", &this->m_year, &this->m_month, &this->m_day
            , &this->m_hour, &this->m_minute);
    }
}

int Date::getYear(void) const {
    
    return this->m_year;
}

void Date::setYear(const int t_year) {

    this->m_year = t_year;
}

int Date::getMonth(void) const {
    
    return this->m_month;
}

void Date::setMonth(const int t_month) {

    this->m_month = t_month;
}

int Date::getDay(void) const {

    return this->m_day;
}

void Date::setDay(const int t_day) {

    this->m_day = t_day;
}

int Date::getHour(void) const {

    return this->m_hour;
}

void Date::setHour(const int t_hour) {

    this->m_hour = t_hour;
}

int Date::getMinute(void) const {

    return this->m_minute;    
}

void Date::setMinute(const int t_minute) {

    this->m_minute = t_minute;
}

int days_normal[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
int days_leap[13] = {0,31,29,31,30,31,30,31,31,30,31,30,31};
bool isLeap(int t_year) {
    if(t_year % 400 == 0) {
        return true;
    }
    else if(t_year % 100 != 0 && t_year % 4 == 0) {
        return true;
    }
    
    return false;
}
bool Date::isValid(const Date &t_date) {
    if(t_date.m_year > 9999 || t_date.m_year < 1000) {
        return false;
    }

    if(t_date.m_month > 12 || t_date.m_month < 1) {
        return false;
    }

    if(isLeap(t_date.m_year)) {
        if(t_date.m_day > days_leap[t_date.m_month] || t_date.m_day < 1) {
            return false;
        }
    }
    else {
        if(t_date.m_day > days_normal[t_date.m_month] || t_date.m_day < 1) {
            return false;
        }
    }

    if(t_date.m_hour > 23 || t_date.m_hour < 0) {
        return false;
    }

    if(t_date.m_minute > 59 || t_date.m_minute < 0) {
        return false;
    }

    return true;
}

Date Date::stringToDate(const std::string &t_dateString) {
    
    if(!isValidString) {
        Date d1("0000-00-00/00:00");
        return d1;
    }
    else {
        Date d1(t_dateString);
        return d1;
    }

    /*Date date;
    char *cha = (char*)t_dateString.data();
    sscanf(cha, "%d-%d-%d/%d:%d", &date.m_year, &date.m_month, &date.m_day
            , &date.m_hour, &date.m_minute);

    return date;*/
}

string Date::dateToString(const Date &t_date) {

    if(!isValid(t_date)){
        return "0000-00-00/00:00";
    }

    string str;

    if (t_date.getYear() < 10) {
        str = "000";
    }
    else if (t_date.getYear() >= 10 && t_date.getYear() < 100) {
        str = "00";
    }
    else if (t_date.getYear() >= 100 && t_date.getYear() < 1000) {
        str = "0";
    }
    str += to_string(t_date.getYear());
    str += "-";

    if (t_date.getMonth() < 10) {
        str += "0";
    }
    str += to_string(t_date.getMonth());
    str += "-";

    if (t_date.getDay() < 10) {
        str += "0";
    }
    str += to_string(t_date.getDay());
    str += "/";

    if (t_date.getHour() < 10) {
        str += "0";
    }
    str += to_string(t_date.getHour());
    str += ":";

    if (t_date.getMinute() < 10) {
        str += "0";
    }
    str += to_string(t_date.getMinute());

    return str;

    /*sprintf(yearStr, "%04d", t_date.m_year);
    sprintf(monthStr, "%02d", t_date.m_month);
    sprintf(dayStr, "%02d", t_date.m_day);
    sprintf(hourStr, "%02d", t_date.m_hour);
    sprintf(minuteStr, "%02d", t_date.m_minute);

    char s[20];
    sprintf(s, "%s-%s-%s/%s:%s", yearStr, monthStr, dayStr, hourStr, minuteStr);

    string str(s);
    return str;*/
}

Date& Date::operator=(const Date &t_date) {
    this->m_year = t_date.m_year;
    this->m_month = t_date.m_month;
    this->m_day = t_date.m_day;
    this->m_hour = t_date.m_hour;
    this->m_minute = t_date.m_minute;

    return *this;
}

bool Date::operator==(const Date &t_date) const {
    if (this->m_year == t_date.m_year) {
        if(this->m_month == t_date.m_month) {
            if(this->m_day == t_date.m_day) {
                if(this->m_hour == t_date.m_hour) {
                    if(this->m_minute == t_date.m_minute) {
                        
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

bool Date::operator>(const Date &t_date) const {
    if (this->m_year > t_date.m_year) {
        return true;
    }
    else if (this->m_year == t_date.m_year) {

        if (this->m_month > t_date.m_month) {
            return true;
        }
        else if (this->m_month == t_date.m_month) {
            
            if (this->m_day > t_date.m_day) {
                return true;
            }
            else if (this->m_day == t_date.m_day) {
                
                if (this->m_hour > t_date.m_hour) {
                    return true;
                }
                if (this->m_hour == t_date.m_hour) {
                    
                    if (this->m_minute > t_date.m_minute) {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

bool Date::operator<(const Date &t_date) const {
    if (this->m_year < t_date.m_year) {
        return true;
    }
    else if (this->m_year == t_date.m_year) {

        if (this->m_month < t_date.m_month) {
            return true;
        }
        else if (this->m_month == t_date.m_month) {
            
            if (this->m_day < t_date.m_day) {
                return true;
            }
            else if (this->m_day == t_date.m_day) {
                
                if (this->m_hour < t_date.m_hour) {
                    return true;
                }
                if (this->m_hour == t_date.m_hour) {
                    
                    if (this->m_minute < t_date.m_minute) {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

bool Date::operator>=(const Date &t_date) const {
    if(*this == t_date || *this > t_date) {
        return true;
    } 

    return false;
}

bool Date::operator<=(const Date &t_date) const {
    if(*this == t_date || *this < t_date) {
        return true;
    } 

    return false;
}