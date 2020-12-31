#ifndef CONNECTOR_HPP
#define CONNECTOR_HPP

#include "Base.hpp"
//#include "Precedence.hpp"
#include <iostream>
#include <vector>
#include <cstring>
#include "Command.hpp"
#include <sys/types.h>
#include <sys/wait.h>
#include "Test.hpp"
 #include <cstdlib>

 using namespace std;

class Connector: public Base{

private:

  vector<char*> arg;

public:

  Connector(){
    argv = new char*[256];
  }

  Connector(vector<char*> temp){
    Connector();
    for(unsigned i = 0; i < temp.size(); i++){
      arg.push_back(temp.at(i));
    }
    arg.push_back(NULL);
  }

  virtual void add(Base*){
    return;
  }

  virtual void parse(char command[256]){
    char* start = strtok(command, " ");
    file = start;
    for(unsigned i = 0; start != NULL; i++){
      arg.push_back(start);
      start = strtok(NULL, " ");
    }
      arg.push_back(NULL);
  }

  virtual bool execute(){
        bool status;
        unsigned tracker = 0;
        vector<char*> num_arg;

        for(unsigned k = 0; k < arg.size(); k++){
            if(arg.at(k) != NULL  && strcmp(arg.at(k), "test") != 0 && strpbrk(arg.at(k), "[") == nullptr && strpbrk(arg.at(k), "(") == nullptr && strpbrk(arg.at(k), "\"") == nullptr && strpbrk(arg.at(k), ";") == nullptr &&  strpbrk(arg.at(k), "&&") == nullptr && strpbrk(arg.at(k), "||") == nullptr && (strpbrk(arg.at(k), "#") == nullptr)) {
                num_arg.push_back(arg.at(k));
            }
             if(arg.at(k) == NULL){
                if(num_arg.empty() == true){
                    return status;
                }
                //num_arg.push_back(arg.at(arg.size()-1));
                char** ARG = new char*[256];
                for(unsigned j = 0; j < num_arg.size(); j++){
                    ARG[j] = num_arg.at(j);
                }
                ARG[num_arg.size()] = NULL;


                Base * SENT = new Command(ARG);
                status = SENT -> execute();
                return status;
            }else if(strpbrk(arg.at(k), "\"") != nullptr){
              //cout << "here\n";
              string s(arg.at(k));
              int count = 0;
              for(unsigned i = 0; i < s.size(); i++){
                if(s.at(i) == '\"'){
                  count++;
                }
              }
              if(count == 2){
                char* temp3 = strtok(arg.at(k), "\"");
                num_arg.push_back(temp3);
                tracker = 1;
              }else{
              char * temp = strtok(arg.at(k), "\"");
              num_arg.push_back(temp);
              char* test;
              for(unsigned i = k+1; i < arg.size(); i++){
                if(arg.at(i) == NULL){
                  break;
                }
                if(strpbrk(arg.at(i), "\"") != nullptr){
                  char *temp2 = strtok(arg.at(i), "\"");
                  num_arg.push_back(temp2);
                    k = i;
                  break;
                }else{
                  num_arg.push_back(arg.at(i));
                }
              }
            }

              char** ARG = new char*[256];
              for(unsigned j = 0; j < num_arg.size(); j++){
                  ARG[j] = num_arg.at(j);
              }
              ARG[num_arg.size()] = NULL;


              Base * SENT = new Command(ARG);
              status = SENT -> execute();
              tracker = 1;
              num_arg.clear();
              num_arg.resize(0);

            }
            else if(strpbrk(arg.at(k), "(") != nullptr){

              int up = 1;
              int down = 0;
              bool quote = false;
              vector<char*> temp;

              bool doub = false;



              char* take = strtok(arg.at(k), "(");
              if(strpbrk(arg.at(k), ")") != nullptr){
                take = strtok(take, ")");
                temp.push_back(take);
                Base* test = new Connector(temp);
                    status = test -> execute();
                    tracker = 1;
              }else{
              temp.push_back(take);
                int count = 0;
                for(unsigned i = k + 1; i < arg.size(); i++){
                if(arg.at(i) == NULL){
                  cout << "INVALID INPUT\n";
                  return false;
                }

                if(strpbrk(arg.at(i), "\"")){
                    quote = !quote;
                    string s(arg.at(i));
                    int count = 0;
                    for(unsigned l = 0; l < s.size(); l++){
                      if(s.at(l) == '\"'){
                        count++;
                      }
                    }
                    if(count == 2){
                      if(s == "\"()\")"){
                        s.pop_back();
                        char *a = &(s[0]);
                        temp.push_back(a);
                        Base* test = new Connector(temp);
                        status = test -> execute();
                        tracker = 1;
                        k = i;
                        break;
                      }else{
                        if(s.at(s.size()-1) == ')'){
                           s.pop_back();
                          char *a = &(s[0]);
                          temp.push_back(a);
                          Base* test = new Connector(temp);
                          status = test -> execute();
                          tracker = 1;
                          k = i;
                          break;
                        }
                      }
                    }

                }

                if(strpbrk(arg.at(i), "(") && quote == false){
                  up++;
                  temp.push_back(arg.at(i));
                }
                else if(strpbrk(arg.at(i), ")") && quote == false){



                  down++;
                  if(up == down){
                    take = strtok(arg.at(i), ")");
                    if(count != 2){
                    temp.push_back(take);
                  }
                    //temp.push_back(NULL);
                    Base* test = new Connector(temp);
                    status = test -> execute();
                    tracker = 1;
                    k = i;
                    break;
                  }else{
                    temp.push_back(arg.at(i));
                  }
                }else{
                  temp.push_back(arg.at(i));
                }
              }
            }

            }



            else if(strcmp(arg.at(k), "test") == 0 || strpbrk(arg.at(k), "[") != nullptr){
              for(unsigned i = k; i < arg.size(); i++){
                if(arg.at(i) != NULL  && strpbrk(arg.at(i), "\"") == nullptr && strpbrk(arg.at(i), "]") == nullptr && strpbrk(arg.at(i), ";") == nullptr &&  strpbrk(arg.at(i), "&&") == nullptr && strpbrk(arg.at(i), "||") == nullptr && (strpbrk(arg.at(i), "#") == nullptr)) {
                num_arg.push_back(arg.at(i));
                //cout << arg.at(i) << endl;
                }else{
                  if(arg.at(i) == NULL){
                    k = i - 1;
                    break;
                  }
                  if(strpbrk(arg.at(i), "]")){
                    k = i;
                    break;
                  }else{
                    k = i -1;
                    break;
                  }
                }
              }
              Base* test = new Test(num_arg);
             // cout << "here\n";
              status = test -> execute();
              num_arg.resize(0);

              tracker = 1;

              if(arg.at(k+1) == NULL){
                return status;
              }

            }


            else if(strpbrk(arg.at(k), "#") != nullptr){
                    if(num_arg.empty() == true){
                      char* temp = strtok(arg.at(k), "#");
                      num_arg.push_back(temp);
                    }
              char** ARG = new char*[256];
              for(unsigned j = 0; j < num_arg.size(); j++){
                  ARG[j] = num_arg.at(j);
              }
              ARG[num_arg.size()] = NULL;


              Base * SENT = new Command(ARG);
              status = SENT -> execute();
              //exit(EXIT_SUCCESS);
              return status;
            }

            else if(strpbrk(arg.at(k), ";") != nullptr){

                char* temp = strtok(arg.at(k), ";");
                num_arg.push_back(temp);

                char** ARG = new char*[256];
                for(unsigned j = 0; j < num_arg.size(); j++){
                    ARG[j] = num_arg.at(j);
                }
                ARG[num_arg.size()] = NULL;


                Base* SENT = new Command(ARG);
                status = SENT -> execute();
                num_arg.clear();
                num_arg.resize(0);
                tracker = 0;
            }

        else if(strpbrk(arg.at(k), ";") != nullptr){

          char* temp = strtok(arg.at(k), ";");
          num_arg.push_back(temp);

          char** ARG = new char*[256];
          for(unsigned j = 0; j < num_arg.size(); j++){
            ARG[j] = num_arg.at(j);
          }
          ARG[num_arg.size()] = NULL;

          Base* SENT = new Command(ARG);
          status = SENT -> execute();
          //num_arg.clear();
          num_arg.resize(0);
          tracker = 0;
        }



        else if(strpbrk(arg.at(k), "&&") != nullptr){


        //cout << "here\n";

          if(tracker == 0){
            char** ARG = new char*[256];
            for(unsigned j = 0; j < num_arg.size(); j++){
              ARG[j] = num_arg.at(j);
              if(j + 1 >= num_arg.size()){
                ARG[j+1] = NULL;
                break;
              }
            }

            Base * SENT = new Command(ARG);
            status = SENT -> execute();
            num_arg.clear();
            num_arg.resize(0);
            tracker = 1;
            //cout << "DID IT\n";
          }
          if(status == true){
            //cout << "WORKS SO FAR\n";
            num_arg.resize(0);
            for(unsigned i = k + 1; i < arg.size() /*&& k < arg.size()*/; i++){
              if(arg.at(i) != NULL && strpbrk(arg.at(i), "\"") == nullptr && strcmp(arg.at(i), "&&") != 0  && strpbrk(arg.at(i), "||") == nullptr && strcmp(arg.at(i), "test") != 0 && strpbrk(arg.at(i), "[") == nullptr && strpbrk(arg.at(i), "(") == nullptr && strpbrk(arg.at(i), "#") == nullptr && strpbrk(arg.at(i), ";") == nullptr) {
                num_arg.push_back(arg.at(i));
              }else{
                k = i - 1;
                break;
              }
            }
            //cout << "here\n";
             if(arg.at(k+1) == NULL){
              //cout << "here\n";
                if(num_arg.empty() == true){
                    return status;
                }
                //num_arg.push_back(arg.at(arg.size()-1));
                char** ARG = new char*[256];
                for(unsigned j = 0; j < num_arg.size(); j++){
                    ARG[j] = num_arg.at(j);
                }
                ARG[num_arg.size()] = NULL;


                Base * SENT = new Command(ARG);
                status = SENT -> execute();
                return status;
            }

            tracker = 1;
            int check = 0;

             if(strpbrk(arg.at(k+1), "\"") != nullptr && check == 0){
            //cout << "here\n";
              string s(arg.at(k+1));
              int count = 0;
              for(unsigned i = 0; i < s.size(); i++){
                if(s.at(i) == '\"'){
                  count++;
                }
              }
              if(count == 2){
                char* temp3 = strtok(arg.at(k + 1), "\"");
                num_arg.push_back(temp3);
                tracker = 1;
                k++;
              }else{
              char * temp = strtok(arg.at(k + 1), "\"");
              num_arg.push_back(temp);
              for(unsigned i = k+2; i < arg.size(); i++){
                if(arg.at(i) == NULL){
                  break;
                }
                if(strpbrk(arg.at(i), "\"") != nullptr){
                  temp = strtok(arg.at(i), "\"");
                  num_arg.push_back(temp);
                    k = i;
                  break;
                }else{
                  num_arg.push_back(arg.at(i));
                }
              }
            }

              char** ARG = new char*[256];
              for(unsigned j = 0; j < num_arg.size(); j++){
                  ARG[j] = num_arg.at(j);
              }
              ARG[num_arg.size()] = NULL;


              Base * SENT = new Command(ARG);
              status = SENT -> execute();
              tracker = 1;
              num_arg.clear();
              num_arg.resize(0);
              check = 1;
              if(arg.at(k+1) == NULL){
                return status;
              }
            }



            if(strpbrk(arg.at(k+1), "(") != nullptr && check == 0){
              check = 1;
              vector<char*> temp;
              char* take = strtok(arg.at(k + 1), "(");
              temp.push_back(take);

              int up = 1;
              int down = 0;
              bool quote = false;

              for(unsigned i = k + 2; i < arg.size(); i++){
                if(arg.at(i) == NULL){
                  cout << "INVALID INPUT\n";
                  return false;
                }

                if(strpbrk(arg.at(i), "\"") != nullptr){
                    quote = !quote;
                    string s(arg.at(i));
                    int count = 0;
                    for(unsigned l = 0; l < s.size(); l++){
                      if(s.at(l) == '\"'){
                        count++;
                      }
                    }
                    if(count == 2){
                      if(s == "\"()\")"){
                        s.pop_back();
                        char *a = &(s[0]);
                        temp.push_back(a);
                        Base* test = new Connector(temp);
                        status = test -> execute();
                        tracker = 1;
                        k = i;
                        break;
                      }else{
                        if(s.at(s.size()-1) == ')'){
                           s.pop_back();
                          char *a = &(s[0]);
                          temp.push_back(a);
                          Base* test = new Connector(temp);
                          status = test -> execute();
                          tracker = 1;
                          k = i;
                          break;
                        }
                      }
                    }

                }

                if(strpbrk(arg.at(i), "(") && quote == false){
                  up++;
                  temp.push_back(arg.at(i));
                }else if(strpbrk(arg.at(i), ")") && quote == false){
                  down++;
                  if(up == down){
                    take = strtok(arg.at(i), ")");
                    temp.push_back(take);
                    Base* test = new Connector(temp);
                    status = test -> execute();
                    tracker = 1;
                    k = i;
                    if(arg.at(k+1) == NULL){
                      return status;
                    }
                    break;
                  }else{
                    temp.push_back(arg.at(i));
                  }
                }else{
                  temp.push_back(arg.at(i));
                }
              }
            } else if(strpbrk(arg.at(k+1), "#") != nullptr && check == 0){
              if(num_arg.empty() == true){
                      char* temp = strtok(arg.at(k), "#");
                      num_arg.push_back(temp);
                    }
              char** ARG = new char*[256];
              for(unsigned j = 0; j < num_arg.size(); j++){
                  ARG[j] = num_arg.at(j);
              }
              ARG[num_arg.size()] = NULL;


              Base * SENT = new Command(ARG);
              status = SENT -> execute();
              //exit(EXIT_SUCCESS);
              return status;
            }

            else if(strcmp(arg.at(k+1), "test") == 0 && check == 0){
              check = 1;
              for(unsigned i = k +1; i < arg.size(); i++){
                if(arg.at(i) != NULL  && strpbrk(arg.at(i), "\"") == nullptr && strpbrk(arg.at(i), "]") == nullptr && strpbrk(arg.at(i), ";") == nullptr &&  strpbrk(arg.at(i), "&&") == nullptr && strpbrk(arg.at(i), "||") == nullptr && (strpbrk(arg.at(i), "#") == nullptr)) {
                num_arg.push_back(arg.at(i));
                //cout << arg.at(i) << endl;;
                }else{
                  if(arg.at(i) == NULL){
                    k = i - 1;
                    break;
                  }
                  if(strpbrk(arg.at(i), "]")){
                    k = i;
                    break;
                  }else{
                    k = i -1;
                    break;
                  }
                }
              }
              Base* test = new Test(num_arg);
              //cout << "here\n";
              status = test -> execute();
              num_arg.resize(0);

              tracker = 1;
              check = 1;
              if(arg.at(k+1) == NULL){
                return status;
              }
            }
            else if(strpbrk(arg.at(k+1), "[") != nullptr && check == 0){
              check = 1;
              for(unsigned i = k +1; i < arg.size(); i++){
                if(arg.at(i) != NULL  && strpbrk(arg.at(i), "\"") == nullptr && strpbrk(arg.at(i), "]") == nullptr && strpbrk(arg.at(i), ";") == nullptr &&  strpbrk(arg.at(i), "&&") == nullptr && strpbrk(arg.at(i), "||") == nullptr && (strpbrk(arg.at(i), "#") == nullptr)) {
                num_arg.push_back(arg.at(i));
                //cout << arg.at(i) << endl;;
                }else{
                  if(arg.at(i) == NULL){
                    k = i - 1;
                    break;
                  }
                  if(strpbrk(arg.at(i), "]")){
                    k = i;
                    break;
                  }else{
                    k = i -1;
                    break;
                  }
                }
              }
              Base* test = new Test(num_arg);
              //cout << "here\n";
              status = test -> execute();
              num_arg.resize(0);

              tracker = 1;
              check = 1;
              if(arg.at(k+1) == NULL){
                return status;
              }
            }
            else if(strpbrk(arg.at(k+1), ";") != nullptr && check == 0){
              char* temp = strtok(arg.at(k + 1), ";");
                num_arg.push_back(temp);
                k++;
                char** ARG = new char*[256];
                for(unsigned j = 0; j < num_arg.size(); j++){
                    ARG[j] = num_arg.at(j);
                }
                ARG[num_arg.size()] = NULL;


                Base* SENT = new Command(ARG);
                status = SENT -> execute();
                num_arg.clear();
                num_arg.resize(0);
                tracker = 0;
                check = 1;
                if(arg.at(k+1) == NULL){
                return status;
              }
            }
          else if(strpbrk(arg.at(k+1), "\"") != nullptr && check == 0){
            cout << "here\n";
              char * temp = strtok(arg.at(k + 1), "\"");
              num_arg.push_back(temp);
              for(unsigned i = k+2; i < arg.size(); i++){
                if(strpbrk(arg.at(i), "\"") != nullptr){
                  temp = strtok(arg.at(i), "\"");
                  num_arg.push_back(temp);
                    k = i;
                  break;
                }else{
                  num_arg.push_back(arg.at(i));
                }
              }

              char** ARG = new char*[256];
              for(unsigned j = 0; j < num_arg.size(); j++){
                  ARG[j] = num_arg.at(j);
              }
              ARG[num_arg.size()] = NULL;


              Base * SENT = new Command(ARG);
              status = SENT -> execute();
              tracker = 1;
              num_arg.clear();
              num_arg.resize(0);
              check = 1;
              if(arg.at(k+1) == NULL){
                return status;
              }
            }

            char** ARg = new char*[256];
            if(check == 0){
            for(unsigned g = 0; g < num_arg.size(); g++){
              if(strpbrk(num_arg.at(g), ";")){
                char* temp = strtok(num_arg.at(g), ";");
                tracker = 0;
                ARg[g] = temp;
                ARg[g+1] = NULL;
                Base * SENt = new Command(ARg);
                //cout << ARg[0] << endl;
                status = SENt -> execute();
                num_arg.clear();
                num_arg.resize(0);
                check = 1;
                break;
              }else{
                ARg[g] = num_arg.at(g);
              }
            }
          }
            if(check == 0){
              ARg[num_arg.size()] = NULL;
              Base * SENt = new Command(ARg);
            //cout << ARg[0] << endl;
              status = SENt -> execute();
              num_arg.clear();
              num_arg.resize(0);
              if(arg.at(k+1) == NULL){
                return status;
              }
            }
            //k++;

            if(k + 1 == arg.size()){
              return status;
            }

              }
            else if(status == false){
            num_arg.clear();
            num_arg.resize(0);
            tracker = 1;
            int up = 0;
            int down = 0;

            for(unsigned t = k+1; t < arg.size(); t++){
              if(arg.at(t) == NULL){
                return status;
              }else if(strpbrk(arg.at(t), "\"") != nullptr){
                for(unsigned i = t + 1; i < arg.size(); i++){
                  if(arg.at(i) == NULL){
                    return status;
                  }
                  if(strpbrk(arg.at(i), "\"") != nullptr){
                    t = i;
                    break;
                  }
                }
                k = t;
                break;
              }else if(strpbrk(arg.at(t), "#") != nullptr){
                return status;
              }else if(strpbrk(arg.at(t), ";") != nullptr){
                k = t;
                break;
              }else if(strpbrk(arg.at(t), "(") != nullptr){
                up++;
                for(unsigned l = t + 1; l < arg.size(); l++){
                  if(strpbrk(arg.at(l), "(") != nullptr){
                    up++;
                  }else if(strpbrk(arg.at(l), ")") != nullptr){
                    down++;
                    if(up == down){
                      k = l;
                      break;
                    }
                  }
                }
                break;
              }else if(strpbrk(arg.at(t), "||") != nullptr){
                k = t;
                break;
              }
            }

      }
    }



///////////////////////////////////////////////////////////////////////////////


          else if(strpbrk(arg.at(k), "||") != nullptr){
            if(tracker == 0){
            char** ARG = new char*[256];
            for(unsigned j = 0; j < num_arg.size(); j++){
              ARG[j] = num_arg.at(j);
              if(j + 1 >= num_arg.size()){
                ARG[j+1] = NULL;
                break;
              }
            }

            Base * SENT = new Command(ARG);
            status = SENT -> execute();
            num_arg.clear();
            num_arg.resize(0);
            tracker = 1;
            //cout << "DID IT\n";
          }
          if(status == false){
            num_arg.resize(0);
            for(unsigned i = k + 1; i < arg.size() /*&& k < arg.size()*/; i++){
              if(arg.at(i) != NULL && strpbrk(arg.at(i), "\"") == nullptr && strcmp(arg.at(i), "&&") != 0  && strpbrk(arg.at(i), "||") == nullptr && strcmp(arg.at(i), "test") != 0 && strpbrk(arg.at(i), "[") == nullptr && strpbrk(arg.at(i), "(") == nullptr && strpbrk(arg.at(i), "#") == nullptr && strpbrk(arg.at(i), ";") == nullptr) {
                num_arg.push_back(arg.at(i));
              }else{
                k = i - 1;
                break;
              }
            }
            //cout << "here\n";
             if(arg.at(k+1) == NULL){
              //cout << "here\n";
                if(num_arg.empty() == true){
                    return status;
                }
                //num_arg.push_back(arg.at(arg.size()-1));
                char** ARG = new char*[256];
                for(unsigned j = 0; j < num_arg.size(); j++){
                    ARG[j] = num_arg.at(j);
                }
                ARG[num_arg.size()] = NULL;


                Base * SENT = new Command(ARG);
                status = SENT -> execute();
                return status;
            }

            tracker = 1;
            int check = 0;

             if(strpbrk(arg.at(k+1), "\"") != nullptr && check == 0){
            //cout << "here\n";
              string s(arg.at(k+1));
              int count = 0;
              for(unsigned i = 0; i < s.size(); i++){
                if(s.at(i) == '\"'){
                  count++;
                }
              }
              if(count == 2){
                char* temp3 = strtok(arg.at(k + 1), "\"");
                num_arg.push_back(temp3);
                tracker = 1;
                k++;
              }else{
              char * temp = strtok(arg.at(k + 1), "\"");
              num_arg.push_back(temp);
              for(unsigned i = k+2; i < arg.size(); i++){
                if(strpbrk(arg.at(i), "\"") != nullptr){
                  temp = strtok(arg.at(i), "\"");
                  num_arg.push_back(temp);
                    k = i;
                  break;
                }else{
                  num_arg.push_back(arg.at(i));
                }
              }
            }

              char** ARG = new char*[256];
              for(unsigned j = 0; j < num_arg.size(); j++){
                  ARG[j] = num_arg.at(j);
              }
              ARG[num_arg.size()] = NULL;


              Base * SENT = new Command(ARG);
              status = SENT -> execute();
              tracker = 1;
              num_arg.clear();
              num_arg.resize(0);
              check = 1;
              if(arg.at(k+1) == NULL){
                return status;
              }
            }



            if(strpbrk(arg.at(k+1), "(") != nullptr && check == 0){
              check = 1;
              int up = 1;
              int down = 0;
              bool quote = false;
              vector<char*> temp;
              char* take = strtok(arg.at(k + 1), "(");
              temp.push_back(take);



              for(unsigned i = k + 2; i < arg.size(); i++){
                if(arg.at(i) == NULL){
                  cout << "INVALID INPUT\n";
                  return false;
                }

               if(strpbrk(arg.at(i), "\"")){
                    quote = !quote;
                    string s(arg.at(i));
                    int count = 0;
                    for(unsigned l = 0; l < s.size(); l++){
                      if(s.at(l) == '\"'){
                        count++;
                      }
                    }
                    if(count == 2){
                      if(s == "\"()\")"){
                        s.pop_back();
                        char *a = &(s[0]);
                        temp.push_back(a);
                        Base* test = new Connector(temp);
                        status = test -> execute();
                        tracker = 1;
                        k = i;
                        break;
                      }else{
                        if(s.at(s.size()-1) == ')'){
                           s.pop_back();
                          char *a = &(s[0]);
                          temp.push_back(a);
                          Base* test = new Connector(temp);
                          status = test -> execute();
                          tracker = 1;
                          k = i;
                          break;
                        }
                      }
                    }

                }

                if(strpbrk(arg.at(i), "(") && quote == false){
                  up++;
                  temp.push_back(arg.at(i));
                }else if(strpbrk(arg.at(i), ")") && quote == false){
                  down++;
                  if(up == down){
                    take = strtok(arg.at(i), ")");
                    temp.push_back(take);
                    Base* test = new Connector(temp);
                    status = test -> execute();
                    tracker = 1;
                    k = i;
                    if(arg.at(k+1) == NULL){
                      return status;
                    }
                    break;
                  }else{
                    temp.push_back(arg.at(i));
                  }
                }else{
                  temp.push_back(arg.at(i));
                }
              }
            } else if(strpbrk(arg.at(k+1), "#") != nullptr && check == 0){
              if(num_arg.empty() == true){
                      char* temp = strtok(arg.at(k), "#");
                      num_arg.push_back(temp);
                    }
              char** ARG = new char*[256];
              for(unsigned j = 0; j < num_arg.size(); j++){
                  ARG[j] = num_arg.at(j);
              }
              ARG[num_arg.size()] = NULL;


              Base * SENT = new Command(ARG);
              status = SENT -> execute();
              //exit(EXIT_SUCCESS);
              return status;
            }

            else if(strcmp(arg.at(k+1), "test") == 0 && check == 0){
              check = 1;
              for(unsigned i = k +1; i < arg.size(); i++){
                if(arg.at(i) != NULL  && strpbrk(arg.at(i), "\"") == nullptr && strpbrk(arg.at(i), "]") == nullptr && strpbrk(arg.at(i), ";") == nullptr &&  strpbrk(arg.at(i), "&&") == nullptr && strpbrk(arg.at(i), "||") == nullptr && (strpbrk(arg.at(i), "#") == nullptr)) {
                num_arg.push_back(arg.at(i));
                //cout << arg.at(i) << endl;;
                }else{
                  if(arg.at(i) == NULL){
                    k = i - 1;
                    break;
                  }
                  if(strpbrk(arg.at(i), "]")){
                    k = i;
                    break;
                  }else{
                    k = i -1;
                    break;
                  }
                }
              }
              Base* test = new Test(num_arg);
              //cout << "here\n";
              status = test -> execute();
              num_arg.resize(0);

              tracker = 1;
              check = 1;
              if(arg.at(k+1) == NULL){
                return status;
              }
            }
            else if(strpbrk(arg.at(k+1), "[") != nullptr && check == 0){
              check = 1;
              for(unsigned i = k +1; i < arg.size(); i++){
                if(arg.at(i) != NULL  && strpbrk(arg.at(i), "\"") == nullptr && strpbrk(arg.at(i), "]") == nullptr && strpbrk(arg.at(i), ";") == nullptr &&  strpbrk(arg.at(i), "&&") == nullptr && strpbrk(arg.at(i), "||") == nullptr && (strpbrk(arg.at(i), "#") == nullptr)) {
                num_arg.push_back(arg.at(i));
                //cout << arg.at(i) << endl;;
                }else{
                  if(arg.at(i) == NULL){
                    k = i - 1;
                    break;
                  }
                  if(strpbrk(arg.at(i), "]")){
                    k = i;
                    break;
                  }else{
                    k = i -1;
                    break;
                  }
                }
              }
              Base* test = new Test(num_arg);
              //cout << "here\n";
              status = test -> execute();
              num_arg.resize(0);

              tracker = 1;
              check = 1;
              if(arg.at(k+1) == NULL){
                return status;
              }
            }
            else if(strpbrk(arg.at(k+1), ";") != nullptr && check == 0){
              char* temp = strtok(arg.at(k + 1), ";");
                num_arg.push_back(temp);
                k++;
                char** ARG = new char*[256];
                for(unsigned j = 0; j < num_arg.size(); j++){
                    ARG[j] = num_arg.at(j);
                }
                ARG[num_arg.size()] = NULL;


                Base* SENT = new Command(ARG);
                status = SENT -> execute();
                num_arg.clear();
                num_arg.resize(0);
                tracker = 0;
                check = 1;
                if(arg.at(k+1) == NULL){
                return status;
              }
            }
          else if(strpbrk(arg.at(k+1), "\"") != nullptr && check == 0){
            cout << "here\n";
              char * temp = strtok(arg.at(k + 1), "\"");
              num_arg.push_back(temp);
              for(unsigned i = k+2; i < arg.size(); i++){
                if(strpbrk(arg.at(i), "\"") != nullptr){
                  temp = strtok(arg.at(i), "\"");
                  num_arg.push_back(temp);
                    k = i;
                  break;
                }else{
                  num_arg.push_back(arg.at(i));
                }
              }

              char** ARG = new char*[256];
              for(unsigned j = 0; j < num_arg.size(); j++){
                  ARG[j] = num_arg.at(j);
              }
              ARG[num_arg.size()] = NULL;


              Base * SENT = new Command(ARG);
              status = SENT -> execute();
              tracker = 1;
              num_arg.clear();
              num_arg.resize(0);
              check = 1;
              if(arg.at(k+1) == NULL){
                return status;
              }
            }

            char** ARg = new char*[256];
            if(check == 0){
            for(unsigned g = 0; g < num_arg.size(); g++){
              if(strpbrk(num_arg.at(g), ";")){
                char* temp = strtok(num_arg.at(g), ";");
                tracker = 0;
                ARg[g] = temp;
                ARg[g+1] = NULL;
                Base * SENt = new Command(ARg);
                //cout << ARg[0] << endl;
                status = SENt -> execute();
                num_arg.clear();
                num_arg.resize(0);
                check = 1;
                break;
              }else{
                ARg[g] = num_arg.at(g);
              }
            }
          }
            if(check == 0){
              ARg[num_arg.size()] = NULL;
              Base * SENt = new Command(ARg);
            //cout << ARg[0] << endl;
              status = SENt -> execute();
              num_arg.clear();
              num_arg.resize(0);
              if(arg.at(k+1) == NULL){
                return status;
              }
            }
            //k++;

            if(k + 1 == arg.size()){
              return status;
            }

              }
            else if(status == true){
                  num_arg.clear();
            num_arg.resize(0);
            tracker = 1;
            int up = 0;
            int down = 0;

            for(unsigned t = k+1; t < arg.size(); t++){
              if(arg.at(t) == NULL){
                return status;
              }else if(strpbrk(arg.at(t), "\"") != nullptr){
                for(unsigned i = t + 1; i < arg.size(); i++){
                  if(arg.at(i) == NULL){
                    return status;
                  }
                  if(strpbrk(arg.at(i), "\"") != nullptr){
                    t = i;
                    break;
                  }
                }
                k = t;
                break;
              }else if(strpbrk(arg.at(t), "#") != nullptr){
                return status;
              }else if(strpbrk(arg.at(t), ";") != nullptr){
                k = t;
                break;
              }else if(strpbrk(arg.at(t), "(") != nullptr){
                up++;
                for(unsigned l = t + 1; l < arg.size(); l++){
                  if(strpbrk(arg.at(l), "(") != nullptr){
                    up++;
                  }else if(strpbrk(arg.at(l), ")") != nullptr){
                    down++;
                    if(up == down){
                      k = l;
                      break;
                    }
                  }
                }
                break;
              }else if(strpbrk(arg.at(t), "&&") != nullptr){
                k = t;
                break;
              }
            }

      }
        }

        }
        return status;
}

  virtual vector<char*> getArg(){
    return arg;
  }

  void exe(char** ARG, int &status){
    if(strcmp(ARG[0], "exit") == 0){
      exit(EXIT_SUCCESS);
    }
    pid_t child = fork();
     if(child < 0){
         perror("ERROR IN FORKING PROCESS");
         exit(EXIT_FAILURE);

    }else if(child == 0){
        if(execvp(ARG[0], ARG) < 0){
          status = 1;
        }
    }
    else{
        if(waitpid(child, NULL, 0) < 0){
          perror("INTERNAL ERROR");
          //exit(EXIT_FAILURE);
        }
    }
    //
  }

  virtual char** Get_ARG(){
      return argv;
    }

};

#endif
