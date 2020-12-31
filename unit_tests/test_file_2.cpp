#include "gtest/gtest.h"
#include "../header/Base.hpp"
#include "../header/Prompt.hpp"
#include "../header/Command.hpp"
#include "../header/Connector.hpp"
//execute returns a bool

TEST(CommandRuns, Single_Arg_Should_Execute_return_true){
    char str[] = "echo helloworld";
    Base * b1 = new Command();
    b1->parse(str);
    bool ran_successfully = b1->execute();
    EXPECT_EQ(ran_successfully, true);

}
TEST(CommandRuns, Single_BadArg_Should_Execute_return_False){
    char str[] = "false";
    Base * b1 = new Command();
    b1->parse(str);
    bool ran_successfully = b1->execute();

    EXPECT_EQ(ran_successfully, false);
}

TEST(CommandRuns, Connector_Test_should_return_true){
    char str [] = "false || ls";
    Base * bw = new Connector();
    bw->parse(str);
    bool ran_successfully = bw->execute();
    EXPECT_EQ(ran_successfully, true);
}

TEST(CommandRuns, Connector_test_should_return_false_2){
    char str [] = "false && ls;";
    Base * bw = new Connector();
    bw->parse(str);
    bool ran_successfully = bw->execute();
    EXPECT_EQ(ran_successfully, false);
}

TEST(PrecedenceTests, Precedence_test_sample){
    char str [] = "(echo a && echo b) || (echo c && echo d)";
    Base * bw = new Connector();
    bw->parse(str);
    bool ran_successfully = bw->execute();
    EXPECT_EQ(ran_successfully, true);

}


TEST(PrecedenceTests, Long_Precedence_test_sample){
    char str [] = "((echo a || ls) && (echo a || ls)) || (echo a || ls) && (echo a || ls) && (echo a || ls) && (echo a || ls) && (echo a || ls) && (echo a || ls) && (echo a || ls) && (echo a || ls)";
    Base * bw = new Connector();
    bw->parse(str);
    bool ran_successfully = bw->execute();
    EXPECT_EQ(ran_successfully, true);

}

TEST(PrecedenceTests, Command_test_sample){
    char str [] = "test names.txt";
    Base * bw = new Connector();
    bw->parse(str);
    bool ran_successfully = bw->execute();
    EXPECT_EQ(ran_successfully, true);

}

TEST(PrecedenceTests, Command_flag_test_sample){
    char str [] = "test -f names.txt";
    Base * bw = new Connector();
    bw->parse(str);
    bool ran_successfully = bw->execute();
    EXPECT_EQ(ran_successfully, true);

}

TEST(PrecedenceTests, Command_incorrect_flag_test_sample){
    char str [] = "test -d names.txt";
    Base * bw = new Connector();
    bw->parse(str);
    bool ran_successfully = bw->execute();
    EXPECT_EQ(ran_successfully, 0);
}

TEST(PrecedenceTests, Command_flag_test_sample_2){
    char str [] = "test -d src";
    Base * bw = new Connector();
    bw->parse(str);
    bool ran_successfully = bw->execute();
    EXPECT_EQ(ran_successfully, 1);
}

TEST(PrecedenceTests, Command_incorrect_flag_test_sample_2){
    char str [] = "test -f src";
    Base * bw = new Connector();
    bw->parse(str);
    bool ran_successfully = bw->execute();
    EXPECT_EQ(ran_successfully, 0);
}
