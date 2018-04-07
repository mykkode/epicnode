
#include "../inc/database-handler.hpp"
#include "../inc/thread-handler.hpp"
#include <stdio.h>
#include <csignal>      //signals (ex: sigterm)
#include <wait.h>       //wait for pid
#include <unistd.h>     //fork and things
#include <stdlib.h>     //things for malloc, free and others
#include <iostream>
#include <string>
#include "../inc/errors.hpp"

using namespace std;

#define VERSION 1
#define BUILD 228
#define TITLE "EPICNODE - INGENNUS"

int const NUMBER_OF_THREADS = 2;
int state = 1;
/*
class container{
private:
  int jobId;
  char str[256];
public:
  container(int jobIdLocal);
  void containerCreate();
  void resourceInsert(const char from[],const  char to[]);
  void resourceExtract(const char from[],const  char to[]);
  void containerStop();
  void containerRemove();
  void containerExecute();
};
container::container(int jobIdLocal){
jobId=jobIdLocal;
printf("OK\n");
}
void container::containerCreate(){
  sprintf(str, "sudo docker run -itd --name id%i mykkode/epicnode", jobId);
  system(str);
}
void container::resourceInsert(const char from[], const char to[]){
  sprintf(str, "sudo docker cp /var/epicnode/jobs/%i/%s id%i:/var/epicnode/executable-handler/%s", jobId, from, jobId, to);
  system(str);
}
void container::resourceExtract(const char from[], const char to[]){
  sprintf(str, "sudo docker cp id%i:/var/epicnode/executable-handler/%s /var/epicnode/jobs/%i/%s", jobId, from, jobId, to);
  system(str);
}
void container::containerStop(){
  sprintf(str, "sudo docker stop id%i", jobId);
  system(str);
}
void container::containerRemove(){
  sprintf(str, "sudo docker rm id%i", jobId);
  system(str);
}
void container::containerExecute(){
  sprintf(str, "sudo docker exec id%i /bin/sh -f /var/epicnode/start.sh", jobId);
  system(str);
}
*/

/*class accessHandler{
private:
  condition_variable condition;
public:
  mutex m;
  void announce(int *x){
    for(int i=1 ; i<=*x ; i++){
      condition.notify_one();
    }
  }
  void freeze(){
    unique_lock<mutex> locker(m);
    condition.wait(locker);
    locker.unlock();
  }
};*/

void signalHandler( int SIGRECV){
  if(SIGRECV == SIGTERM){
    printf("--Thread-h: Intrerrupt signal %i received\n",SIGRECV);

    state = 0;
  }
}

int main(){
  printf("%s VERSION %d BUILD %d\n\n",TITLE, VERSION, BUILD);

  pid_t PID;
  PID = fork();

  if(PID){
    printf("Daemon: daemon is starting\n");
    printf("Daemon: ready to receive commands\n");

    string command;

    while(getline(cin, command)){
      if(command == "stop"){
        int endsts;
        printf("Daemon: initiating termination of thread handler\n");
        kill(PID, SIGTERM);
        waitpid(PID, &endsts, WUNTRACED);
        printf("Daemon: thread handler process terminated\n");
        printf("Daemon: termination\n");
        exit(SIGTERM);
      }
      else printf("Daemon: Unknown command\n");
    }
  } else {
    printf("--Thread-h: thread handler is starting\n");

    printf("--Thread-h: setting signals\n");
    signal(SIGTERM, signalHandler);

    accessHandler * ah = new accessHandler;
    dataBaseHandler * dbh = new dataBaseHandler;
    threadHandler * th = new threadHandler(ah, (int)NUMBER_OF_THREADS);

    printf("--Thread-h: initiating threads\n");
    th->spawnThreads();

    printf("--Thread-h: connecting to database\n");

    int JID, SID;
    try{

      dbh->begin();
      dbh->connect("tcp://127.0.0.1:3306", "epicUser", "devtest", "epic");

      preparedStatement * ps = new preparedStatement;

      dbh->prepareStatement(ps, "SELECT `startServerSession`(?) AS `startServerSession`;");

      ps->bindString(1, "testServer");
      ps->execute();

      if(ps->next()){
        SID = ps->getInt("startServerSession");
      }

      delete ps;
    }
     catch (sql::SQLException &e) {
       cout << "# ERR: SQLException in " << __FILE__;
       cout << "(" << __FUNCTION__ << ") on line "
          << __LINE__ << endl;
       cout << "# ERR: " << e.what();
       cout << " (MySQL error code: " << e.getErrorCode();
       cout << ", SQLState: " << e.getSQLState() << " )" << endl;
     }
     catch (int &e){
       cout<< errorName[e]<<endl;
     }
    catch(...){
      printf("NOT OK");
    }

    try{
      preparedStatement * ps = new preparedStatement;
      dbh->prepareStatement(ps, "CALL `getJobs`(?, ?);");

      ps->bindInt(1,SID);
      ps->bindInt(2,(int)NUMBER_OF_THREADS);

      while(state){
        ps->bindInt(2, th->available());
        ps->execute();

        while(ps->next()){
          JID = ps->getInt("id");
          printf("--Thread-h: new job: %d\n",JID);
          th->insertJob(JID);
        }
        ps->getMoreResults();
        usleep(1000);

      }
      delete ps;

      th->finalizeThreads();
      exit(SIGTERM);

    }
    catch(...){
        printf("FINAL THROWN");
    }
  }
}
