#include "text.h"
#include <iostream>
using namespace std;
Text::Text(int status)
{
   if(status==1)
   	cout<<"�ȿ�ʼ�����õ���"<<endl;
   else if(status==2)
   	cout<<"�һ�ٵ�������"<<endl;
   else if(status==3)
   	cout<<"�Ҵ���ٹ�10���ӾͿ��Ե���"<<endl;
   else if(status==4)
   	cout<<"��Ǹ���Ҹϲ����ˣ�������Լʱ���"<<endl;
   else 
   cout<<"����"<<endl;
}
Text::~Text()
{
}