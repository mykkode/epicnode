using namespace std;

#include "../inc/thread-handler.hpp"

threadHandler::threadHandler(accessHandler * localAh){
  ah = localAh;
}
void threadHandler::spawnThreads(){
  unique_lock<mutex> locker(ah->m);

  int i;
  for(i=0 ; i<NUMBER_OF_THREADS ; i++){
    threads.push_back(std::thread(&threadHandler::threadFlow,this, i));
    threads[i].detach();
  }
  
  locker.unlock();
}
void threadHandler::threadFlow(int threadId){
  printf("----Thread-%i: is starting\n",threadId);
  while(1){
    ah -> freeze();
    printf("----Thread-%i: %i\n",1, getJob());
  }
}
int threadHandler::getJob(){
  unique_lock<mutex> locker(ah->m);
  int job;
  job = jh -> getJob();
  locker.unlock();
  return job;
}