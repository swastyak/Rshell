#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <cstdlib>
#include <time.h>
#include "parse.hpp"
using namespace std;

int main (int argc, char * argv[]){
    char inputString [1000];
    cout << "$ " ;
    cin.getline(inputString, 256);
    parse(inputString);
    
        pid_t process = fork();
          if (process == 0){
               cout << "child process ";
               cout <<process << endl;    
           }
           else {
                 waitpid(0, NULL, WUNTRACED);
                 cout << "parent process" <<process <<  endl;
           }
                                                            
	char * execvpTest [3];
 	char * input1 = "echo";
	char * input2 = "\"HelloWorld\"";
	execvpTest[0] = input1;
	execvpTest[1] = input2;
	execvpTest[2] = NULL;
	if (execvp(execvpTest[0], execvpTest) == -1){
		perror("execvp");
	}
	
    return 0;
}
