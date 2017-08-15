#include <stdlib.h>

using namespace std;

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
