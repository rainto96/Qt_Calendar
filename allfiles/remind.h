
#ifndef REMIND_H
#define REMIND_H
#include <cstdio>
#include <cstring>
#include "date.h"
#include <QObject>
#include "daytime.h"
#include <iostream>
#include "ShowNowTime.h"
#include <QMessageBox>
#include "date.h"
#include <QTimer>
#include "search.h"
using namespace std;
class Remind:public QObject
{
    Q_OBJECT
    private:
        DayTime remindTime;
        Date* date;
        QTimer timer;
    public slots:
        void checkPlaySound()
        {
            DayTime nowtime(ShowNowTime::getHour(),ShowNowTime::getMinite(),ShowNowTime::getSecond());

            if(nowtime==remindTime)
            {
                QMessageBox* s=new QMessageBox;
                QString ss=QString("Hey My dear lord,Here are a date right now!\nDateTitle:%1\nDateLocation:%2\nDate:%3\nStartTime:%4\nEndTime:%5\n");
                ss=ss.arg(QString::fromStdString(date->getTitle()),QString::fromStdString(date->getLocation()),QString::fromStdString(date->getSDay().show()),QString::fromStdString(date->getSTime().show()),QString::fromStdString(date->getETime().show()));
                s->setText(ss);
                s->exec();
            }
        }
        /*void checkTimethenMes()
        {
            QMessageBox msgbox;
            QString str=QString("the date's title is %1");
            str=str.arg(one.getDate()->getTitle());
            msgbox.setText(str);
            msgbox.show();
        }*/
    public:
        //DayTime nowtime;
        DayTime& getRemindTime();
        void setRemindTime(DayTime t);
        Date* getDate()
        {
            return date;
        }
        void setDate(Date* here)
        {
            date=here;
        }
        static void setTimeClock_Today(Date* AllDates)
        {
            Remind *t=new Remind[25];
            Date* todayDate=new Date[25];
            todayDate->setDateNum(0);
            DateTime today(ShowNowTime::getYear(),ShowNowTime::getMonth(),ShowNowTime::getDay());
            Search::searchDateTime(today,today,todayDate,AllDates);
            for(int i=1;i<=todayDate->dateNum();i++)
            {
                if(todayDate[i].NeedRemind())
                {
                    DayTime time=todayDate[i].getSTime();
                    (t+i)->setRemindTime(DayTime(time.getH(),time.getM(),time.getS()));
                    (t+i)->setDate(todayDate+i);
                }
            }
            QTimer *time_clock=new QTimer(t);
            for(int i=1;i<=todayDate->dateNum();i++)
                QObject::connect(time_clock,SIGNAL(timeout()),t+i,SLOT(checkPlaySound()));
            time_clock->start(1);
            cout<<todayDate->dateNum()<<endl;
        }

};
#endif // REMIND_H
