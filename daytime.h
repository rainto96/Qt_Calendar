#ifndef DAYTIME_H
#define DAYTIME_H

#include <string>
#include <sstream>
using namespace std;
class DayTime
{
    private:
        int H,M,S;
    public:
    		bool operator >=(DayTime& second);
			bool operator <=(DayTime& second);
			bool operator ==(DayTime& second);
        DayTime();
        DayTime(int H,int M,int S);
        int getH();
        int getM();
        int getS();
        void SetTime(int H,int M,int S);
        void display();
        string show();
};

#endif // DAYTIME_H
