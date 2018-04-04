using namespace std;

#include "../inc/thread-handler.hpp"

threadHandler::threadHandler(accessHandler * localAh, int NOT){
  NUMBER_OF_THREADS = NOT;
  ah = localAh;
  locked = 0;
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
void threadHandler::finalizeThreads(){
  unique_lock<mutex> locker(ah->m);

  while(locked != 0){
    printf("--Thread-h: waiting for working threads: %d\n", locked);
    sleep(1);
  }
  
  ah->announce(NUMBER_OF_THREADS);
  
  locker.unlock();
}
void threadHandler::threadFlow(int threadId){
  printf("----Thread-%i: is starting\n",threadId);
  int job;
  while(1){
    ah -> freeze();
    job = getJob();

    if(job == 0){
      printf("----Thread-%i: thread safe exit\n",threadId);
      return ;
    }
    
    printf("----Thread-%i: taking job %i\n",threadId,job);
  }
}

void threadHandler::insertJob(int jid){
  unique_lock<mutex> locker(ah->m);
  
  list.push_back(jid);
  printf("--Thread-h: inserted Job: %d\n",jid);
  ah->announce(1);

  locker.unlock();
}

void threadHandler::finishJob(){
  unique_lock<mutex> locker(ah->m);
  locked --;
  locker.unlock();
}

int threadHandler::getJob(){
  unique_lock<mutex> locker(ah->m);

  if(list.size()){
    int toReturn = list.back();
    list.pop_back();
    locked++;
    locker.unlock();
    return toReturn;
  }
  else{
    locker.unlock();
    return 0;
  }
  return 0;
}

int threadHandler::available(){
  unique_lock<mutex> locker(ah->m);

  int toReturn;
  
  if(NUMBER_OF_THREADS > locked){
    toReturn =  NUMBER_OF_THREADS - locked;
    locker.unlock();
    return toReturn;
  }
  else{
    locker.unlock();
    return 0;
  }
  return 0;
}
