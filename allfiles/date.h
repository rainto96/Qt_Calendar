#ifndef DATE_H
#define DATE_H

#include <QObject>
#include <string>
#include <datetime.h>
#include <daytime.h>
#include <character.h>
#include <loop.h>
using namespace std;

class Date
{
private:
    char title[111];
    char location[222];
    char PS[1111];
    Character withwhom[100];
    DateTime start_time_date;
    DateTime end_time_date;
    DayTime start_time_day;
    DayTime end_time_day;
    bool all_day;
    Loop loop;
    DateTime clockDate;
    DayTime clockDay;
    int datenum;
    bool important;
    int origin;
    bool needRemind;
    bool isdone;
public:
    Date()
    {
        datenum=1;
    }
    int dateNum();
    void setDateNum(int num);
    void setTitle(string t);
    string getTitle();
    void setLocation(string l);
    string getLocation();
    void setSTime(int H,int M,int S);
    DayTime& getSTime();
    void setETime(int H,int M,int S);
    DayTime& getETime();
    void setSDay(int Y,int M,int D);
    DateTime& getSDay();
    void setEDay(int Y,int M,int D);
    DateTime& getEDay();
    void setIsAllday(int a);
    bool IsAllday();
    void setCharacter(Character a[],int n);
    Character*	getCharacter();
    void setPS(string text);
    string getText();
    void setLoop(DateTime D1,DateTime D2,DateTime D3);
    Loop& getLoop();
    void setClock(DateTime a, DayTime b);
    DayTime& getClockDay();
    DateTime& getClockDate();
    //void onClock(Set&);
    void setImportant(bool a);
    bool isImportant();
    int getOrigin();
    void setOrigin(int s);
    bool NeedRemind();
    void setRemind(bool s);
    bool isDone();
    void setIsdone(bool s);
};
#endif // DATE_H
