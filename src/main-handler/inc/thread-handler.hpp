using namespace std;

#ifndef THREADHANDLER_H
#define THREADHANDLER_H

#include <vector>
#include <thread>       // multiple threads
#include <unistd.h>		//sleep
#include "access-handler.hpp"

class threadHandler{
private:
	struct compact {
		int jid;
		int eid;
	};
	vector < thread > threads;
	vector < int > status;
	vector < struct compact > list;
	accessHandler * ah;
	int locked, NUMBER_OF_THREADS;

public:
	threadHandler(accessHandler * , int);
	void spawnThreads();
	void threadFlow(int);
	void insertJob(int, int);
	void finishJob();
	void finalizeThreads();
	struct compact getJob();
	int available();
};

#endif