#include "weekdialog.h"
#include "ui_weekdialog.h"
#include "remind.h"
#include <QTimer>
#include <QPainter>
#include "dialog_edit.h"
using namespace std;
map<pair<int,int>,int>mapToDate;
WeekDialog::WeekDialog(Date* in_week,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WeekDialog)
{
    ui->setupUi(this);
    AllDates=in_week;
    //cout<<"in weekdialog is::"<<AllDates->dateNum()<<endl;
    QLabel *labelq = new QLabel;
    labelq->setPixmap(QPixmap(":/images/flag.png"));
    ui->tableWidget->setCellWidget(0, 0, labelq);
    /************set TIME CLOCK*************/
    /*Remind *t=new Remind[25];
    Date* todayDate=new Date[25];
    todayDate->setDateNum(0);
    DateTime today(ShowNowTime::getYear(),ShowNowTime::getMonth(),ShowNowTime::getDay());
    Search::searchDateTime(today,today,todayDate,AllDates);
    for(int i=1;i<=todayDate->dateNum();i++)
    {
        DayTime time=todayDate[i].getSTime();
        (t+i)->setRemindTime(DayTime(time.getH(),time.getM(),time.getS()));
        (t+i)->setDate(todayDate+i);
    }
    QTimer *time_clock=new QTimer(t);
    for(int i=1;i<=todayDate->dateNum();i++)
        QObject::connect(time_clock,SIGNAL(timeout()),t+i,SLOT(checkPlaySound()));
    time_clock->start(1);
    //cout<<todayDate->dateNum()<<endl;*/
    FileIO::readFromFile(AllDates,"/home/rainto96/Qtprogram/table/mem.dat",999);
    //Remind::setTimeClock_Today(AllDates);

    /************set TIME CLOCK*************/
    setBeautiful();
    spinbox_ShowToday();
    setLabelPointer();
    setWeekDay(getSpinboxesDate());
    showCurrentDate();
    /*Date test;
    test.setTitle("sbyqp");
    test.setSDay(2014,7,5);
    test.setEDay(2014,7,5);
    test.setSTime(22,00,00);
    test.setSTime(23,00,00);
    pushToTable(test);*/

    /*QDate d1(2014,6,30);
    QDate d2(2014,7,6);
    cout<<"lookhere"<<endl;
    cout<<d1.weekNumber()<<endl;
    cout<<d2.weekNumber()<<endl;*/
}

WeekDialog::~WeekDialog()
{
    delete ui;
    delete AllDates;
}
void WeekDialog::setBackground()
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
}
void WeekDialog::setBeautiful()
{
    setBackground();

    QPalette pal;
    pal.setColor(QPalette::ButtonText, QColor(255,255,255));
    ui->button_LastWeek->setPalette(pal);
    ui->button_nextWeek->setPalette(pal);
    ui->button_Newdate->setPalette(pal);
    ui->pushButton->setPalette(pal);
    ui->button_LastWeek->setStyleSheet("border:2px green;border-radius:10px;padding:2px 2px;background:rgb(124,250,0)");
    ui->button_nextWeek->setStyleSheet("border:2px green;border-radius:10px;padding:2px 2px;background:rgb(124,250,0)");
    ui->button_Newdate->setStyleSheet("border:2px green;border-radius:10px;padding:2px 2px;background:rgb(124,250,0)");
     ui->pushButton->setStyleSheet("border:2px green;border-radius:10px;padding:2px 2px;background:rgb(124,250,0)");
    int width=100*1.7;int height=62*0.6;
    for(int i=0;i<=6;i++)
        ui->tableWidget->setColumnWidth(i,width);
    for(int i=0;i<=23;i++)
        ui->tableWidget->setRowHeight(i,height);
    ui->tableWidget->setStyleSheet("border:2px #FFFFCD;border-radius:10px;padding:2px 2px;background:#FFFFCD");
}
void WeekDialog::setLabelPointer()
{
    //set labels
    pLblWeek[1]=ui->label_Mon;
    pLblWeek[2]=ui->label_Tue;
    pLblWeek[3]=ui->label_Wed;
    pLblWeek[4]=ui->label_Thu;
    pLblWeek[5]=ui->label_Fri;
    pLblWeek[6]=ui->label_Sat;
    pLblWeek[7]=ui->label_Sun;
    for(int i=1;i<=7;i++)
    {
        pLblWeek[i]->setAlignment(Qt::AlignCenter);
    }
}
void WeekDialog::spinbox_ShowToday()
{
    //display today
    ui->spinBox_Year->setValue(ShowNowTime::getYear());
    ui->spinBox_Month->setValue(ShowNowTime::getMonth());
    ui->spinBox_Day->setValue(ShowNowTime::getDay());
}
void WeekDialog::setWeekDay(QDate day)
{
    QDate daytmp=day;
    int today_weekday=day.dayOfWeek();
    for(int i=today_weekday;i<=7;i++)
    {
        pLblWeek[i]->setText(QString::number(daytmp.day()));
        daytmp=daytmp.addDays(1);
    }
    for(int i=today_weekday;i>=1;i--)
    {
        //cout<<i<<endl;
        pLblWeek[i]->setText(QString::number(day.day()));
        day=day.addDays(-1);
    }
}

QDate WeekDialog::getSpinboxesDate()
{
    int year=ui->spinBox_Year->value();
    int month=ui->spinBox_Month->value();
    int day=ui->spinBox_Day->value();
    return QDate(year,month,day);
}

void WeekDialog::showCurrentDate()
{
    int index[999];
    int num=0;
    Date* save=new Date[999];
    QDate currentDate=getSpinboxesDate();
    int weeknum=currentDate.weekNumber();
    for(int i=1;i<=AllDates->dateNum();i++)
    {
        QDate tmp=QDate(AllDates[i].getSDay().getYear(),AllDates[i].getSDay().getMonth(),AllDates[i].getSDay().getDay());
        if(i==97)
        {
            //cout<<"my tmp"<<i<<" is"<<tmp.year()<<'/'<<tmp.month()<<'/'<<tmp.day()<<endl;
            //cout<<AllDates[i].getTitle()<<endl;
            //cout<<tmp.weekNumber()<<endl;
            //cout<<weeknum<<endl;
        }
        if(tmp.weekNumber()==weeknum)
        {

            index[num]=i;
            save[num]=AllDates[i];
            if(i==97)
            {
                //cout<<"5indexis::"<<index[num]<<endl;
                //cout<<num<<endl;
            }
            num++;
        }
    }
    save->setDateNum(num);
    //cout<<"nicemy ass::"<<save->dateNum()<<endl;
    for(int i=0;i<save->dateNum();i++)
    {
        pushToTable(save[i],index[i]);
        //cout<<"start"<<endl;
        if(i==31)
        {
            //cout<<save[i].getSTime().show()<<endl;
            //cout<<"31:::"<<save[i].getTitle()<<endl;
            //cout<<index[i]<<endl;
            //cout<<save[i].getETime().show()<<endl;
        }
    }
    delete save;
}
void WeekDialog::pushToTable(Date& adate,int index)
{
    int rowstart=adate.getSTime().getH();
    int rowend=adate.getETime().getH();
    //cout<<"lookrowend::"<<rowend<<endl;
    ui->tableWidget->setSpan(rowstart,adate.getSDay().getWeek()-1,rowend-rowstart,1);
//    if(index==99)
//    {
//        //cout<<"99hasbeen"<<endl;
//        //cout<<rowstart<<endl;
//        //cout<<adate.getSDay().getWeek()-1<<endl;
//        //cout<<label->text().toStdString()<<endl;
//        //cout<<adate.getSDay().show()<<endl;
//        //cout<<adate.getEDay().show()<<endl;
//        //cout<<adate.getTitle()<<endl;
//        //cout<<"end"<<endl;
//    }
    if(adate.getSDay()==adate.getEDay())
    {
        QLabel* label=new QLabel;
        QString res;
        //if(adate.isDone())
            //res=QString("<u>")+QString::fromStdString(adate.getTitle())+QString("</u>");
        //else
            res=QString::fromStdString(adate.getTitle());
        label->setText(res);
        if(adate.isImportant()&&adate.isDone())
            label->setStyleSheet("text-decoration:line-through;font: bold large;font-size:16px;color:white;background-color: #FF0000;");
        else if(adate.isImportant())
            label->setStyleSheet("font: bold large ;s:true;font-weight:11px;font-size:16px;color:white;background-color: #FF0000;");
        else if(adate.isDone())
            label->setStyleSheet("text-decoration:line-through;font: bold large ;s:true;font-weight:11px;font-size:16px;color:white;background-color: #FFD700;");
        else
            label->setStyleSheet("font: bold large ;s:true;font-weight:11px;font-size:16px;color:white;background-color: #FFD700;");

        ui->tableWidget->setCellWidget(rowstart,adate.getSDay().getWeek()-1,label);

        pair<int,int >p1(rowstart,adate.getSDay().getWeek()-1);
        mapToDate[p1]=index;
    }

}

void WeekDialog::cancelSpan()
{
    for(int i=0;i<=23;i++)
        for(int j=0;j<=6;j++)
            ui->tableWidget->setSpan(i, j, 1, 1);
}

void WeekDialog::on_tableWidget_cellClicked(int row, int column)
{
    //cout<<row<<' '<<column<<endl;
    map<pair<int,int>,int>::iterator it;
    pair<int,int >p1(row,column);
    it=mapToDate.find(p1);
    if(it!=mapToDate.end())
    {
        /*cout<<"mapis"<<endl;
        cout<<mapToDate.at(p1)<<endl;
        cout<<"---"<<endl;*/
        Dialog_edit* dialog_edit=new Dialog_edit(AllDates,mapToDate.at(p1));
        dialog_edit->exec();
        //delete dialog_edit;
        showCurrentDate();
        //FileIO::writeToFile(AllDates,"/home/rainto96/THISISMY/mem/mes.dat");
    }
    else
    {
        QDate* spinDate=new QDate;
        *spinDate=getSpinboxesDate();
        QTime* tmpqtime=new QTime(row,0,0);
        int week_num_spin=spinDate->dayOfWeek();
        QDate clickDay=spinDate->addDays(-(week_num_spin-(column+1)));
        dialog_save=new Dialog_save(&clickDay,tmpqtime);
        dialog_save->getInfo(AllDates);
        dialog_save->exec();
        showCurrentDate();
        delete dialog_save;
    }
}


void WeekDialog::on_button_Newdate_clicked()
{
    dialog_save=new Dialog_save();
    dialog_save->getInfo(AllDates);
    dialog_save->exec();
    delete dialog_save;
    showCurrentDate();
    //FileIO::writeToFile(AllDates,"/home/rainto96/THISISMY/mem/mes.dat");
}

void WeekDialog::setSpinboxesDate(QDate& date)
{
    ui->spinBox_Year->setValue(date.year());
    ui->spinBox_Month->setValue(date.month());
    ui->spinBox_Day->setValue(date.day());
}

void WeekDialog::on_button_LastWeek_clicked()
{
    cancelSpan();
    ui->tableWidget->clearContents();
    QDate date=getSpinboxesDate();
    date=date.addDays(-7);
    setSpinboxesDate(date);
    setWeekDay(date);
    showCurrentDate();
}

void WeekDialog::on_button_nextWeek_clicked()
{
    cancelSpan();
    ui->tableWidget->clearContents();
    QDate date=getSpinboxesDate();
    date=date.addDays(7);
    setSpinboxesDate(date);
    setWeekDay(date);
    showCurrentDate();
}

void WeekDialog::getInfo(Date *dates)
{
    this->AllDates=dates;
}

void WeekDialog::on_pushButton_clicked()
{
    this->close();
}
