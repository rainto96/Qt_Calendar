#ifndef DATETIME_H
#define DATETIME_H
#include <QDateTime>
#include <iostream>
#include <string>
using namespace std;

class DateTime
{
    private:
        int Year, Month, Day;
    public:
        bool operator >=(DateTime second);
        bool operator <=(DateTime second);
        bool operator ==(DateTime second);
		int getYear();
		int getMonth();
		int getDay();
        int setYear(int year);
        int setMonth(int month);
        int setDay(int day);
        DateTime ();
        DateTime (int Y, int M, int D);
        bool IsLeap ();
        bool IsTrue ();
        void SetDate (int Y, int M, int D);
        int CalculateDays (DateTime d);
        int getWeek ();
        void Display ();
        static int getDayNumOfOneMonth(int year,int month);
        string show();
        QDate toQDate();//////////////////////////////////////////////////////////////////////////////
        void QDatetoDate(QDate D);////////////////////////////////////////////////////////////
};

#endif // DATETIME_H
