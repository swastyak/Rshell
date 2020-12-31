#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "Base.hpp"
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>
 #include <sys/wait.h>

using namespace std;

class Command : public Base{
public:

  Command(){
    argv = new char*[128];
  }

  Command(char** arg){
    argv = arg;
    file = arg[0];
  }

    virtual void add(Base*){
      //NO IMPLEMENTATION
    }

    virtual void parse(char command[128]){
      unsigned i;
      bool quote1 = false;
      bool quote2 = false;
      char* start = strtok(command, " ");
      file = start;
      for(i = 0; start != NULL; i++){
      argv[i] = start;
      start = strtok(NULL, " ");
      if(start == NULL){
        argv[i+1] = NULL;
      }
      }
    }

    virtual bool execute(){
      int stat;
      int check = 1;
      if(strcmp(file, "exit") == 0){
        exit(EXIT_SUCCESS);
      }
      if(strcmp(file, "false") == 0){
      return false;
      }
      else{
      pid_t child = fork();
      if(child < 0){
           perror("ERROR IN FORKING PROCESS");
           exit(EXIT_FAILURE);

      }else if(child == 0){
          pid_t did_it_work = execvp(file, argv);
          if(did_it_work < 0) {
              //std::cout << did_it_work << std::endl;
              perror("EXECUTION COULD NOT RUN");
              exit(EXIT_FAILURE);
              //return false;
        } else {
            //std::cout << did_it_work << std::endl;
            return true;
        }
      }
      else{
          if(waitpid(child, NULL, WUNTRACED) < 0){
            perror("INTERNAL ERROR");
            exit(EXIT_FAILURE);
            return false;
        } else {
            return true;
        }



      }
    }
      return true;
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
