#include <fstream>
#include <cstdlib>
#include <iostream>
#include "classes.hpp"

int main(){
  cout<<"created"<<flush;
container a(0);
a.containerCreate();

a.resourceInsert("config.json","config.json");
a.resourceInsert("main","/executable/main");
a.resourceExtract("output","output");
a.containerExecute();
a.containerStop();
a.containerRemove();
}
