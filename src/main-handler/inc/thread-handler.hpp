using namespace std;

#ifndef THREADHANDLER_H
#define THREADHANDLER_H

#include <vector>
#include <thread>       // multiple threads
#include <unistd.h>		//sleep
#include "access-handler.hpp"

class threadHandler{
private:
	vector < thread > threads;
	vector < int > status;
	vector <int> list;
	accessHandler * ah;
	int locked, NUMBER_OF_THREADS;
public:
	threadHandler(accessHandler * localAh, int NOT);
	void spawnThreads();
	void threadFlow(int threadId);
	void insertJob(int jid);
	void finishJob();
	void finalizeThreads();
	int getJob();
	int available();
};

#endif