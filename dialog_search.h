#ifndef DIALOG_SEARCH_H
#define DIALOG_SEARCH_H
#include <character.h>
#include <date.h>
#include <datetime.h>
#include <daytime.h>
#include <loop.h>
#include <search.h>
#include "ShowNowTime.h"
#include <text.h>
#include <QMainWindow>
#include <QDialog>

namespace Ui {
class Dialog_search;
}

class Dialog_search : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_search(Date* in,QWidget *parent = 0);
    ~Dialog_search();

private slots:
    void on_comboBox_currentIndexChanged(int index);
    void on_pushButton_clicked();

    void on_radioButton_2_clicked();

private:
    Ui::Dialog_search *ui;
    Search search;//新建一个搜索类
    Date result[99];//新建一个约会类数组用于存放搜索结果
    Date* AllDates;
    DateTime startdate;//开始日期
    DateTime enddate;//结束日期
    bool isimportant;//是否重要
};

#endif // DIALOG_SEARCH_H
