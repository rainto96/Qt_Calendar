//人物类的头文件，包含每个函数的声明

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
    string getEmail();  //用string处理比较方便
private:
///信息用char数组存储，方便文件的读写
    char name[111];
    char email[111];
};

#endif // CHARACTER_H
