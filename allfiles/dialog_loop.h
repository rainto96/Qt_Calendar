#ifndef DIALOG_LOOP_H
#define DIALOG_LOOP_H

#include <QDialog>
#include "date.h"
#include "loop.h"

namespace Ui {
class Dialog_loop;
}

class Dialog_loop : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_loop(QWidget *parent = 0);
    void getInfo(Date *D);
    ~Dialog_loop();

private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Dialog_loop *ui;
    Date *datedemo;
};

#endif // DIALOG_LOOP_H
