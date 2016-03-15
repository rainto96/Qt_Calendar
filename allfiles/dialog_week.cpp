#include "dialog_week.h"
#include "ui_dialog_week.h"

Dialog_Week::Dialog_Week(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Week)
{
    ui->setupUi(this);
}

Dialog_Week::~Dialog_Week()
{
    delete ui;
}
