#include "../inc/access-handler.hpp"

void accessHandler::announce(int *x){
  for(int i=1 ; i<=*x ; i++){
    condition.notify_one();
  }
}
void accessHandler::freeze(){
  unique_lock<mutex> locker(m);
  condition.wait(locker);
  locker.unlock();
}