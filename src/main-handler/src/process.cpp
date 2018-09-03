//
// Created by mykkode on 04.05.2018.
//
using namespace std;

#include "../inc/process.hpp"

newProcess::newProcess(){
    jobId = 0;
    exId = 0;
    PID = 0;
}
newProcess::setValues(int job, int exercie){
    jobId = job;
    exId = exercie;
}
newProcess::evaluate(){
    pid_t PID = fork();
}
