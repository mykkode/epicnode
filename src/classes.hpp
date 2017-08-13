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

using json = nlohmann::json;
using namespace std;

/**
 *  The localTimer class will handle the time the evaluated program spent until now
 */
class testHandler{
private:
  int testNumber,k;
  char testBase[25];
public:
  testHandler(char* textBasePointer);
  bool pushTest(int test);
  bool pullOutput(int test);
};
testHandler::testHandler(char* textBasePointer){
  strcpy(testBase, textBasePointer);
  k=strlen(testBase);
}
bool testHandler::pushTest(int test)
{
  char testPath[36];
  sprintf(testPath, "input/%s%i.in", testBase,test);

  ifstream infile(testPath);
  if(infile.good()){
    infile.close();
    char destinationPath[40];
    sprintf(destinationPath, "executable/%s.in", testBase);
    rename(testPath, destinationPath);
    return true;
  }
  return false;
}

bool testHandler::pullOutput(int test)
{
  char outputPath[41];
  sprintf(outputPath, "executable/%s.out", testBase);
cout<<outputPath;
  ifstream infile(outputPath);
  if(infile.good()){
    infile.close();
    char destinationPath[38];
    sprintf(destinationPath, "output/%s%i.out", testBase,test);
    rename(outputPath, destinationPath);
    return true;
  }
  return false;
}

class localTimer{
private:
  int64_t a;
  int64_t b;
public:
  localTimer();
  void timeUpdate();
  void timeRestart();
  int getTime();
};

localTimer::localTimer(){
  a=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
  b=a;
}
void localTimer::timeUpdate(){
  b=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}
void localTimer::timeRestart(){
  a=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
  b=a;
}
int localTimer::getTime(){
  return b-a;
}

/**
 *  The handlerConfig class will handle the configuration and parameters that the evaluated program has to follow
 */
  class configHandler{
private:
  json executed, config;
  int k;
  char testBase[25];
  fstream out,in;
public:
  configHandler();
  int getMaxTime();
  int getMaxMemory();
  int getNumberOfTests();
  char *getTestBase();
  void testFail(int test, int testTime, const char reason[]);
  void testSuccess(int test, int testTime, int testMemory);
  void end();
};

configHandler::configHandler(){
  out.open("raport.json", fstream::out);
  in.open("config.json", fstream::in);

  in>>config;

  executed["executed"]=true;
  if(config["jobId"].is_null() || config["numberOfTests"].is_null() || config["testBase"].is_null() || config["problemId"].is_null() || config["maxTime"].is_null()){
    executed["executed"]=false;
    end();
    exit(0);
  }
  else{
    cout<<"Job Id:"<<config["jobId"]<<'\n';
    cout<<"Tests number:"<<config["numberOfTests"]<<'\n';
    cout<<"Test base:"<<config["testBase"]<<'\n';
    cout<<"Problem Id:"<<config["problemId"]<<'\n';

    executed["jobId"]=config["jobId"];
    executed["numberOfTests"]=config["numberOfTests"];
    executed["testBase"]=config["testBase"];
    executed["problemId"]=config["problemId"];
  }
  ;
  string tb = config["testBase"];
  strcpy(testBase,tb.c_str());
  k=strlen(testBase);

  testBase[k+1]=0;
  for(int i=0; i<executed["numberOfTests"]; i++){
    testBase[k]=i+'0';
    executed["tests"][testBase]["executed"]=false;
    executed["tests"][testBase]["time"]=-1;
    executed["tests"][testBase]["halted"]=true;
    executed["tests"][testBase]["haltReason"]="Not ran yet";
  }
  testBase[k]=0;
}
int configHandler::getMaxTime(){
  return config["maxTime"];
}
int configHandler::getNumberOfTests(){
  return config["numberOfTests"];
}
int configHandler::getMaxMemory(){
  return config["maxMemory"];
}
char* configHandler::getTestBase(){
  return testBase;
}
void configHandler::testFail(int test, int testTime, const char reason[]){
  testBase[k]=test+'0';
  executed["tests"][testBase]["executed"]=true;
  executed["tests"][testBase]["time"]=testTime;
  executed["tests"][testBase]["halted"]=true;
  executed["tests"][testBase]["haltReason"]=reason;

  cout<<endl<<"Raport Test: "<<test<<endl;
  cout<<"Halted: "<<reason<<endl;
}

void configHandler::testSuccess(int test, int testTime, int testMemory){
  testBase[k]=test+'0';
  executed["tests"][testBase]["executed"]=true;
  executed["tests"][testBase]["time"]=testTime;
  executed["tests"][testBase]["halted"]=false;
  executed["tests"][testBase]["haltReason"]="None";

  cout<<endl<<"Raport Test: "<<test<<endl;
  cout<<"Mem: "<<testMemory<<endl;
  cout<<"Time: "<<testTime<<endl;
  cout<<"Response: "<<"OK!"<<endl;
}

void configHandler::end(){
  out<<setw(4)<<executed<<flush<<endl;
}

/**
 *  The memoryHandler class will handle the amount of memory used by the evaluated program at any time.
 */
class memoryHandler{
private:
  int64_t max;
  int64_t act;
  char location[64];
public:
  memoryHandler(pid_t  pid);
  void refresh();
  int val();
};
memoryHandler::memoryHandler(pid_t  pid){
  sprintf(location, "/proc/%d/statm", pid);

  ifstream mem(location);
  mem>>act;
  mem.close();

  max = act;
}
void memoryHandler::refresh(){
  ifstream mem(location);
  mem>>act;
  mem.close();

  if(max<act){
    max=act;
  }
}
int memoryHandler::val(){
  return max*sysconf(_SC_PAGESIZE)/1000;
}
