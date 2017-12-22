using namespace std;

#ifndef JOBHANDLER_H
#define JOBHANDLER_H

#include "access-handler.hpp"
#include <vector>

extern int const NUMBER_OF_THREADS;

class jobHandler{

  private:
    int locked;
    accessHandler * ah;
    vector <int> n;

  public:
    jobHandler(accessHandler * localAh);
    int available();
    int getJob();
    void finishJob();
    void insertJob(int jid);
};

#endif