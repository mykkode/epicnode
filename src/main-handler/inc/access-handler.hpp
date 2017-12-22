using namespace std;

#ifndef ACCESSHANDLER_H
#define ACCESSHANDLER_H

#include <mutex>        		//used for locking variables - data race
#include <condition_variable>	//non cpu intensive waiting

class accessHandler{
private:
  condition_variable condition;
public: 
  mutex m;
  void announce(int *x);
  void freeze();
};

#endif