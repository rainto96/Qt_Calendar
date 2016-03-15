//日视图的cpp文件，包含每个函数的实现

#include "daydialog.h"
#include "ui_daydialog.h"
#include <QLabel>
#include <QDebug>
#include <QCloseEvent>
#include "ShowNowTime.h"



DayDialog::DayDialog(Date* in_day,QWidget *parent) :////构造函数，
    QDialog(parent),
    ui(new Ui::DayDialog)
{
    ui->setupUi(this);
    AllDates=in_day;//接受上一级视图传进来的（可修改的）所有事件的数组指针，
    //cout<<"in daydialog is::"<<AllDates->dateNum()<<endl;
    setBackground();
//构造时默认显示当前时间
    int daytemp=ShowNowTime::getDay();
    int monthtemp=ShowNowTime::getMonth();
    int yeartemp=ShowNowTime::getYear();
    date=DateTime(yeartemp,monthtemp,daytemp);
    AllDatessize=AllDates[0].dateNum();

    ui->timeEdit_Etime->setTime(QTime(ShowNowTime::getHour(),ShowNowTime::getMinite(),ShowNowTime::getSecond()));
    ui->timeEdit_Stime->setTime(QTime(ShowNowTime::getHour(),ShowNowTime::getMinite(),ShowNowTime::getSecond()));
    showdate.index=-1;
    load();//载入tablewidget及其他部件的函数
}

DayDialog::~DayDialog()//析构函数
{
    delete ui;
}
bool DayDialog::searchDate(int row,Date& D)//row为该事件在tablewidget中的行数，D存储查找到的事件
{
    for(int i=0;i<t;i++)
    {
        if(thisdate[i].row==row)//tristate为结构体，定义声明均在头文件中，包含一个事件及其在AllDates中的下标以及在当天的tablewidget中的行数
        {
            D=thisdate[i].date;
            showdate=thisdate[i];
            return true;
        }
    }
    return false;
}

void DayDialog::on_tableWidget_list_cellClicked(int row, int column)//tablewidget中每一个格子点击的槽函数，用于在左边的预览窗显示相应的时间内容
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

void DayDialog::on_pushButton_Edit_clicked()//新建约会的按钮点击的槽函数
{
    dialog_save.getInfo(AllDates);
    dialog_save.exec();
    AllDatessize=AllDates[0].dateNum();
    load();
}
Date* DayDialog::getAllDates()//从上一视图中获取AllDates的获取信息函数
{
    return AllDates;
}


string DayDialog::checkmonth(DateTime date)//查找当前天代表的月份的英文string
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

string DayDialog::checkweek(int a )//查找当天代表的星期的英文string
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

void DayDialog::load()//重新载入tablewidget部件的显示内容，用于每次添加，编辑之后的实时显示事件
{
    t=0;

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
            //cout<<t<<endl;
            thisdate[t++].date=AllDates[i];
            //day[t-1].getSDay().Display();
            int S=thisdate[t-1].date.getSTime().getH();
            thisdate[t-1].row=S;
            thisdate[t-1].index=i;
            int L=thisdate[t-1].date.getETime().getH()-S;
            //cout<<S<<L<<endl;
            ui->tableWidget_list->setSpan(S,1,L,1);//(S,1) is the start cell,L is number of contain row
           // ui->tableWidget_list->setItem(S,1,new QTableWidgetItem(QString::fromStdString(thisdate[t-1].date.getTitle())));




             int rowstart=thisdate[t-1].row;
              QLabel* label=new QLabel;
              QString res;
              //if(adate.isDone())
                  //res=QString("<u>")+QString::fromStdString(adate.getTitle())+QString("</u>");
              //else
                  res=QString::fromStdString(thisdate[t-1].date.getTitle());
              label->setText(res);
              if(thisdate[t-1].date.isImportant()&&thisdate[t-1].date.isDone())
                  label->setStyleSheet("text-decoration:line-through;font: bold large;font-size:16px;color:white;background-color: #FF0000;");
              else if(thisdate[t-1].date.isImportant())
                  label->setStyleSheet("font: bold large ;s:true;font-weight:11px;font-size:16px;color:white;background-color: #FF0000;");
              else if(thisdate[t-1].date.isDone())
                  label->setStyleSheet("text-decoration:line-through;font: bold large ;s:true;font-weight:11px;font-size:16px;color:white;background-color: #FFD700;");
              else
                  label->setStyleSheet("font: bold large ;s:true;font-weight:11px;font-size:16px;color:white;background-color: #FFD700;");

              ui->tableWidget_list->setCellWidget(rowstart,1,label);





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


void DayDialog::on_pushButton_Next_clicked()//next day 按钮点击的槽函数，初始化thisdate数组，将tablewidget复原并重新载入当天内容，
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

void DayDialog::on_pushButton_Previous_clicked()//previous day 按钮点击的槽函数
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
void DayDialog::setBackground()
{
    /*QImage image1;
    image1.load("background.jpg");    //括号内为图片的相对目录
    QImage image2 = image1.scaled(320,240);
    QPalette palette;
    palette.setBrush(this->backgroundRole(),QBrush(image2));
    this->setPalette(palette);*/
    QPalette pal;
    pal.setColor(QPalette::ButtonText, QColor(255,250,240));
    this->setPalette(pal);
    int width=100;int height=62;
    ui->tableWidget_list->setColumnWidth(0,width);
    for(int i=0;i<=23;i++)
        ui->tableWidget_list->setRowHeight(i,height);
    ui->tableWidget_list->setStyleSheet("border:2px #FFFFCD;border-radius:10px;padding:2px 2px;background:#FFFFCD");

    pal.setColor(QPalette::ButtonText, QColor(255,255,255));
    ui->pushButton_Previous->setPalette(pal);
    ui->pushButton_Next->setPalette(pal);
    ui->pushButton_Edit->setPalette(pal);
    ui->pushButton->setPalette(pal);
    ui->pushButton_2->setPalette(pal);

    ui->pushButton_Previous->setStyleSheet("border:2px green;border-radius:10px;padding:2px 2px;background:rgb(124,250,0)");
    ui->pushButton_Next->setStyleSheet("border:2px green;border-radius:10px;padding:2px 2px;background:rgb(124,250,0)");
    ui->pushButton_Edit->setStyleSheet("border:2px green;border-radius:10px;padding:2px 2px;background:rgb(124,250,0)");
    ui->pushButton->setStyleSheet("border:2px green;border-radius:10px;padding:2px 2px;background:rgb(124,250,0)");
    ui->pushButton_2->setStyleSheet("border:2px green;border-radius:10px;padding:2px 2px;background:rgb(124,250,0)");

}

void DayDialog::getInfo(Date *dates)//从上一视图获取AllDates数组
{
    this->AllDates=dates;
}

void DayDialog::on_pushButton_clicked()//“back to mianwindow”按钮点击的槽函数，将此窗口关闭，显示主窗口
{
    this->close();
}

void DayDialog::on_pushButton_2_clicked()//编辑当前事件的按钮点击的槽函数，不在AllDates数组末尾追加事件，直接修改当前事件
{
    //yqp, please get index_______________________________________________________
    if(showdate.index!=-1)
    {
        int index=showdate.index;
        dialog_edit=new Dialog_edit(AllDates,index);
        dialog_edit->exec();
        load();
        on_tableWidget_list_cellClicked(AllDates[index].getSTime().getH(),1);
    }
}
