#include <iostream>
#include <string>
#include <date.h>
#include <search.h>
using namespace std;

//输入关键字,逐条语句判断是否含有该关键字,若含有，则逐条存在save数组里面。
void Search::searchTitle(string title,Date* save,Date* source)
{
   int num=1;
   for(int i=1;i<=source[0].dateNum();i++)
   {
      string::size_type idx=source[i].getTitle().find(title);
      if(idx != string::npos)
      {

        save[num]=source[i];
        save[num++].setOrigin(i);
      }
   }
   save[0].setDateNum(num-1);
}

//输入起始时间和终止时间，逐条判断时间是否在该段时间段内，若存在，则逐条存储在save数组里面。
void Search::searchDateTime(DateTime start,DateTime end,Date* save,Date* source)
{
   int num=1;
   for(int i=1;i<=source[0].dateNum();i++)
   {
      if(source[i].getSDay()<=start&&source[i].getEDay()>=end
         ||source[i].getSDay()>=start&&source[i].getSDay()<=end
         ||source[i].getEDay()>=start&&source[i].getEDay()<=end)
      {
          save[num]=source[i];
          save[num++].setOrigin(i);
      }
   }
    save[0].setDateNum(num-1);
}

//输入地点，逐条判断该时间是否在该地点发生，若存在，则逐条存储在save数组里面。
void Search::searchLocation(string location,Date* save,Date* source)
{
    int num=1;
    for(int i=1;i<=source[0].dateNum();i++)
    {
        string::size_type idx=source[i].getLocation().find(location);
        if(idx != string::npos)
        {

            save[num]=source[i];
            save[num++].setOrigin(i);
        }
    }
    save[0].setDateNum(num-1);
}

//输入是否关键，逐条语句判断是否与之一致，若一致，则逐条存储在save数组里。
void Search::searchImportant(bool a,Date* save,Date* source)
{
    int num=1;
    for(int i=1;i<=source[0].dateNum();i++)
    {
        if(a==source[i].isImportant())
        {
            save[num].setOrigin(i);
            save[num++]=source[i];
        }
    }
    save[0].setDateNum(num-1);
}

//若输入起始日期或终止日期在其它事件的日期段内，返回true
bool Search::searchDaytime(DateTime day,DayTime start,DayTime end,Date* source)
{
    for(int i=1;i<=source[0].dateNum();i++)
    {
        if(source[i].getSDay()==day&&((source[i].getSTime()<=end&&source[i].getSTime()>=start)||(source[i].getETime()<=end&&source[i].getETime()>=start)))
        {
            return true;
        }
    }
    return false;
}

//若输入起始时间或终止时间在其它事件的时间段内，返回true
bool Search::searchDaytime_edit(DateTime day,DayTime start,DayTime end,Date* source,int index)
{
    for(int i=1;i<=source[0].dateNum();i++)
    {
        if(i!=index&&source[i].getSDay()==day&&((source[i].getSTime()<=end&&source[i].getSTime()>=start)||(source[i].getETime()<=end&&source[i].getETime()>=start)))
        {
            return true;
        }
    }
    return false;
}