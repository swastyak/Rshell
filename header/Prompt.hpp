#ifndef PROMPT_HPP
#define PROMPT_HPP

#include <iostream>
#include <vector>
#include "Base.hpp"

using namespace std;

class Prompt : public Base{
  private:
          vector<Base*> prompts;
  public:
          virtual bool execute(){
            for(unsigned i = 0; i < prompts.size(); i++){
                  prompts.at(i) -> execute();
                  return 1;
              }
              return 0;
          }
          virtual void add(Base* addition){
                prompts.push_back(addition);
            }
          virtual void parse(char command[]){
            //NO IMPLEMENTATION
          }
          virtual char** Get_ARG(){
            return argv;
          }

          virtual vector<char*> getArg(){
            vector<char*> t;
            return t;
          }

};

#endif
