#include "loop.h"
Loop::Loop()
{
    loop=DateTime();
}
Loop::Loop(DateTime Loop)
{
    loop=Loop;
}
void Loop::set_Start_DateTime(DateTime D)
{
    SDate=D;
}
void Loop ::set_End_DateTime(DateTime D)
{
    EDate=D;
}
void Loop ::set_loopLength(DateTime D)
{
    loop=D;
}
DateTime& Loop ::get_End_DateTime()
{
    return EDate;
}
DateTime& Loop::get_Start_DateTime()
{
    return SDate;
}
DateTime& Loop::get_loopLength()
{
    return loop;
}
