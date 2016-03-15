#include <iostream>
#include <string>
#include <date.h>
#include <search.h>
using namespace std;

void Search::searchTitle(string title,Date* save,Date* source)
{
   int num=1;
   for(int i=1;i<=source[0].dateNum();i++)
   {
      string::size_type idx=source[i].getTitle().find(title);
      if(idx != string::npos)
      {
        save[num].setOrigin(i);
        save[num++]=source[i];
      }
   }
   save[0].setDateNum(num-1);
}


void Search::searchDateTime(DateTime start,DateTime end,Date* save,Date* source)
{
   int num=1;
   for(int i=1;i<=source[0].dateNum();i++)
   {
      if(source[i].getSDay()<=start&&source[i].getEDay()>=end
         ||source[i].getSDay()>=start&&source[i].getSDay()<=end
         ||source[i].getEDay()>=start&&source[i].getEDay()<=end)
      {
          save[num].setOrigin(i);
          save[num++]=source[i];
      }
   }
    save[0].setDateNum(num-1);
}



void Search::searchLocation(string location,Date* save,Date* source)
{
    int num=1;
    for(int i=1;i<=source[0].dateNum();i++)
    {
        string::size_type idx=source[i].getLocation().find(location);
        if(idx != string::npos)
        {
            save[num].setOrigin(i);
            save[num++]=source[i];
        }
    }
    save[0].setDateNum(num-1);
}



void Search::serachImportant(bool a,Date* save,Date* source)
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
