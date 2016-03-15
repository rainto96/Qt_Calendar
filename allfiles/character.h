#ifndef CHARACTER_H
#define CHARACTER_H

#include <cstring>
#include <string>
using namespace std;
class Character
{
public:
    Character();
    Character(string N,string E);
    void setName(string N);
    void setEmail(string E);
    string getName();
    string getEmail();
private:
    char name[111];
    char email[111];
};

#endif // CHARACTER_H
