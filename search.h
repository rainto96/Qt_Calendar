#ifndef SEARCH_H
#define SEARCH_H

#include <iostream>
#include <date.h>
using namespace std;
class Search
{
public:
    static void searchTitle(string title, Date* save, Date* source);//寻找出含关键字的时间
    static void searchDateTime(DateTime start,DateTime end,Date* save,Date* source);//寻找出在输入时间段内发生的事件
    static void searchLocation(string location,Date* save,Date* source);//寻找出在输入地点发生的事件
    static void searchImportant(bool a,Date* save,Date* source);//寻找出重要与否的事件
    static bool searchDaytime(DateTime day,DayTime start,DayTime end,Date* source);//判断事件是否与其他事件有日期上的重复
    static bool searchDaytime_edit(DateTime day,DayTime start,DayTime end,Date* source,int index);//判断事件是否与其他事件有时间上的重复
};

#endif // SEARCH_H
