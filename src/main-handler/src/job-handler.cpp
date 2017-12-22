#include "../inc/job-handler.hpp"

jobHandler::jobHandler(accessHandler * localAh){
  ah = localAh;
  locked = 0;
}

int jobHandler::available(){
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
}
int jobHandler::getJob(){
  unique_lock<mutex> locker(ah->m);

  if(n.size()){
    int r = n.back();
    n.pop_back();
    locked++;
    locker.unlock();
    return r;
  }
  else{
    locker.unlock();
    return 0;
  }
}
void jobHandler::finishJob(){
  unique_lock<mutex> locker(ah->m);
  locked --;
  locker.unlock();
}
void jobHandler::insertJob(int jid){
  unique_lock<mutex> locker(ah->m);
  n.push_back(jid);
  locker.unlock();
}