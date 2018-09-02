//
// Created by mykkode on 04.05.2018.
//

#ifndef MAIN_HANDLER_PROCESS_HPP
#define MAIN_HANDLER_PROCESS_HPP

#include <stdio.h>
#include <unistd.h>

class newProcess{
    private:
        int jobId;
        int exId;
        int PID;
    public:
        newProcess();
        void setValues(int, int);
        int evaluate();
};

#endif //MAIN_HANDLER_PROCESS_HPP
