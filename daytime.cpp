#include "daytime.h"
#include <cstdio>
bool DayTime::operator == (DayTime& second)
{
	return H==second.H && M==second.M && S==second.S;
}
bool DayTime::operator>= (DayTime& second)
{
	if(H>second.H)
		return true;
	else if(H<second.H)
		return false;
	else
	{
		if(M>second.M)
			return true;
		else if(M<second.M)
			return false;
		else
		{
			if(S>second.S)
				return true;
			else if(S<second.S)
				return false;
			else
				return true;
		}
	}
}
bool DayTime::operator<= (DayTime& second)
{
	if((*this)==second)
		return true;
	else
	{
		if((*this)>=second)
			return false;
		else
			return true;
	}
}
DayTime::DayTime()
{
    H=-1,M=0,S=0;
}
DayTime::DayTime(int H,int M,int S)
{
    this->H=H;
    this->M=M;
    this->S=S;
}
int DayTime::getH()
{
    return H;
}
int DayTime::getM()
{
    return M;
}
int DayTime::getS()
{
    return S;
}
void DayTime::SetTime(int H,int M,int S)
{
    this->H=H;
    this->M=M;
    this->S=S;
}
void DayTime::display()
{
    printf("%2d:%2d:%2d\n",H,M,S);
}

string DayTime::show()
{
    stringstream ss;
    ss.clear();
    string s;
    ss<<H<<':'<<M<<':'<<S;
    ss>>s;
    return s;
}
