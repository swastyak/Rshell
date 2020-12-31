#ifndef TEST_HPP
#define TEST_HPP

#include "Base.hpp"
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <iostream>
#include <cstring>
#include <cstdlib>
 #include <sys/wait.h>
#include <sys/stat.h>
 #include <vector>

using namespace std;

class Test : public Base{
	private:
		vector<char*> testers;
	public:

	Test(vector<char*> v){
		for(unsigned i = 0; i < v.size(); i++){
			testers.push_back(v.at(i));
		}
	}

	virtual void add(Base*){

	}
    virtual void parse(char command[128]){

    }
    virtual bool execute(){

    	struct stat buffer;

    	//cout << testers.at(0) << endl << testers.at(1) << endl;


    	if(strcmp(testers.at(1), "-e") == 0){

   			if(stat(testers.at(2), &buffer) == 0){
    				cout << "(true)\n";
    				return true;
    			}else{
    				cout << "(false)\n";
    				return false;
    			}
    		}
    	else if(strcmp(testers.at(1), "-f") == 0){
    		stat(testers.at(2), &buffer);
    		if(stat(testers.at(2), &buffer) == 0){
    			//cout << "here\n";
    			if(S_ISREG(buffer.st_mode) == true){
    				cout << "(true)\n";
    				return true;
    			}else{
    				cout << "(false)\n";
    				return false;
    			}
    	}

    		cout << "(false)\n";
    		return false;

    	}
    	else if(strcmp(testers.at(1), "-d") == 0){
    		stat(testers.at(2), &buffer);
    		if(stat(testers.at(2), &buffer) == 0){
    			if(S_ISDIR(buffer.st_mode) == true){
    				cout << "(true)\n";
    				return true;
    			}else{
    				cout << "(false)\n";
    				return false;
    			}
    	}

    		cout << "(false)\n";
    		return false;
    	}else{
    		//cout << "here\n";
    		char* temp = testers.at(1);
   			if(stat(temp, &buffer) == 0){
    				cout << "(true)\n";
    				return true;
    			}else{
    				cout << "(false)\n";
    				return false;
    			}
    	}




    }
    virtual char** Get_ARG(){
    	char** temp;
    	return temp;
    }
    virtual vector<char*> getArg(){
    	return testers;
    }
};

#endif
