#include "daydialog.h"
#include "ui_daydialog.h"
#include "FileIO.h"
#include <QLabel>
#include <QDebug>
#include <QCloseEvent>
#include "ShowNowTime.h"



DayDialog::DayDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DayDialog)
{
    ui->setupUi(this);
    AllDates=new Date[99];
    int daytemp=ShowNowTime::getDay();
    int monthtemp=ShowNowTime::getMonth();
    int yeartemp=ShowNowTime::getYear();
    date=DateTime(yeartemp,monthtemp,daytemp);
    FileIO::readFromFile(AllDates,"/home/rainto96/Qtprogram/table/mem.dat",99);
    AllDatessize=AllDates[0].dateNum();

    ui->timeEdit_Etime->setTime(QTime(ShowNowTime::getHour(),ShowNowTime::getMinite(),ShowNowTime::getSecond()));
    ui->timeEdit_Stime->setTime(QTime(ShowNowTime::getHour(),ShowNowTime::getMinite(),ShowNowTime::getSecond()));

    load();
}

DayDialog::~DayDialog()
{
    delete ui;
}
bool DayDialog::searchDate(int row,Date& D)
{
    for(int i=0;i<t;i++)
    {
        if(thisdate[i].row==row)
        {
            D=thisdate[i].date;
            return true;
        }
    }
    return false;
}

void DayDialog::on_tableWidget_list_cellClicked(int row, int column)
{
    //Date d=this->searchDate(row);
   // cout<<d.getSTime().getH()<<endl;
    Date d;
    if(this->searchDate(row,d))
    {
        ui->textBrowser_title->setText(QString::fromStdString(d.getTitle()));
        ui->textBrowser_text->setText(QString::fromStdString(d.getText()));
        ui->timeEdit_Stime->setTime(QTime(d.getSTime().getH(),d.getSTime().getM(),d.getSTime().getS()));
        ui->timeEdit_Etime->setTime(QTime(d.getETime().getH(),d.getETime().getM(),d.getETime().getS()));

        int looplenth=0;
        if(d.getLoop().get_loopLength().getYear()!=0)
        {
            looplenth=d.getLoop().get_loopLength().getYear();
            ui->comboBox_Looptype->setCurrentIndex(0);
        }
        else if(d.getLoop().get_loopLength().getMonth()!=0)
        {
            looplenth=d.getLoop().get_loopLength().getMonth();
            ui->comboBox_Looptype->setCurrentIndex(1);
        }
        else if(d.getLoop().get_loopLength().getDay()!=0)
        {
            looplenth=d.getLoop().get_loopLength().getDay();
            ui->comboBox_Looptype->setCurrentIndex(2);
        }
        ui->textBrowser_Loopnum->setText(QString::number(looplenth));

        if(d.IsAllday())
             ui->textBrowser_allday->setText(QString("YES"));
        else
            ui->textBrowser_allday->setText(QString("NO"));

        int clock_num=0;
        if(d.getClockDate().getDay()>0)
        {
            clock_num=d.getClockDate().getDay();
            ui->comboBox_Clocktype->setCurrentIndex(2);
        }
        else if(d.getClockDay().getH()>0)
        {
            clock_num=d.getClockDay().getH();
            ui->comboBox_Clocktype->setCurrentIndex(1);
        }
        else if(d.getClockDay().getM()>0)
        {
            clock_num=d.getClockDay().getM();
            ui->comboBox_Clocktype->setCurrentIndex(0);
        }
        ui->textBrowser_Clocknum->setText(QString::number(clock_num));

        ui->textBrowser_Location->setText(QString::fromStdString(d.getLocation()));

        ui->textBrowser_withwho->setText(QString::fromStdString(d.getCharacter()->getName()));
    }
    else
    {
        ui->timeEdit_Etime->setTime(QTime(ShowNowTime::getHour(),ShowNowTime::getMinite(),ShowNowTime::getSecond()));
        ui->timeEdit_Stime->setTime(QTime(ShowNowTime::getHour(),ShowNowTime::getMinite(),ShowNowTime::getSecond()));
        ui->textBrowser_withwho->clear();
        ui->textBrowser_title->clear();
        ui->textBrowser_text->clear();
        ui->textBrowser_Loopnum->clear();
        ui->textBrowser_Location->clear();
        ui->textBrowser_Clocknum->clear();
        ui->textBrowser_allday->clear();
    }
}

void DayDialog::on_pushButton_Edit_clicked()
{
    dialog_save.getInfo(AllDates);
    dialog_save.exec();
    AllDatessize=AllDates[0].dateNum();
    load();
}
Date* DayDialog::getAllDates()
{
    return AllDates;
}


string DayDialog::checkmonth(DateTime date)
{
    switch(date.getMonth())
    {
    case 1:return "Jan.";break;
    case 2:return "Feb.";break;
    case 3:return "Mar.";break;
    case 4:return "Apr.";break;
    case 5:return "May";break;
    case 6:return "Jun.";break;
    case 7:return "Jul.";break;
    case 8:return "Aug.";break;
    case 9:return "Sept.";break;
    case 10:return "Oct.";break;
    case 11:return "Nov.";break;
    case 12:return "Dec.";break;
    }
}

string DayDialog::checkweek(int a )
{
    switch(date.getWeek())
    {
    case 1:return "Monday";break;
    case 2:return "Tuesday";break;
    case 3:return "Wednesday";break;
    case 4:return "thursday";break;
    case 5:return "Friday";break;
    case 6:return "Saturday";break;
    case 7:return "Sunday";break;
    }
}

void DayDialog::load()
{
    t=0;
    Character a[2];
    a[0].setName("YQP");
    a[0].setEmail("qingping@qq.com");
    a[1].setName("YQP1");
    a[1].setEmail("qingping@qq.com");

    ui->tableWidget_list->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_list->setColumnCount(2);//
    ui->tableWidget_list->setColumnWidth(0,25);
    ui->tableWidget_list->setRowCount(24);
    for(int i=0;i<24;i++)
        ui->tableWidget_list->setRowHeight(i,50);
    QStringList list;
    list<<""<<"timelist";
    ui->tableWidget_list->setHorizontalHeaderLabels(list);
    ui->tableWidget_list->horizontalHeader()->setStretchLastSection(1);
    for(int i=0;i<24;i++)
    {
        QTableWidgetItem *item = new QTableWidgetItem(QString::number(i));
        item->setTextAlignment(0x0004|0x0080);
        ui->tableWidget_list->setItem(i,0,item);
    }

    ui->Label_Day->setFont(QFont(ui->Label_Day->font().rawName(),60));
    ui->Label_Day->setText(QString::number(date.getDay()));
    ui->Label_Month->setFont(QFont(ui->Label_Day->font().rawName(),17));
    ui->Label_Month->setText(QString::fromStdString(checkmonth(date)));
    ui->Label_Week->setFont(QFont(ui->Label_Day->font().rawName(),17));
    ui->Label_Week->setText(QString::fromStdString(checkweek(date.getWeek())));
    ui->Label_year->setFont(QFont(ui->Label_Day->font().rawName(),21));
    ui->Label_year->setText(QString::number(date.getYear()));



    //AllDatessize=3;
    for(int i=0;i<AllDatessize;i++)
    {
         if(AllDates[i].getSDay()==date)
         {
            AllDates[i].getSDay().Display();
            cout<<t<<endl;
            thisdate[t++].date=AllDates[i];
            //day[t-1].getSDay().Display();
            int S=thisdate[t-1].date.getSTime().getH();
            thisdate[t-1].row=S;
            int L=thisdate[t-1].date.getETime().getH()-S;
            //cout<<S<<L<<endl;
            ui->tableWidget_list->setSpan(S,1,L,1);//(S,1) is the start cell,L is number of contain row
            ui->tableWidget_list->setItem(S,1,new QTableWidgetItem(QString::fromStdString(thisdate[t-1].date.getTitle())));
         }
    }

    //ui->tableWidget_list->setSpan(3,1,2,1);
    //ui->tableWidget_list->setItem(3,1,new QTableWidgetItem(QString("sblrtljlkjlkjlkjlkjlklkjkllllllllllllllllllllllllllllllllllllllllllllllll")));
    QHeaderView* headerView =ui->tableWidget_list->verticalHeader();
    headerView->setHidden(true);
    QWidget *widget=ui->tableWidget_list->cellWidget(0,0);
    QLabel *combox=(QLabel*)widget;
    //ui->tableWidget_list->resizeRowsToContents();
    int temp=ui->tableWidget_list->rowHeight(0);
    ui->tableWidget_list->setRowHeight(1,temp);
}


void DayDialog::on_pushButton_Next_clicked()
{
    memset(thisdate,0,sizeof(thisdate));
    QDate datetemp(date.getYear(),date.getMonth(),date.getDay());
    datetemp=datetemp.addDays(1);
    date=DateTime(datetemp.year(),datetemp.month(),datetemp.day());
    ui->tableWidget_list->clear();
    for(int i=0;i<24;i++)
        ui->tableWidget_list->setSpan(i,1,1,1);
    load();
}

void DayDialog::on_pushButton_Previous_clicked()
{
    memset(thisdate,0,sizeof(thisdate));
    QDate datetemp(date.getYear(),date.getMonth(),date.getDay());
    datetemp=datetemp.addDays(-1);
    date=DateTime(datetemp.year(),datetemp.month(),datetemp.day());
    ui->tableWidget_list->clear();
    for(int i=0;i<24;i++)
        ui->tableWidget_list->setSpan(i,1,1,1);
    load();
}
