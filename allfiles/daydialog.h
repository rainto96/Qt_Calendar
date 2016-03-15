#ifndef DAYDIALOG_H
#define DAYDIALOG_H

#include <QDialog>
#include "date.h"
#include "dialog_save.h"
#include "FileIO.h"
#include <QMessageBox>

struct a
{
    Date date;
    int row;
};
namespace Ui {
class DayDialog;
}

class DayDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DayDialog(QWidget *parent = 0);
    void load();
    bool searchDate(int row,Date& D);
    string checkweek(int a);
    Date* getAllDates();
    string checkmonth(DateTime date);
    ~DayDialog();


private slots:
    void on_tableWidget_list_cellClicked(int row, int column);

    void on_pushButton_Edit_clicked();

    void on_pushButton_Next_clicked();

    void on_pushButton_Previous_clicked();

private:
    Ui::DayDialog *ui;
    int datenum;
    a thisdate[24];
    Date *AllDates;
    int AllDatessize;
    int t;
    DateTime date;
    Dialog_save dialog_save;
};

#endif // DAYDIALOG_H
