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

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void PrintDays(DateTime &ptime,int DaySum);
    void FindToday();
    void MarkSticker(Date *specialday);
    //Date* FindMSpeday(int year, int month);
    //Date* FindDSpeday(int year,int month,int day);
    //bool isMSpeday(int year, int month);
private slots:


    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_tableWidget_cellClicked(int row, int column);

    void on_lineEdit_2_returnPressed();

    void on_pushButton_clicked();

    void on_tableWidget_doubleClicked(const QModelIndex &index);

    void on_pushButton_4_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    DateTime time;
    ShowNowTime CurrentTime;
    QDate qdate;
    Date* AllDates;
    Dialog_save* dialog_save;
    Date special[50];
};

#endif // MAINWINDOW_H
