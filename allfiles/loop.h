#ifndef  LOOP_H
#define LOOP_H
#include <string>
#include "daytime.h"
#include "datetime.h"

using namespace std;

class Loop
{
public:
    Loop();
    Loop(DateTime Loop);
    void set_Start_DateTime(DateTime D);
    void set_End_DateTime(DateTime D);
    void set_loopLength(DateTime D);
    DateTime& get_End_DateTime();
    DateTime& get_Start_DateTime();
    DateTime& get_loopLength();
private:
    DateTime SDate;
    DateTime EDate;
    DateTime loop;
};



#endif // CHARACTER_H
