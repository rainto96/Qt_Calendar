#include "text.h"
#include <iostream>
using namespace std;
Text::Text(int status)
{
   if(status==1)
   	cout<<"先开始，不用等我"<<endl;
   else if(status==2)
   	cout<<"我会迟到几分钟"<<endl;
   else if(status==3)
   	cout<<"我大概再过10分钟就可以到了"<<endl;
   else if(status==4)
   	cout<<"抱歉，我赶不上了，我们另约时间吧"<<endl;
   else 
   cout<<"错误"<<endl;
}
Text::~Text()
{
}