#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "FileIO.h"
#include "remind.h"
#include "dialog_edit.h"
#include <QTableWidget>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    AllDates=new Date[9999];
    //cout<<"constructor::"<<AllDates->dateNum()<<endl;
    setBackground();
    ui->tableWidget_2->setColumnWidth(0,200);
    ui->tableWidget_3->setColumnWidth(0,200);
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


    //FileIO::readFromFile(AllDates,"/home/fuying/afterONE/mem/mem.dat",999);
    FileIO::readFromFile(AllDates,"/home/rainto96/Qtprogram/table/mem.dat",999);//从文件中读入之前保存好的约会
    //cout<<AllDates->dateNum()<<"here"<<endl;
    //cout<<"startsetRemind"<<endl;
    //Remind::setTimeClock_Today(AllDates);
    //cout<<"endsetRemind"<<endl;
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget_2->horizontalHeader()->setVisible(false);
    ui->tableWidget_3->horizontalHeader()->setVisible(false);
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

    firstday.setDay(1);
    lastday.setDay(27);
    Search::searchDateTime(firstday,lastday,special,AllDates);
    ////cout<<firstday.show()<<endl;
    //cout<<lastday.show()<<endl;
    //cout<<"Alldates_::"<<AllDates->dateNum()<<endl;
    //cout<<"Alldates[1].day::"<<AllDates[0].getSDay().show()<<endl;
    //cout<<"special_::"<<special[0].dateNum()<<endl;
    MarkSticker(special);
}//界面初始化


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->tableWidget->clearContents();
    ui->tableWidget_2->setRowCount(0);
    ui->tableWidget_3->setRowCount(0);
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

}//显示下个月的视图

//void MainWindow::closeEvent( QCloseEvent * event )
//{
//    FileIO::writeToFile(AllDates,"/home/rainto96/Qtprogram/table/mem.dat");
//   switch( QMessageBox::information( this, tr("关闭窗口"),tr("确定要关闭程序？"),tr("确定"), tr("取消"),0, 1 ) )
//    {
//   case 0:
//   {
//       event->accept();
//       break;
//   }
//   case 1:
//    default:
//           event->ignore();
//           break;
//    }
//}

void MainWindow::on_pushButton_3_clicked()
{
    //QUESTIONES
    ui->tableWidget->clearContents();
    ui->tableWidget_2->setRowCount(0);
    ui->tableWidget_3->setRowCount(0);

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
}//显示上个月的视图

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
        qdate.setDate(time.getYear()-1,12,time.getDay());
        nsum=qdate.daysInMonth();

    }
    else
    {
        qdate.setDate(time.getYear(),time.getMonth()-1,time.getDay());
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
        ui->tableWidget_2->clear();
        /*for(int i=0;i<=ui->tableWidget_2->rowCount();i++)
        {
           cout<<i<<endl;
            ui->tableWidget_2->removeRow(i);
        }*/
        ui->tableWidget_2->setRowCount(0);
       // memset(special,0,sizeof(special));
        //Date* test=new Date[100];
       // Search::searchDateTime(time,time,test,AllDates);
        //cout<<"here_test:"<<test[0].dateNum()<<endl;
        //cout<<"t2::"<<test[2].getOrigin()<<endl;
        //cout<<"test_address"<<test+2<<endl;
        //delete test;

        Search::searchDateTime(time,time,special,AllDates);
        //cout<<"here:"<<special[0].dateNum()<<endl;
        //cout<<"s1::"<<special[1].getOrigin()<<endl;
        for(int i=1;i<=special->dateNum();i++)
        {
            int row =ui->tableWidget_2->rowCount();

            ui->tableWidget_2->insertRow( row );
            //cout<<2<<endl;
            ui->tableWidget_2->setItem(row,0,new QTableWidgetItem(QString::fromStdString(special[i].getTitle())));
            //cout<<3<<endl;
        }
        //cout<<special[1].getTitle()<<endl;

        //cout<<special[1].getOrigin()<<endl;

        //cout<<special[2].getTitle()<<endl;

        //cout<<special[2].getOrigin()<<endl;


        ui->tableWidget_3->setRowCount(0);

        tomo.SetDate(tom.year(),tom.month(),tom.day());

        Search::searchDateTime(tomo,tomo,special2,AllDates);
        for(int i=1;i<=special2->dateNum();i++)
        {
            int row =ui->tableWidget_3->rowCount();
            ui->tableWidget_3->insertRow( row );
            //cout<<2<<endl;
            ui->tableWidget_3->setItem(row,0,new QTableWidgetItem(QString::fromStdString(special2[i].getTitle())));
            //cout<<3<<endl;
        }




    }

}//点击表格中的某一天后在右边的界面有相应显示

void MainWindow::on_lineEdit_2_returnPressed()
{
    ui->tableWidget->clearContents();
    ui->tableWidget_2->setRowCount(0);
    ui->tableWidget_3->setRowCount(0);
    time.SetDate(ui->lineEdit->text().toInt(),ui->lineEdit_2->text().toInt(),1);
    qdate.setDate(time.getYear(),time.getMonth(),time.getDay());
    int daysum=qdate.daysInMonth();
    PrintDays(time,daysum);
    QDate month(time.getYear(),time.getMonth(),1);
    DateTime lastday(time.getYear(),time.getMonth(),month.daysInMonth());
    DateTime firstday(time.getYear(),time.getMonth(),1);
    Search::searchDateTime(firstday,lastday,special,AllDates);
    MarkSticker(special);


}//输入年月后跳转

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
    /*cout<<dates->dateNum();
           //cout<<dates[1]->getSTin_tableWidget_cellClicked(row,column);*/
    on_tableWidget_cellClicked(row,column);
    ui->tableWidget->item(row,column)->setSelected(true);


}//回到今天的界面

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
        QDate qspecialday(specialday[i].getSDay().getYear(),specialday[i].getSDay().getMonth(),specialday[i].getSDay().getDay());
        QDate firstday(specialday[i].getSDay().getYear(),specialday[i].getSDay().getMonth(),1);
        int column=qspecialday.dayOfWeek()%7;
        int row=(qspecialday.day()+(firstday.dayOfWeek()%7)-1)/7;
        ui->tableWidget->setItem(row, column, new QTableWidgetItem(QIcon(":/new/prefix1/dicator.png"),tr("")));
        ui->tableWidget->item(row,column)->setText(QString::number(qspecialday.day(),10));



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
    //cout<<"in button clicked"<<AllDates->dateNum()<<endl;
    dialog_save->getInfo(AllDates);
    dialog_save->exec();
    //刷新显示
    ui->tableWidget_2->setRowCount(0);
    Search::searchDateTime(time,time,special,AllDates);
    for(int i=1;i<=special->dateNum();i++)
    {
        int row =ui->tableWidget_2->rowCount();
        ui->tableWidget_2->insertRow( row );


        ui->tableWidget_2->setItem(row,0,new QTableWidgetItem(QString::fromStdString(special[i].getTitle())));

    }
    //////
    QDate qdate;
    qdate.setDate(ui->lineEdit->text().toInt(),ui->lineEdit_2->text().toInt(),1);
    int daysum=qdate.daysInMonth();
    time.SetDate(ui->lineEdit->text().toInt(),ui->lineEdit_2->text().toInt(),1);
    PrintDays(time,daysum);
    DateTime lastday(time.getYear(),time.getMonth(),daysum);
    DateTime firstday(time.getYear(),time.getMonth(),1);
    Search::searchDateTime(firstday,lastday,special,AllDates);

    FindToday();
    MarkSticker(special);
}//点击右边界面的事件标题后可以对它进行编辑

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

/*void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    int index;
    //得到行号index
    item->
    Dialog_edit* dialog_edit=new Dialog_edit(AllDates,index);
    dialog_edit->exec();
    //刷新显示


    FileIO::writeToFile(AllDates,"/home/fuying/cal/mem/mem.dat");
}*/

void MainWindow::on_pushButton_5_clicked()
{
    this->close();
    daydialog=new DayDialog(AllDates);
    daydialog->show();
    daydialog->exec();
    //刷新显示
    ui->tableWidget_2->setRowCount(0);
    Search::searchDateTime(time,time,special,AllDates);
    for(int i=1;i<=special->dateNum();i++)
    {
        int row =ui->tableWidget_2->rowCount();
        ui->tableWidget_2->insertRow( row );


        ui->tableWidget_2->setItem(row,0,new QTableWidgetItem(QString::fromStdString(special[i].getTitle())));

    }
    //////
    int daysum=qdate.daysInMonth();
    DateTime lastday(time.getYear(),time.getMonth(),daysum);
    DateTime firstday(time.getYear(),time.getMonth(),1);
    Search::searchDateTime(firstday,lastday,special,AllDates);
    MarkSticker(special);
    this->show();

}

void MainWindow::on_pushButton_6_clicked()
{
    this->close();
    weekdialog=new WeekDialog(AllDates);
    weekdialog->show();
    weekdialog->exec();
    //刷新显示
    ui->tableWidget_2->setRowCount(0);
    Search::searchDateTime(time,time,special,AllDates);
    for(int i=1;i<=special->dateNum();i++)
    {
        int row =ui->tableWidget_2->rowCount();
        ui->tableWidget_2->insertRow( row );


        ui->tableWidget_2->setItem(row,0,new QTableWidgetItem(QString::fromStdString(special[i].getTitle())));

    }
    ///////
    int daysum=qdate.daysInMonth();
    DateTime lastday(time.getYear(),time.getMonth(),daysum);
    DateTime firstday(time.getYear(),time.getMonth(),1);
    Search::searchDateTime(firstday,lastday,special,AllDates);
    MarkSticker(special);
    this->show();
}
void MainWindow::setBackground()
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
        ui->tableWidget->setColumnWidth(0,width);
        for(int i=0;i<=23;i++)
            ui->tableWidget->setRowHeight(i,height);
        ui->tableWidget->setStyleSheet("border:2px #FFFFCD;border-radius:10px;padding:2px 2px;background:#FFFFCD");

        pal.setColor(QPalette::ButtonText, QColor(255,255,255));
        ui->pushButton->setPalette(pal);
        ui->pushButton_2->setPalette(pal);
        ui->pushButton_3->setPalette(pal);
        ui->pushButton_4->setPalette(pal);
        ui->pushButton_5->setPalette(pal);
        ui->pushButton_6->setPalette(pal);
        ui->pushButton_7->setPalette(pal);
        ui->pushButton_8->setPalette(pal);
        //ui->pushButton_2->setPalette(pal);

        ui->pushButton->setStyleSheet("border:2px green;border-radius:10px;padding:2px 2px;background:rgb(124,250,0)");
        ui->pushButton_2->setStyleSheet("border:2px green;border-radius:10px;padding:2px 2px;background:rgb(124,250,0)");
        ui->pushButton_3->setStyleSheet("border:2px green;border-radius:10px;padding:2px 2px;background:rgb(124,250,0)");
        ui->pushButton_4->setStyleSheet("border:2px green;border-radius:10px;padding:2px 2px;background:rgb(124,250,0)");
        ui->pushButton_5->setStyleSheet("border:2px green;border-radius:10px;padding:2px 2px;background:rgb(124,250,0)");
        ui->pushButton_6->setStyleSheet("border:2px green;border-radius:10px;padding:2px 2px;background:rgb(124,250,0)");
        ui->pushButton_7->setStyleSheet("border:2px green;border-radius:10px;padding:2px 2px;background:rgb(124,250,0)");
        ui->pushButton_8->setStyleSheet("border:2px green;border-radius:10px;padding:2px 2px;background:rgb(124,250,0)");
}//设置背景颜色和按钮样式

void MainWindow::on_tableWidget_2_cellClicked(int row, int column)
{
    //cout<<time.show()<<"::here time"<<endl;
     Search::searchDateTime(time,time,special,AllDates);
    int index=special[row+1].getOrigin();

    Dialog_edit* dialog_edit=new Dialog_edit(AllDates,index);
    dialog_edit->exec();
    //刷新显示
    ui->tableWidget_2->setRowCount(0);
    Search::searchDateTime(time,time,special,AllDates);
    for(int i=1;i<=special->dateNum();i++)
    {
        int row =ui->tableWidget_2->rowCount();
        ui->tableWidget_2->insertRow( row );


        ui->tableWidget_2->setItem(row,0,new QTableWidgetItem(QString::fromStdString(special[i].getTitle())));

    }
    //////

    //FileIO::writeToFile(AllDates,"/home/fuying/afterONE/mem/mem.dat");
    FileIO::writeToFile(AllDates,"/home/rainto96/Qtprogram/table/mem.dat");

}//点击右边界面的事件标题后可以对它进行编辑

void MainWindow::on_tableWidget_3_cellClicked(int row, int column)
{

    int index=special2[row+1].getOrigin();
    Dialog_edit* dialog_edit=new Dialog_edit(AllDates,index);
    dialog_edit->exec();
    //刷新显示

    ui->tableWidget_3->setRowCount(0);
    Search::searchDateTime(tomo,tomo,special2,AllDates);
    for(int i=1;i<=special2->dateNum();i++)
    {
        int row =ui->tableWidget_3->rowCount();
        ui->tableWidget_3->insertRow( row );
        ui->tableWidget_3->setItem(row,0,new QTableWidgetItem(QString::fromStdString(special2[i].getTitle())));
    }

    //FileIO::writeToFile(AllDates,"/home/fuying/afterONE/mem/mem.dat");
    FileIO::writeToFile(AllDates,"/home/rainto96/Qtprogram/table/mem.dat");
}//点击右边界面的事件标题后可以对它进行编辑

void MainWindow::on_pushButton_7_clicked()
{
    dialog_search=new Dialog_search(AllDates);
    dialog_search->exec();
    delete dialog_search;
}//搜索对话框

void MainWindow::on_pushButton_8_clicked()
{
    delete AllDates;
    AllDates=new Date[999];
    FileIO::writeToFile(AllDates,"/home/rainto96/Qtprogram/table/mem.dat");
    //刷新显示
    ui->tableWidget_2->setRowCount(0);
    Search::searchDateTime(time,time,special,AllDates);
    for(int i=1;i<=special->dateNum();i++)
    {
        int row =ui->tableWidget_2->rowCount();
        ui->tableWidget_2->insertRow( row );


        ui->tableWidget_2->setItem(row,0,new QTableWidgetItem(QString::fromStdString(special[i].getTitle())));

    }
    //////
    QDate qdate;
    qdate.setDate(ui->lineEdit->text().toInt(),ui->lineEdit_2->text().toInt(),1);
    int daysum=qdate.daysInMonth();
    time.SetDate(ui->lineEdit->text().toInt(),ui->lineEdit_2->text().toInt(),1);
    PrintDays(time,daysum);
    DateTime lastday(time.getYear(),time.getMonth(),daysum);
    DateTime firstday(time.getYear(),time.getMonth(),1);
    Search::searchDateTime(firstday,lastday,special,AllDates);
    MarkSticker(special);

}//清空
