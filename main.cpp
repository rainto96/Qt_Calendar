#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include "FileIO.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    //QTextCodec::setCodecForTr( QTextCodec::codecForName("GBK") );
    //QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf8"));
    //QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));
    MainWindow w;
    w.show();
    return  app.exec();
}
