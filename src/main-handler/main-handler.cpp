#include <fstream>
#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include "classes.hpp"

int main(){
  cout<<"created"<<flush;
container a(0);

a.containerCreate();
a.resourceInsert("config.json","config.json");
a.resourceInsert("main","/executable/main");
a.containerExecute();
a.resourceExtract("raport.json","raport.json");
a.containerStop();
a.containerRemove();
}
