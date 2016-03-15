#include "dialog_save.h"
#include "ui_dialog_save.h"
#include "ShowNowTime.h"
#include "remind.h"
#include "FileIO.h"

Dialog_save::Dialog_save(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_save)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate(ShowNowTime::getYear(),ShowNowTime::getMonth(),ShowNowTime::getDay()));
    ui->dateEdit_2->setDate(QDate(ShowNowTime::getYear(),ShowNowTime::getMonth(),ShowNowTime::getDay()));
    ui->timeEdit->setTime(QTime(ShowNowTime::getHour(),ShowNowTime::getMinite(),ShowNowTime::getSecond()));
    ui->timeEdit_2->setTime(QTime(ShowNowTime::getHour(),ShowNowTime::getMinite(),ShowNowTime::getSecond()));
    QTime remindtime=QTime(ShowNowTime::getHour(),ShowNowTime::getMinite(),ShowNowTime::getSecond());
    remindtime=remindtime.addSecs(-900);
    ui->timeEdit_3->setTime(remindtime);
    ui->checkBox_2->setChecked(true);

}

Dialog_save::Dialog_save(QDate* tmpdate,QTime* tmptime,QWidget *parent):
    QDialog(parent),
    ui(new Ui::Dialog_save)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(*tmpdate);
    ui->dateEdit_2->setDate(*tmpdate);
    ui->timeEdit->setTime(*tmptime);
    ui->timeEdit_2->setTime(tmptime->addSecs(3599));
    ui->timeEdit_3->setTime(tmptime->addSecs(-900));
    ui->checkBox_2->setChecked(true);
}


Dialog_save::~Dialog_save()
{
    delete ui;
}

void Dialog_save::getInfo(Date* in)
{
    dates=in;
    //cout<<"getinfo::"<<dates->dateNum()<<endl;
}

void Dialog_save::on_pushButton_clicked()
{
    DateTime testday=DateTime(ui->dateEdit->date().year(),ui->dateEdit->date().month(),ui->dateEdit->date().day());
    DayTime testStime=DayTime(ui->timeEdit->time().hour(),ui->timeEdit->time().minute(),ui->timeEdit->time().second());
    DayTime testEtime=DayTime(ui->timeEdit_2->time().hour(),ui->timeEdit_2->time().minute(),ui->timeEdit_2->time().second());
    if(!Search::searchDaytime(testday,testStime,testEtime,dates))
    {
        int now=dates->dateNum();
        //cout<<"now in save::"<<now<<endl;
        dates->setDateNum(now+1);
        //cout<<"india:"<<dates->dateNum()<<endl;
        (dates+now)->setTitle(ui->lineEdit->text().toStdString());
        (dates+now)->setLocation(ui->lineEdit_2->text().toStdString());
        (dates+now)->setSTime(ui->timeEdit->time().hour(),ui->timeEdit->time().minute(),ui->timeEdit->time().second());
        (dates+now)->setSDay(ui->dateEdit->date().year(),ui->dateEdit->date().month(),ui->dateEdit->date().day());
        (dates+now)->setETime(ui->timeEdit_2->time().hour(),ui->timeEdit_2->time().minute(),ui->timeEdit_2->time().second());
        (dates+now)->setEDay(ui->dateEdit_2->date().year(),ui->dateEdit_2->date().month(),ui->dateEdit_2->date().day());
        (dates+now)->setRemindTime(DayTime(ui->timeEdit_3->time().hour(),ui->timeEdit_3->time().minute(),ui->timeEdit_3->time().second()));
        (dates+now)->setPS(ui->textEdit->toPlainText().toStdString());
        (dates+now)->setImportant(ui->checkBox->isChecked());
        (dates+now)->setRemind(ui->checkBox_2->isChecked());
        (dates+now)->setIsdone(ui->checkBox_3->isChecked());
        this ->setLoopdate(dates+now);
        //cout<<"now is "<<now<<endl;
        FileIO::writeToFile(dates,"/home/rainto96/Qtprogram/table/mem.dat");
        //Remind::setTimeClock_Today(dates);
   this->close();
    }
    else
    {
        QMessageBox messagebox(QMessageBox::Warning,tr("information"),tr("there is a time confict"),QMessageBox::Ok,NULL);
        messagebox.exec();
    }
}

void Dialog_save::setLoopdate(Date* datedemo)
{
    int AllDatessize=dates[0].dateNum();
    if(datedemo->getLoop().get_loopLength().getDay()!=0)
    {
        int length=datedemo->getLoop().get_loopLength().getDay();
        for(QDate datetempS=datedemo->getLoop().get_Start_DateTime().toQDate();
            datetempS<=datedemo->getLoop().get_End_DateTime().toQDate();
            datetempS=datetempS.addDays(length))
        {
            AllDatessize++;
            dates[AllDatessize-1]=*datedemo;
            dates[AllDatessize-1].getSDay().QDatetoDate(datetempS);
            dates[AllDatessize-1].getEDay().QDatetoDate(datetempS);
        }
    }
   else if(datedemo->getLoop().get_loopLength().getMonth()!=0)
    {
        int length=datedemo->getLoop().get_loopLength().getMonth();
        for(QDate datetempS=datedemo->getLoop().get_Start_DateTime().toQDate();
            datetempS<=datedemo->getLoop().get_End_DateTime().toQDate();
            datetempS=datetempS.addMonths(length))
        {
            AllDatessize++;
            dates[AllDatessize-1]=*datedemo;
            dates[AllDatessize-1].getSDay().QDatetoDate(datetempS);
            dates[AllDatessize-1].getEDay().QDatetoDate(datetempS);
        }
    }
    dates[0].setDateNum(AllDatessize);

}


void Dialog_save::on_pushButton_ChooseLoop_clicked()
{
    int now=dates->dateNum();
    //cout<<"india:"<<dates->dateNum()<<endl;
    (dates+now)->setTitle(ui->lineEdit->text().toStdString());
    (dates+now)->setLocation(ui->lineEdit_2->text().toStdString());
    //(dates+now)->setSTime(ui->timeEdit->time().hour(),ui->timeEdit->time().minute(),ui->timeEdit->time().second());
    //(dates+now)->setSDay(ui->dateEdit->date().year(),ui->dateEdit->date().month(),ui->dateEdit->date().day());
  //  (dates+now)->setETime(ui->timeEdit_2->time().hour(),ui->timeEdit_2->time().minute(),ui->timeEdit_2->time().second());
    //(dates+now)->setETime(5,0,0);
    //(dates+now)->setEDay(ui->dateEdit_2->date().year(),ui->dateEdit_2->date().month(),ui->dateEdit_2->date().day());
    (dates+now)->setPS(ui->textEdit->toPlainText().toStdString());
    dialog_loop.getInfo(dates+now);
    dialog_loop.exec();
}
