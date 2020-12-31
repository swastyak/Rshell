#include <iostream>
#include "../header/Base.hpp"
#include "../header/Command.hpp"
#include "../header/Prompt.hpp"
#include "../header/Connector.hpp"
#include <string>
using namespace std;

int main(int argc, char** argv){
    cout << "$ ";
    char input[256];
    if (argc == 1){
        cin.getline(input, 256);
        while (strcmp(input, "exit")){
            Base* test = new Connector();
            test -> parse(input);
            test -> execute();
            cout << "$ ";
            cin.getline(input, 256);
        }
        return 0;
    }

    for (int i = 1; i < argc; ++i){
        cout << argv[i] << " " << flush;
    }
    cout << endl;
    char str[256];
    int i = 1;
    while (argv[i] != NULL){
        strcat(str, argv[i]);
        strcat(str, " ");
        i++;
    }


    Base * b1 = new Connector();
    b1->parse(str);
    char ** test = b1->Get_ARG();
    b1->execute();

    return 0;
}
//
// char str2 [] = "echo 1 && echo 2 || echo 3";
// Base * b2 = new Connector ();
// b2->parse(str2);
// vector<char*> test = b2->getArg();
// for (int i = 0 ; i  < test.size()- 1; ++i){
//     cout << test[i] << " ";
// }
// cout << std::flush;
//b2->execute();
// using namespace std;
//
// int main(int argc, char** argv){
//     char * str;
//     int i = 1;
//     while (argv[i] != NULL){
//            strcat(str, argv[i]);
//            strcat(str, " ");
//    }
//    cout << str << endl;
//         // Base* test = new Connector();
//         // test -> parse(str);
//         // test -> execute();
//         // return 0;
//   }
