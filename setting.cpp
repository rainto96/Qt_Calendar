#include "setting.h"
#include "text.h"


Set::Set()
{
	this->isMsgbox=true;
    this->defaultText=Text(1);
	this->defaultClkTime=DayTime();


}

Set::Set(bool isMsgbox, int status,int M )
{
	this->isMsgbox=isMsgbox;
    this->defaultText=Text(status);
	this->defaultClkTime=DayTime(0,M,0);

}
bool Set::getisMsgbox()
{
    return Set::isMsgbox;
}
void Set::setisMsgbox(bool NewisMsgbox)
{
    this->isMsgbox=NewisMsgbox;
}
void Set::setdefaultClkTime(DayTime NewClkTime)
{
	this->defaultClkTime=NewClkTime;
}

DayTime Set::getdefaultClkTime()
{
	return defaultClkTime;
}

void Set::setdefaultText(Text NewText)
{
	this->defaultText=NewText;
}

Text Set::getdefaultText()
{
	return this->defaultText;
}
