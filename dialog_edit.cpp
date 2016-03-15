#include "remind.h"
#include "dialog_edit.h"
#include "ui_dialog_edit.h"
#include "date.h"
#include "ShowNowTime.h"
#include <QDate>
#include <cstdio>
#include "FileIO.h"
Dialog_edit::Dialog_edit(Date* AllDates,int index,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_edit)
{
    ui->setupUi(this);
    this->index=index;
    dates=AllDates;

    ui->pushButton_4->setStyleSheet("background:green");
    ui->pushButton->setStyleSheet("background:green");

    ui->lineEdit->setText(QString::fromStdString((dates+index)->getTitle()));
    ui->lineEdit_2->setText(QString::fromStdString((dates+index)->getLocation()));
    ui->dateEdit->setDate(QDate((dates+index)->getSDay().getYear(),(dates+index)->getSDay().getMonth(),(dates+index)->getSDay().getDay()));
    ui->dateEdit_2->setDate(QDate((dates+index)->getSDay().getYear(),(dates+index)->getSDay().getMonth(),(dates+index)->getSDay().getDay()));
    ui->timeEdit->setTime(QTime((dates+index)->getSTime().getH(),(dates+index)->getSTime().getM(),(dates+index)->getSTime().getS()));
    ui->timeEdit_2->setTime(QTime((dates+index)->getETime().getH(),(dates+index)->getETime().getM(),(dates+index)->getETime().getS()));
    ui->timeEdit_3->setTime(QTime((dates+index)->getRemindTime().getH(),(dates+index)->getRemindTime().getM(),(dates+index)->getRemindTime().getS()));
    ui->textEdit->setText(QString::fromStdString((dates+index)->getText()));
    ui->checkBox->setChecked((dates+index)->isImportant());
    ui->checkBox_2->setChecked((dates+index)->NeedRemind());
    ui->checkBox_3->setChecked((dates+index)->isDone());
    /*ui->timeEdit->setTime(QTime(ShowNowTime::getHour(),ShowNowTime::getMinite(),ShowNowTime::getSecond()));
    ui->timeEdit_2->setTime(QTime(ShowNowTime::getHour()+1,ShowNowTime::getMinite(),ShowNowTime::getSecond()));
    ui->dateEdit->setDate(QDate(ShowNowTime::getYear(),ShowNowTime::getMonth(),ShowNowTime::getDay()));
    ui->dateEdit_2->setDate(QDate(ShowNowTime::getYear(),ShowNowTime::getMonth(),ShowNowTime::getDay()));*/
}

Dialog_edit::~Dialog_edit()
{
    delete ui;
}


void Dialog_edit::on_pushButton_clicked()
{
    DateTime testday=DateTime(ui->dateEdit->date().year(),ui->dateEdit->date().month(),ui->dateEdit->date().day());
    DayTime testStime=DayTime(ui->timeEdit->time().hour(),ui->timeEdit->time().minute(),ui->timeEdit->time().second());
    DayTime testEtime=DayTime(ui->timeEdit_2->time().hour(),ui->timeEdit_2->time().minute(),ui->timeEdit_2->time().second());
    if(!Search::searchDaytime_edit(testday,testStime,testEtime,dates,index))
    {
       (dates+index)->setTitle(ui->lineEdit->text().toStdString());
       (dates+index)->setLocation(ui->lineEdit_2->text().toStdString());
       (dates+index)->setSTime(ui->timeEdit->time().hour(),ui->timeEdit->time().minute(),ui->timeEdit->time().second());
       (dates+index)->setSDay(ui->dateEdit->date().year(),ui->dateEdit->date().month(),ui->dateEdit->date().day());
       (dates+index)->setETime(ui->timeEdit_2->time().hour(),ui->timeEdit_2->time().minute(),ui->timeEdit_2->time().second());
       (dates+index)->setEDay(ui->dateEdit_2->date().year(),ui->dateEdit_2->date().month(),ui->dateEdit_2->date().day());
       (dates+index)->setRemindTime(DayTime(ui->timeEdit_3->time().hour(),ui->timeEdit_3->time().minute(),ui->timeEdit_3->time().second()));
       (dates+index)->setPS(ui->textEdit->toPlainText().toStdString());
       (dates+index)->setImportant(ui->checkBox->isChecked());
       (dates+index)->setRemind(ui->checkBox_2->isChecked());
       (dates+index)->setIsdone(ui->checkBox_3->isChecked());
        FileIO::writeToFile(dates,"/home/rainto96/Qtprogram/table/mem.dat");
        Remind::setTimeClock_Today(dates);
       this->close();
    }
    else
    {
        QMessageBox messagebox(QMessageBox::Warning,tr("information"),tr("there is a time confict"),QMessageBox::Ok,NULL);
        messagebox.exec();
    }
}


void Dialog_edit::on_pushButton_4_clicked()
{
    int now=dates->dateNum();
    dialog_loop=new Dialog_loop;
    dialog_loop->getInfo(dates+now);
    dialog_loop->exec();
    delete dialog_loop;
}
