#include "dialog_loop.h"
#include "ui_dialog_loop.h"
#include "ShowNowTime.h"

Dialog_loop::Dialog_loop(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_loop)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate(ShowNowTime::getYear(),ShowNowTime::getMonth(),ShowNowTime::getDay()));
    ui->dateEdit_2->setDate(QDate(ShowNowTime::getYear(),ShowNowTime::getMonth(),ShowNowTime::getDay()));
}
void Dialog_loop::getInfo(Date *D)
{
    datedemo=D;
}

Dialog_loop::~Dialog_loop()
{
    delete ui;
}



void Dialog_loop::on_pushButton_clicked()
{
    datedemo->getLoop().set_Start_DateTime(DateTime(ui->dateEdit->date().year(),ui->dateEdit->date().month(),ui->dateEdit->date().day()));
    datedemo->getLoop().set_End_DateTime(DateTime(ui->dateEdit_2->date().year(),ui->dateEdit_2->date().month(),ui->dateEdit_2->date().day()));
    if(ui->comboBox->currentIndex()==0)
    {
        datedemo->getLoop().set_loopLength(DateTime(0,1,0));
        datedemo->getLoop().get_loopLength().Display();
    }
        else if(ui->comboBox->currentIndex()==1)
    {
        datedemo->getLoop().set_loopLength(DateTime(0,0,(ui->textEdit->toPlainText().toInt())*7));
    }
    else if(ui->comboBox->currentIndex()==2)
        datedemo->getLoop().set_loopLength(DateTime(0,0,(ui->textEdit->toPlainText().toInt())));
    //datedemo->getLoop().get_Start_DateTime().Display();
    //cout<<ui->textEdit->toPlainText().toInt()<<endl;
    this->close();
}

void Dialog_loop::on_pushButton_2_clicked()
{
    this->close();
}
