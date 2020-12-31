#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

void parse (char *input) {
    int totCommands = 0;
    int totalConnectors = 0;
    int totArgs = 0;
    for (int i = 0; i < strlen(input); ++i) {
        if (isalpha(input[i])){
            while (isalpha(input[i])){
                i++;
            }
            totCommands++;
        }
        while(input[i] == ' '){
            i++;
        }
        if (input[i] == '-'){
            i++;
            while (isalpha(input[i])){
                i++;
            }
            totArgs++;
        }
        else if (input[i] == '"'){
            i++;
            while(input[i] != '"'){
                i++;
            }
            totArgs++;
        }
        if (input[i] == ';'){
            totalConnectors++;
        }
        else if (input[i] == '&' && input[i+1] == '&') {
            totalConnectors++;
            i++;
        }
        else if (input[i] == '|' && input[i+1] == '|') {
            totalConnectors++;
            i++;
        }
    
    
    }
    cout << "Total commands: " << totCommands << "\nTotal connectors: " << totalConnectors << endl;
    cout << "Total arguments: " << totArgs << endl;
    
}

