#ifndef DIALOG_SAVE_H
#define DIALOG_SAVE_H

#include <QDialog>
#include "date.h"
#include <QTime>
#include "dialog_loop.h"
namespace Ui {
class Dialog_save;
}

class Dialog_save : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_save(QWidget *parent = 0);
    explicit Dialog_save(QDate* tmpdate,QTime* tmptime,QWidget *parent = 0);
    void getInfo(Date* in);
    void setLoopdate(Date* datedemo);
    ~Dialog_save();

private slots:
    void on_pushButton_clicked();


    void on_pushButton_ChooseLoop_clicked();

private:
    Ui::Dialog_save *ui;
    Date* dates;
    Dialog_loop dialog_loop;
};

#endif // DIALOG_SAVE_H
