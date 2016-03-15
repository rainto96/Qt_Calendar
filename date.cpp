#include <date.h>
#include <cstring>
void Date::setTitle(string t)
{
    strcpy(title,t.c_str());
    /*int len=t.length();
    for(int i=0;i<len;i++)
    {
        title[i]=t[i];
    }
    title[len]='\0';*/
}

string Date::getTitle()
{
    return string(title);
}
int Date::dateNum()
{
    return datenum;
}
void Date::setDateNum(int num)
{
    datenum=num;
}
void Date::setLocation(string l)
{
    strcpy(location,l.c_str());
    /*int len=l.length();
    for(int i=0;i<len;i++)
    {
        location[i]=l[i];
    }
    location[len]='\0';*/
}


string Date::getLocation()
{
    return string(location);
}


void Date::setSTime(int H,int M,int S)
{
   start_time_day.SetTime(H,M,S);
}


DayTime& Date::getSTime()
{
    return start_time_day;
}


void Date::setETime(int H,int M,int S)
{
    end_time_day.SetTime(H,M,S);
}


DayTime& Date::getETime()
{
    return end_time_day;
}


void Date::setSDay(int Y,int M,int D)
{
    start_time_date.SetDate(Y,M,D);

}


DateTime& Date::getSDay()
{
    return start_time_date;
}


void Date::setEDay(int Y,int M,int D)
{
    end_time_date.SetDate(Y,M,D);

}


DateTime& Date::getEDay()
{
    return end_time_date;
}
void Date::setIsAllday(int a)
{
    if(a==0)
        all_day=false;
    else
        all_day=true;
}

bool Date::IsAllday()
{
    return all_day;

}


void Date::setCharacter(Character a[],int n)
{
   for(int i=0;i<n;i++)
   {
       withwhom[i]=a[i];
   }
}



Character*	Date::getCharacter()
{

    return withwhom;
}


void Date::setPS(string text)
{
    strcpy(PS,text.c_str());
    /*int len=text.length();
    for(int i=0;i<len;i++)
    {
        PS[i]=text[i];
    }
    PS[len]='\0';*/
}


string Date::getText()
{
    return string(PS);
}


void Date::setLoop(DateTime D1,DateTime D2,DateTime D3)
{
   loop.set_Start_DateTime(D1);
   loop.set_End_DateTime(D2);
   loop.set_loopLength(D3);
}
Loop& Date::getLoop()
{
    return loop;
}

void Date::setClock(DateTime a,DayTime b)
{
  clockDate=a;
  clockDay=b;
}

DayTime& Date::getClockDay()
{
    return  clockDay;
}

DateTime& Date::getClockDate()
{

    return clockDate;
}
//void Date::onClock(Set&)
void Date::setImportant(bool a)
{
    important=a;
}
bool Date::isImportant()
{
    return important;
}
int Date::getOrigin()
{
    return origin;
}
void Date::setOrigin(int s)
{
    origin=s;
}
bool Date::NeedRemind()
{
    return needRemind;
}
void Date::setRemind(bool s)
{
    needRemind=s;
}
bool Date::isDone()
{
    return isdone;
}
void Date::setIsdone(bool s)
{
    isdone=s;
}
