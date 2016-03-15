#ifndef SETTING_H
#define SETTING_H
#include "daytime.h"
#include "text.h"

class Set 
{
private:
    bool isMsgbox;
    DayTime defaultClkTime;
    Text defaultText;
public:
	Set();
	Set(bool isMsgbox, int status,int M );
    bool getisMsgbox();
    void setisMsgbox(bool NewisMsgbox);
    DayTime getdefaultClkTime();
    void setdefaultClkTime(DayTime NewClkTime);
    Text getdefaultText();
    void setdefaultText(Text NewText);
};

#endif