#ifndef MAIN_HANDLER_PROCESS_HPP
#define MAIN_HANDLER_PROCESS_HPP

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fstream>
#include "../dependencies/json.hpp"

class evaluator {
private:
    int jobID;
    int exerciseID;
    int numberOfTests;
    char testBase[32];
    char buffer[128];
    nlohmann::json raport;

public:
    evaluator();
    void dec();
    void enc();
    void setValues(int, int);
    int evaluate();
};

#endif //MAIN_HANDLER_PROCESS_HPP
