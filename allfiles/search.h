#ifndef SEARCH_H
#define SEARCH_H

#include <iostream>
#include <date.h>
using namespace std;
class Search
{
public:
    static void searchTitle(string title, Date* save, Date* source);
    static void searchDateTime(DateTime start,DateTime end,Date* save,Date* source);
    static void searchLocation(string location,Date* save,Date* source);
    static void serachImportant(bool a,Date* save,Date* source);
};

#endif // SEARCH_H
