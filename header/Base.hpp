#ifndef BASE_HPP
#define BASE_HPP

#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

class Base{
  protected:
    char input[128];
    char * file;
    char** argv;
  public:
    Base(){
      argv = new char*[128];
      file = nullptr;
    }
    virtual void add(Base*) = 0;
    virtual void parse(char command[128]) = 0;
    virtual bool execute() = 0;
    virtual char** Get_ARG() = 0;
    virtual vector<char*> getArg() = 0;
};
#endif
