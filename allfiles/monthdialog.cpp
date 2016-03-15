#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "FileIO.h"
#include "remind.h"
#include "dialog_edit.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    AllDates=new Date[999];
    /*AllDates[0].setDateNum(2);

    AllDates[1].setTitle("watch movie");
    AllDates[1].setLocation("wanda theater");
    AllDates[1].setSTime(15,0,0);
    AllDates[1].setETime(16,30,0);
    AllDates[1].setSDay(2014,7,8);
    AllDates[1].setEDay(2014,7,8);
    AllDates[1].setPS("I will go to movie with classmates at wanda theater on 2014.7.8");

    AllDates[2].setTitle("date");
    AllDates[2].setLocation("country");
    AllDates[2].setSTime(8,0,0);
    AllDates[2].setETime(20,0,0);
    AllDates[2].setSDay(2014,5,2);
    AllDates[2].setEDay(2014,5,2);
    AllDates[2].setPS("I have a date with girlfriend to country on 2014,6,2");*/



    FileIO::readFromFile(AllDates,"/home/rainto96/THISISMY/mem/mes.dat",999);
    //cout<<AllDates->dateNum()<<"here";
    Remind::setTimeClock_Today(AllDates);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    for(int i=0;i<7;i++)
    {
        ui->tableWidget->setColumnWidth(i,70);
    }
    for(int i=0;i<6;i++)
    {
        ui->tableWidget->setRowHeight(i,70);
    }
    QDate month(CurrentTime.getYear(),CurrentTime.getMonth(),1);
    DateTime lastday(CurrentTime.getYear(),CurrentTime.getMonth(),month.daysInMonth());
    DateTime firstday(CurrentTime.getYear(),CurrentTime.getMonth(),1);
    FindToday();

    Search::searchDateTime(firstday,lastday,special,AllDates);
    MarkSticker(special);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->tableWidget->clearContents();
    time.SetDate(ui->lineEdit->text().toInt(),(ui->lineEdit_2->text().toInt()+1),1);
    ui->lineEdit_2->setText(QString::number(time.getMonth(),10));
    if(time.getMonth()>12)
    {
        time.SetDate((ui->lineEdit->text().toInt()+1),1,1);

        ui->lineEdit_2->setText(QString::number(1,10));
        ui->lineEdit->setText(QString::number((ui->lineEdit->text().toInt()+1),10));
    }
    qdate.setDate(time.getYear(),time.getMonth(),time.getDay());
    int daysum=qdate.daysInMonth();
    PrintDays(time,daysum);
    DateTime lastday(time.getYear(),time.getMonth(),daysum);
    DateTime firstday(time.getYear(),time.getMonth(),1);
    Search::searchDateTime(firstday,lastday,special,AllDates);
    MarkSticker(special);

}



void MainWindow::on_pushButton_3_clicked()
{
    //QUESTIONES
    ui->tableWidget->clearContents();
    time.SetDate(ui->lineEdit->text().toInt(),(ui->lineEdit_2->text().toInt()-1),1);
    ui->lineEdit_2->setText(QString::number(time.getMonth(),10));
    if(time.getMonth()<1)
    {
        time.SetDate((ui->lineEdit->text().toInt()-1),12,1);

        ui->lineEdit_2->setText(QString::number(12,10));
        ui->lineEdit->setText(QString::number((ui->lineEdit->text().toInt()-1),10));
    }
    qdate.setDate(time.getYear(),time.getMonth(),time.getDay());
    int daysum=qdate.daysInMonth();
    PrintDays(time,daysum);
    QDate month(time.getYear(),time.getMonth(),1);
    DateTime lastday(time.getYear(),time.getMonth(),month.daysInMonth());
    DateTime firstday(time.getYear(),time.getMonth(),1);
    Search::searchDateTime(firstday,lastday,special,AllDates);
    MarkSticker(special);





}

void MainWindow::PrintDays(DateTime &ptime,int DaySum)
{

    int weekday=ptime.getWeek()%7;
    ui->tableWidget->setItem(0,weekday,new QTableWidgetItem("1"));
    int sum=2;
    int i=weekday+1;
    int j=0;
    for(j;j<7;j++)
    {
        for(i;i<7;i++)
        {
            QString Qsum=QString::number(sum,10);
            QTableWidgetItem*t=new QTableWidgetItem(Qsum);
            ui->tableWidget->setItem(j,i,t);

            sum++;
            if(sum>DaySum)
                break;
        }
        if(sum>DaySum)
            break;
        i=0;
    }
    int nsum=1;
    for(j;j<7;j++)
    {

        for(i+1;i<7;i++)
        {
            QString Qsum=QString::number(nsum,10);
            QTableWidgetItem*t=new QTableWidgetItem(Qsum);
            QColor color=Qt::gray;
            t->setTextColor(color);
            ui->tableWidget->setItem(j,i+1,t);
            nsum++;
        }
        i=0;
    }
    if((time.getMonth()-1)<1)
    {
        qdate.setDate(time.getYear(),time.getMonth(),time.getDay());
        nsum=qdate.daysInMonth();

    }
    else
    {
        qdate.setDate(time.getYear(),time.getMonth(),time.getDay());
        nsum=qdate.daysInMonth();
    }
    for(weekday-1;weekday>-1;weekday--)
    {
        QString Qsum=QString::number(nsum,10);
        QTableWidgetItem*t=new QTableWidgetItem(Qsum);
        QColor color=Qt::gray;
        t->setTextColor(color);
        ui->tableWidget->setItem(0,weekday-1,t);
        nsum--;

    }


}

void MainWindow::on_tableWidget_cellClicked(int row, int column)
{

    QDate tom;

    if(ui->tableWidget->item(row,column)->textColor()==Qt::gray)
    {
    }
    else
    {
        time.SetDate(time.getYear(),time.getMonth(),ui->tableWidget->item(row,column)->text().toInt());
        qdate.setDate(time.getYear(),time.getMonth(),time.getDay());
        ui->label->setText(ui->tableWidget->item(row,column)->text());
        QFont ft;
        ft.setPointSize(30);
        ui->label->setFont(ft);
        QString dtstr=qdate.toString("yyyy-MM-dd");
        ui->label_2->setText(dtstr);
        ft.setPointSize(20);
        ui->label_2->setFont(ft);
        if(time.getDay()==qdate.daysInMonth()&&time.getMonth()==12)
        {
            tom.setDate(time.getYear()+1,1,1);
        }
        else if(time.getDay()==qdate.daysInMonth())
        {
            tom.setDate(time.getYear(),time.getMonth()+1,1);
        }
        else
        {
            tom.setDate(time.getYear(),time.getMonth(),time.getDay()+1);
        }
        ui->label_4->setText(tom.toString("yyyy-MM-dd"));
        ui->label_3->setText("Tomorrow");
        ui->listWidget->clear();
        Search::searchDateTime(time,time,special,AllDates);

        for(int i=1;i<=special->dateNum();i++)
        {

            ui->listWidget->addItem(QString::fromStdString(special[i].getTitle()));

        }


    }

}

void MainWindow::on_lineEdit_2_returnPressed()
{
    ui->tableWidget->clearContents();
    time.SetDate(ui->lineEdit->text().toInt(),ui->lineEdit_2->text().toInt(),1);
    qdate.setDate(time.getYear(),time.getMonth(),time.getDay());
    int daysum=qdate.daysInMonth();
    PrintDays(time,daysum);

}

void MainWindow::FindToday()
{
    time.SetDate(CurrentTime.getYear(),CurrentTime.getMonth(),1);
    ui->lineEdit_2->setText(QString::number(time.getMonth(),10));
    ui->lineEdit->setText(QString::number(time.getYear(),10));
    QDate today(CurrentTime.getYear(),CurrentTime.getMonth(),CurrentTime.getDay());
    QDate firstday(CurrentTime.getYear(),CurrentTime.getMonth(),1);
    int daysum=today.daysInMonth();
    PrintDays(time,daysum);
    int row,column;
    column=(today.dayOfWeek()%7);
    row=(today.day()+(firstday.dayOfWeek()%7)-1)/7;
    on_tableWidget_cellClicked(row,column);

    ui->tableWidget->item(row,column)->setSelected(true);


}

void MainWindow::on_pushButton_clicked()
{

    FindToday();
    QDate month(time.getYear(),time.getMonth(),1);
    DateTime lastday(time.getYear(),time.getMonth(),month.daysInMonth());
    DateTime firstday(time.getYear(),time.getMonth(),1);
    Search::searchDateTime(firstday,lastday,special,AllDates);
    MarkSticker(special);


}

void MainWindow::MarkSticker(Date *specialday)
{
    int sum=specialday->dateNum();
    for(int i=1;i<=sum;i++)
    {
        if(specialday->getSDay()==specialday->getEDay())
        {
            QDate qspecialday(specialday[i].getEDay().getYear(),specialday[i].getEDay().getMonth(),specialday[i].getEDay().getDay());
            QDate firstday(specialday[i].getEDay().getYear(),specialday[i].getEDay().getMonth(),1);
            int column=qspecialday.dayOfWeek()%7;
            int row=(qspecialday.day()+(firstday.dayOfWeek()%7)-1)/7;
            ui->tableWidget->setItem(row, column, new QTableWidgetItem(QIcon(":/new/prefix1/dicator.png"),tr("")));
            ui->tableWidget->item(row,column)->setText(QString::number(qspecialday.day(),10));
        }
        else
        {
            // to be continued

        }

    }
}

void MainWindow::on_tableWidget_doubleClicked(const QModelIndex &index)
{
    //出日视图
}

void MainWindow::on_pushButton_4_clicked()
{
    //Add date
    dialog_save=new Dialog_save;
    dialog_save->getInfo(AllDates);
    dialog_save->exec();
}

/*Date* MainWindow::FindMSpeday(int year, int month)
{
     Date *save=new Date[9999];
     Search search;
     QDate D(year,month,1);
     int sum=D.daysInMonth();
     search.searchDateTime(DateTime(year,month,1),DateTime(year,month,sum),save,AllDates);
     return save;

}

Date* MainWindow::FindDSpeday(int year,int month,int day)
{
    Date *save=new Date[9999];
    Search search;
    search.searchDateTime(DateTime(year,month,day),DateTime(year,month,day),save,AllDates);
    return save;

}
bool MainWindow::isMSpeday(int year, int month)
{
    Date *save=new Date[100];
    Search search;
    QDate D(year,month,1);
    int sum=D.daysInMonth();
    return search.searchDateTime(DateTime(year,month,1),DateTime(year,month,sum),save,AllDates);

}*/

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    //得到行号index
    Dialog_edit* dialog_edit=new Dialog_edit(AllDates,index);
    dialog_edit->exec();
    //刷新显示
    FileIO::writeToFile(AllDates,"/home/rainto96/THISISMY/mem/mes,dat");
}
