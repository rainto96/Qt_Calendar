#ifndef DIALOG_EDIT_H
#define DIALOG_EDIT_H
#include <QDialog>
#include "date.h"
#include "dialog_loop.h"
#include <QTime>
namespace Ui {
class Dialog_edit;
}

class Dialog_edit : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_edit(Date* AllDates,int index,QWidget *parent = 0);
    ~Dialog_edit();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::Dialog_edit *ui;
    Date* dates;
    Dialog_loop* dialog_loop;
    int index;
};
#endif // DIALOG_EDIT_H
