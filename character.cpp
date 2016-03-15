//人物类，包含相关人物的姓名和邮箱

#include "character.h"
Character::Character()///无参构造函数
{
    strcpy(name,"");
    strcpy(email,"");
}
Character ::Character(string N,string E)///有参构造函数
{
    strcpy(name,N.c_str());
    strcpy(email,E.c_str());
}
void Character::setName(string N)//设置姓名为N
{
    strcpy(name,N.c_str());
}
void Character::setEmail(string E)//设置Emial
{
    strcpy(email,E.c_str());
}
string Character::getName()//获取当前对象的姓名
{
    return string(name);
}
string Character::getEmail()//获取当前对象的邮箱
{
    return string(email);
}
