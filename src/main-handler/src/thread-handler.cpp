using namespace std;

#include "../inc/thread-handler.hpp"
#include "../inc/container.hpp"

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

  while(1){
    ah -> freeze();
      struct compact job = getJob();

    if(job.jid == 0){
      printf("----Thread-%i: thread safe exit\n",threadId);
      return ;
    }
    printf("----Thread-%i: taking job %d, exercise type %d\n",threadId,job.jid, job.eid);
    container * local = new container(job.jid, job.eid);
    local->containerCreate();
    local->jobResourceInsert("main","executable/");
    local->jobResourceInsert("config.json","");
    local->exResourceInsert();
    local->containerExecute();
    local->containerStop();
    local->jobResourceExtract("raport.json", "");
    local->exResourceExtract();
    local->containerRemove();
    printf("----Thread-%i: finished  job %i\n",threadId,job.jid);
    finishJob();

  }
}

void threadHandler::insertJob(int jid, int eid){
  unique_lock<mutex> locker(ah->m);

  struct compact local;
  local.jid = jid;
  local.eid = eid;

  list.push_back(local);
  printf("--Thread-h: inserted Job: %d\n",jid);
  ah->announce(1);

  locker.unlock();
}

void threadHandler::finishJob(){
  unique_lock<mutex> locker(ah->m);
  locked --;
  locker.unlock();
}

struct threadHandler::compact threadHandler::getJob(){
  unique_lock<mutex> locker(ah->m);

  if(list.size()){
    struct compact toReturn = list.back();
    list.pop_back();
    locked++;
    locker.unlock();
    return toReturn;
  }
  locker.unlock();
  struct compact local;
  local.eid = 0;
  local.jid = 0;
  return local;

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
