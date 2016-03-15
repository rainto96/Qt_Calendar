//循环类，包含开始时间及结束时间以及循环周期
#include "loop.h"
Loop::Loop()//构造函数
{
    loop=DateTime();
}
Loop::Loop(DateTime Loop)//构造函数
{
    loop=Loop;
}
void Loop::set_Start_DateTime(DateTime D)//设置循环开始时间
{
    SDate=D;
}
void Loop ::set_End_DateTime(DateTime D)//设置循环结束时间
{
    EDate=D;
}
void Loop ::set_loopLength(DateTime D)//设置循环周期
{
    loop=D;
}
DateTime& Loop ::get_End_DateTime()//获取结束时间
{
    return EDate;
}
DateTime& Loop::get_Start_DateTime()//获取开始时间
{
    return SDate;
}
DateTime& Loop::get_loopLength()//获取循环周期
{
    return loop;
}
