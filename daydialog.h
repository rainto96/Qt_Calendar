//日视图的头文件，每个函数的声明

#ifndef DAYDIALOG_H
#define DAYDIALOG_H

#include <QDialog>
#include "date.h"
#include "dialog_save.h"
#include "FileIO.h"
#include <QMessageBox>
#include "dialog_edit.h"
struct a//保存当天所有事件的结构体，row是该事件在当天tablewidget中的行数，index是该事件在AllDates中的数组
{
    Date date;
    int row;
    int index;
};
namespace Ui {
class DayDialog;
}

class DayDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DayDialog(Date* in_day,QWidget *parent = 0);//构造函数
    void load();//重新载入函数
    bool searchDate(int row,Date& D);//查找这个row相关的事件
    string checkweek(int a);//查找a（1-7）代表的星期的英文
    Date* getAllDates();//获取AllDates
    void getInfo(Date* dates);//从上一视图获取AllDates
    string checkmonth(DateTime date);//返回date的月份的英文
    ~DayDialog();//析构函数
    void setBackground();

//槽函数
private slots:
    void on_tableWidget_list_cellClicked(int row, int column);

    void on_pushButton_Edit_clicked();

    void on_pushButton_Next_clicked();

    void on_pushButton_Previous_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::DayDialog *ui;
    int datenum;
    a thisdate[24];
    a showdate;
    Date *AllDates;
    int AllDatessize;
    int t;
    DateTime date;
    Dialog_save dialog_save;
    Dialog_edit* dialog_edit;
};

#endif // DAYDIALOG_H
