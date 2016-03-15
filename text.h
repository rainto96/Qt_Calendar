#ifndef TEXT_H
#define TEXT_H
#include <iostream>
using namespace std;
class Text
{
   public:
      Text();
	  Text(int status);
	  ~Text();
	private:
	  string str;
	  int status;
};
#endif
