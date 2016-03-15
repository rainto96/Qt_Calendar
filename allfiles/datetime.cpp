#include "datetime.h"
#include <sstream>
bool DateTime::operator== (DateTime second)
{
	return Year==second.Year && Month==second.Month && Day==second.Day;
}
QDate DateTime::toQDate()//////////////////////////////////////////////////////////////////////////////
{
    return QDate(Year,Month,Day);
}
void DateTime::QDatetoDate(QDate D)
{
    Year=D.year();
    Month=D.month();
    Day=D.day();
}

bool DateTime::operator>= (DateTime second)
{
	if(Year>second.Year)
		return true;
	else if(Year<second.Year)
		return false;
	else
	{
		if(Month>second.Month)
			return true;
		else if(Month<second.Month)
			return false;
		else
		{
			if(Day>second.Day)
				return true;
			else if(Day<second.Day)
				return false;
			else
				return true;
		}
	}
}
bool DateTime::operator<= (DateTime second)
{
	if((*this)==second)
		return true;
	else
	{
		if((*this)>=second)
			return false;
		else
			return true;
	}
}
int DateTime::getDay()
{
	return Day;
}
int DateTime::getYear()
{
	return Year;
}
int DateTime::getMonth()
{
	return Month;
}
int DateTime::setYear(int year)
{
    Year=year;
}
int DateTime::setMonth(int month)
{
    Month=month;
}
int DateTime::setDay(int day)
{
    Day=day;
}
DateTime::DateTime ()
{
    Year = Month = Day = 0;
}
DateTime::DateTime (int Y, int M, int D)
{
    Year = Y;
    Month = M;
    Day = D;
}
bool DateTime::IsLeap ()
{
    return ((this->Year % 4 == 0) && (this->Year % 100 != 0) || (this->Year % 400 == 0));
}
void DateTime::SetDate (int Y, int M, int D)
{
    Year = Y;
    Month = M;
    Day = D;
}
void DateTime::Display ()
{
    cout <<  Month << "/"<< Day << "/"<< Year << endl;
}
bool DateTime::IsTrue ()
{
    if (!(this->Year < 1900 || this->Month > 12 || this->Month <= 0))
    {
        if (this->IsLeap ())
        {
            if (this->Day <= 29) return true;
        }
        else
        {
            if (this->Day <= 28) return true;
        }
    }
    return false;
}
int DateTime::CalculateDays (DateTime d)
{
    int flag = 0;
    int result = 0;
    if (d.IsLeap ())
        flag = 1;
    for (int i = 1; i < d.Month; i++)
    {
        if (i ==2)
            result += 28 + flag;
        else if (((i % 2 == 1) && (i < 8)) || ((i % 2 == 0) && (i > 7)))
            result += 31;
        else
            result += 30;
    }
    result += d.Day;
    return result;
}
int DateTime::getWeek ()
{
    DateTime my=(*this);
    if(my.Month == 1 || my.Month == 2)
    {
        my.Month += 12;
        my.Year--;
    }
    int flag =
        (my.Day+2*my.Month+3*(my.Month+1)/5+my.Year+my.Year/4-my.Year/100+my.Year/400)%7;
    switch(flag)
    {
        case 0: return 1; break;
        case 1: return 2; break;
        case 2: return 3; break;
        case 3: return 4; break;
        case 4: return 5; break;
        case 5: return 6; break;
        case 6: return 7; break;
    }
}
int DateTime::getDayNumOfOneMonth(int year,int month)
{
    bool isleap=DateTime(year,month,1).IsLeap();
    int num[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    if(month==2)
    {
        if(isleap)
            return 29;
        else
            return 28;
    }
    else
        return num[month];
}

string DateTime::show()
{
    string s;
    stringstream ss;
    ss.clear();
    ss<<Year<<'/'<<Month<<'/'<<Day;
    ss>>s;
    return s;
}
