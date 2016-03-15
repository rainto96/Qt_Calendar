#include <iostream>
#include <string>
#include <date.h>
#include <search.h>
using namespace std;

//����ؼ���,��������ж��Ƿ��иùؼ���,�����У�����������save�������档
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

//������ʼʱ�����ֹʱ�䣬�����ж�ʱ���Ƿ��ڸö�ʱ����ڣ������ڣ��������洢��save�������档
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

//����ص㣬�����жϸ�ʱ���Ƿ��ڸõص㷢���������ڣ��������洢��save�������档
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

//�����Ƿ�ؼ�����������ж��Ƿ���֮һ�£���һ�£��������洢��save�����
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

//��������ʼ���ڻ���ֹ�����������¼������ڶ��ڣ�����true
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

//��������ʼʱ�����ֹʱ���������¼���ʱ����ڣ�����true
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