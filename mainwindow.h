#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QCalendarWidget>
#include<QLineEdit>
#include "datetime.h"
#include<string>
#include<QTableWidgetItem>
#include"ShowNowTime.h"
#include<QColor>
#include<QFont>
#include<QDate>
#include"dialog_save.h"
#include"search.h"
#include"daytime.h"
#include"loop.h"
#include "daydialog.h"
#include "weekdialog.h"
#include <QMessageBox>
#include "dialog_search.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void PrintDays(DateTime &ptime,int DaySum);//打印每一个月的界面
    void FindToday();//回到今天的页面
    void MarkSticker(Date *specialday);//给有约会的天作标记
    //void closeEvent( QCloseEvent * event );
    //Date* FindMSpeday(int year, int month);
    //Date* FindDSpeday(int year,int month,int day);
    //bool isMSpeday(int year, int month);
    void setBackground();//设置背景颜色
private slots:


    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_tableWidget_cellClicked(int row, int column);

    void on_lineEdit_2_returnPressed();

    void on_pushButton_clicked();

    void on_tableWidget_doubleClicked(const QModelIndex &index);

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_tableWidget_2_cellClicked(int row, int column);

    void on_tableWidget_3_cellClicked(int row, int column);

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

private:
    Ui::MainWindow *ui;
    DateTime time;
    ShowNowTime CurrentTime;
    QDate qdate;
    Date* AllDates;
    Dialog_save* dialog_save;
    DayDialog* daydialog;
    WeekDialog* weekdialog;
    Date special[50];
    Date special2[50];
    DateTime tomo;
    Dialog_search* dialog_search;
};

#endif // MAINWINDOW_H
