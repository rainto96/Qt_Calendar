#ifndef SEARCH_H
#define SEARCH_H

#include <iostream>
#include <date.h>
using namespace std;
class Search
{
public:
    static void searchTitle(string title, Date* save, Date* source);//Ѱ�ҳ����ؼ��ֵ�ʱ��
    static void searchDateTime(DateTime start,DateTime end,Date* save,Date* source);//Ѱ�ҳ�������ʱ����ڷ������¼�
    static void searchLocation(string location,Date* save,Date* source);//Ѱ�ҳ�������ص㷢�����¼�
    static void searchImportant(bool a,Date* save,Date* source);//Ѱ�ҳ���Ҫ�����¼�
    static bool searchDaytime(DateTime day,DayTime start,DayTime end,Date* source);//�ж��¼��Ƿ��������¼��������ϵ��ظ�
    static bool searchDaytime_edit(DateTime day,DayTime start,DayTime end,Date* source,int index);//�ж��¼��Ƿ��������¼���ʱ���ϵ��ظ�
};

#endif // SEARCH_H
