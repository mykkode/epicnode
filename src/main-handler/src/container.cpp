#include <stdlib.h>     //fork and things
#include <stdio.h>
#include "../inc/container.hpp"

container::container(int jidLocal, int eidLocal){
    exId=eidLocal;
    jobId=jidLocal;
    printf("OK\n");
}
void container::preprocessing(){
    sprintf(str, "sudo g++ -g /var/epicnode/jobs/%d/main.cpp -o /var/epicnode/jobs/%d/main", jobId, jobId);
    system(str);
}
void container::containerCreate(){
    sprintf(str, "sudo docker run -itd --name id%i mykkode/epicnode", jobId);
    system(str);
}
void container::exResourceInsert(){
    sprintf(str, "sudo docker cp /var/epicnode/ex/%i/input/ id%i:/var/epicnode/executable-handler/", exId, jobId);
    system(str);
}
void container::exResourceExtract(){
    sprintf(str, "sudo docker cp id%i:/var/epicnode/executable-handler/output/ /var/epicnode/jobs/%i/", jobId, jobId);
    system(str);
}
void container::jobResourceInsert(const char from[], const char to[]){
    sprintf(str, "sudo docker cp /var/epicnode/jobs/%i/%s id%i:/var/epicnode/executable-handler/%s", jobId, from, jobId, to);
    system(str);
}
void container::jobResourceExtract(const char from[], const char to[]){
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
