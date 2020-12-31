#include "gtest/gtest.h"
#include "../header/Base.hpp"
#include "../header/Prompt.hpp"
#include "../header/Command.hpp"
#include "../header/Connector.hpp"

TEST(ParserTest, Single_ls_command_And_Argument){
    char str [] = "ls -a";
    Base * b1 = new Command();
    b1->parse(str);
    char ** test = b1->Get_ARG();
    char str2 [] = "ls";

    EXPECT_STREQ(test[0],str2 );
}

TEST(ParserTest, Test_arg_With_Connectors_in_Argument){
    char str [] = "echo \"I am echoing with || and && and they should not be included as connectors but as a part of the arg\"";
    Base * b2 = new Connector();
    char comparestr[] = "||";
    b2->parse(str);
    vector <char*> test = b2->getArg();
    // cout << std::endl << test[1] << std::endl;
    // cout << comparestr << endl;
    EXPECT_STREQ(test[5], comparestr);
}

TEST(ParserTest, See_All_connectors_Accounted_for){
    char str [] = "echo 1 && echo 2 || ls; echo 4";
    Base *b2 = new Connector();
    char comparestr[] = "&&";
    b2->parse(str);
    vector <char*> test = b2->getArg();
    EXPECT_STREQ(test[2], comparestr);
}

TEST(ParserTest, Single_test_command_And_Argument){
    char str [] = "test -d ../rshell";
    Base * b1 = new Command();
    b1->parse(str);
    char ** test = b1->Get_ARG();
    char str2 [] = "test";

    EXPECT_STREQ(test[0],str2 );
}

TEST(ParserTest, Flag_test_command_And_Argument){
    char str [] = "test -d ../rshell";
    Base * b1 = new Command();
    b1->parse(str);
    char ** test = b1->Get_ARG();
    char str2 [] = "-d";
    EXPECT_STREQ(test[1],str2 );
}




int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
