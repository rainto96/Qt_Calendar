#include "remind.h"
#include "daytime.h"
#include <iostream>
using namespace std;
DayTime& Remind::getRemindTime()
{
    return remindTime;
}
void Remind::setRemindTime(DayTime t)
{
    remindTime=t;
}
