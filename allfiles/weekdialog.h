#ifndef WEEKDIALOG_H
#define WEEKDIALOG_H

#include <QDialog>
#include <QLabel>
#include "date.h"
#include "dialog_save.h"
#include <QLabel>
#include <QDate>
#include <string>
#include "date.h"
#include <iostream>
#include <cstdio>
#include <map>
#include "FileIO.h"
#include "ShowNowTime.h"
#include "search.h"
#include "remind.h"
namespace Ui {
class WeekDialog;
}

class WeekDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WeekDialog(QWidget *parent = 0);
    ~WeekDialog();
    void setLabelPointer();
    void spinbox_ShowToday();
    void setWeekDay(QDate day);
    QDate getSpinboxesDate();
    void setSpinboxesDate(QDate& date);
    void showCurrentDate();
    void pushToTable(Date& adate,int index);
    void setBeautiful();
    void setBackground();
    void cancelSpan();
private slots:


    void on_tableWidget_cellClicked(int row, int column);

    void on_button_Newdate_clicked();

    void on_button_LastWeek_clicked();

    void on_button_nextWeek_clicked();



private:
    Ui::WeekDialog *ui;
    Date* AllDates;
    Dialog_save* dialog_save;
    QLabel* pLblWeek[10];
};

#endif // WEEKDIALOG_H
