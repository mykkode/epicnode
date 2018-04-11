#ifndef MAIN_HANDLER_CONTAINER_HPP
#define MAIN_HANDLER_CONTAINER_HPP

class container{
private:
  int jobId;
  char str[256];
public:
  container(int jobIdLocal);
  void containerCreate();
  void resourceInsert(const char *,const  char *);
  void resourceExtract(const char *,const  char *);
  void containerStop();
  void containerRemove();
  void containerExecute();
};

#endif //MAIN_HANDLER_CONTAINER_HPP
