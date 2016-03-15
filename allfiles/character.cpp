#include "character.h"
Character::Character()
{
    strcpy(name,"");
    strcpy(email,"");
}
Character ::Character(string N,string E)
{
    strcpy(name,N.c_str());
    strcpy(email,E.c_str());
}
void Character::setName(string N)
{
    strcpy(name,N.c_str());
}
void Character::setEmail(string E)
{
    strcpy(email,E.c_str());
}
string Character::getName()
{
    return string(name);
}
string Character::getEmail()
{
    return string(email);
}
