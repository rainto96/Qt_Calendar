#include "FileIO.h"
#include <cstdio>
void FileIO::writeToFile(Date* dates,char* dir)
{
	FILE* out;
   out=fopen(dir,"w");
   fwrite(dates,sizeof(Date),dates->dateNum(),out);
   fclose(out);
}
void FileIO::readFromFile(Date* dates,char* dir,int howmany)
{
	FILE* in;
   if((in=fopen(dir,"r"))!=NULL)
   	 {
        fread(dates,sizeof(Date),howmany,in);
        fclose(in);
   	 }
   else
       dates[0].setDateNum(0);
}
/*
使用范例
	比如你开了Date alldates[999]数组用来存所有约会数据
写粗就是
	FileIO::writeToFile(alldates,"/home/rainto96/mem.dat");//也可以是别的路径
读入就是
	FileIO::readFromFile(alldates,"/home/rainto96/mem.dat",999);
*/
