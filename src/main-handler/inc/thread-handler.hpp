using namespace std;

#ifndef THREADHANDLER_H
#define THREADHANDLER_H

#include <vector>
#include <thread>       // multiple threads

#include "job-handler.hpp"

extern int const NUMBER_OF_THREADS;

class threadHandler{
private:
  vector < thread > threads;
  vector < int > status;
  accessHandler * ah;
  jobHandler * jh;
public:

  threadHandler(accessHandler * localAh);

  void spawnThreads();
  void threadFlow(int threadId);
  int getJob();
};

#endif