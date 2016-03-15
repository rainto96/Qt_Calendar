#include "dialog_search.h"
#include "ui_dialog_search.h"
#include "datetime.h"
#include "daytime.h"
#include <QPalette>
Dialog_search::Dialog_search(Date* in,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_search)
{
    ui->setupUi(this);
    AllDates=in;
    QPalette pal;
    pal.setColor(QPalette::ButtonText, QColor(255,250,240));
    //this->setPalette(pal);
     ui->pushButton->setPalette(pal);
     pal.setColor(QPalette::ButtonText, QColor(255,255,255));
      ui->pushButton->setStyleSheet("border:2px green;border-radius:10px;padding:2px 2px;background:rgb(124,250,0)");
      QDate Today(ShowNowTime::getYear(),ShowNowTime::getMonth(),ShowNowTime::getDay());
      ui->dateEdit->setDate(Today);
      ui->dateEdit_2->setDate(Today);
    /*AllDates[0].setDateNum(4);

    AllDates[1].setTitle("watch movie");
    AllDates[1].setLocation("wanda theater");
    AllDates[1].setSTime(15,0,0);
    AllDates[1].setETime(16,30,0);
    AllDates[1].setSDay(2014,7,8);
    AllDates[1].setEDay(2014,7,8);
    AllDates[1].setImportant(true);

    AllDates[2].setTitle("date");
    AllDates[2].setLocation("country");
    AllDates[2].setSTime(8,0,0);
    AllDates[2].setETime(20,0,0);
    AllDates[2].setSDay(2014,6,2);
    AllDates[2].setEDay(2014,6,2);
    AllDates[2].setImportant(false);

    AllDates[3].setTitle("camping");
    AllDates[3].setLocation("park");
    AllDates[3].setSTime(18,0,0);
    AllDates[3].setETime(8,0,0);
    AllDates[3].setSDay(2012,12,20);
    AllDates[3].setEDay(2012,12,21);
    AllDates[3].setImportant(false);

    AllDates[4].setTitle("a business travel");
    AllDates[4].setLocation("Shanghai");
    AllDates[4].setSTime(13,0,0);
    AllDates[4].setETime(8,0,0);
    AllDates[4].setSDay(2011,9,28);
    AllDates[4].setEDay(2011,10,1);
    AllDates[4].setImportant(true);*/
}
Dialog_search::~Dialog_search()
{
    delete ui;
}

void Dialog_search::on_comboBox_currentIndexChanged(int index)//当下拉框选单发生变化时，堆窗口控件显示相应的页面
{
    if(index==0)
    {
    ui->stackedWidget->setCurrentIndex(0);
    }
    else if(index==1)
    {
     ui->stackedWidget->setCurrentIndex(1);
    }
    else if(index==2)
    {
     ui->stackedWidget->setCurrentIndex(2);
    }
    else if(index==3)
    {
    ui->stackedWidget->setCurrentIndex(3);
    }
}


void Dialog_search::on_radioButton_2_clicked()//当用户选择YES时，isimpotant的值变为true
{
    isimportant=true;
}



void Dialog_search::on_pushButton_clicked()//当search按钮被点击时，根据用户的搜索方式进行搜索并在右边的表格中显示出搜索结果
{
    ui->tableWidget->clearContents();

    if(ui->comboBox->currentIndex()==0)
      {
        search.searchTitle(ui->lineEdit->text().toStdString(),result,AllDates);
      }


    if(ui->comboBox->currentIndex()==1)
    {
        search.searchLocation(ui->lineEdit_2->text().toStdString(),result,AllDates);
    }


    if(ui->comboBox->currentIndex()==2)
    {
        startdate.SetDate(ui->dateEdit->date().year(),ui->dateEdit->date().month(),ui->dateEdit->date().day());
        enddate.SetDate(ui->dateEdit_2->date().year(),ui->dateEdit_2->date().month(),ui->dateEdit_2->date().day());
        search.searchDateTime(startdate,enddate,result,AllDates);
    }
    if(ui->comboBox->currentIndex()==3&&isimportant)
    {

        search.searchImportant(isimportant,result,AllDates);
    }


    for(int i=1;i<=result[0].dateNum();i++)
    {
        QLabel *title=new QLabel;
        QLabel *location=new QLabel;
        QLabel *startdate=new QLabel;
        QLabel *enddate=new QLabel;
        QLabel *starttime=new QLabel;
        QLabel *endtime=new QLabel;
        title->setText(QString::fromStdString(result[i].getTitle()));
        location->setText(QString::fromStdString(result[i].getLocation()));
        startdate->setText(QString::fromStdString(result[i].getSDay().show()));
        enddate->setText(QString::fromStdString(result[i].getEDay().show()));
        starttime->setText(QString::fromStdString(result[i].getSTime().show()));
        endtime->setText(QString::fromStdString(result[i].getETime().show()));
        ui->tableWidget->setColumnWidth(i-1,100);
        ui->tableWidget->setCellWidget(i-1,0,title);
        ui->tableWidget->setCellWidget(i-1,1,location);
        ui->tableWidget->setCellWidget(i-1,2,startdate);
        ui->tableWidget->setCellWidget(i-1,3,enddate);
        ui->tableWidget->setCellWidget(i-1,4,starttime);
        ui->tableWidget->setCellWidget(i-1,5,endtime);
    }
}



