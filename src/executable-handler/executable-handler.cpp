#include "json.hpp" // will include "rapidjson/rapidjson.h"
#include <string.h>
#include <unistd.h> // things for fork()
#include <iostream> // read and prind to console
#include <fstream> // read and print to files
#include <signal.h> // kill
#include <chrono> // time things
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "classes.hpp"

using json = nlohmann::json;
using namespace std;

configHandler *config;


memoryHandler *usedMem = NULL;

int main(int argc, char const *argv[]) {
config = new configHandler();
testHandler tests(config->getTestBase());

for(int i=0;i<config->getNumberOfTests();i++){
  if(tests.pushTest(i)){
    pid_t  pid;
    bool childStarted = false;
    pid = vfork();

    if(pid == 0){
      chdir("executable");
      childStarted = true;
      execl("main", "main", (char*)NULL);
    }

    if(pid > 0){
      while(!childStarted){}

      usedMem = new memoryHandler(pid);
      localTimer timerTest;
      int stat;

      while (timerTest.getTime() <= config->getMaxTime() && usedMem->val()<=config->getMaxMemory() && !waitpid(pid, &stat, WNOHANG)) {
        usleep(200);
        timerTest.timeUpdate();
        usedMem->refresh();
      }

      kill(pid, SIGTERM);

      if(!(timerTest.getTime() <= config->getMaxTime())){
        config->testFail(i, timerTest.getTime(), "Time limit exceeded!");
      }
      else
      if(!(usedMem->val() <= config->getMaxMemory())){
        config->testFail(i, timerTest.getTime(), "Memory limit exceeded!");
      }
      else
      if(!tests.pullOutput(i)){
        config->testFail(i, timerTest.getTime(), "Output file not found!");
      }
      else{
        config->testSuccess(i, timerTest.getTime(), usedMem->val());
      }
    }
  }
  else{
    config->testFail(i, 0, "Test not found in directory! (General Failure - Contact support)");
  }
}

config->end();
    return 1;
}
