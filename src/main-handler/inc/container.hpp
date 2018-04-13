#ifndef MAIN_HANDLER_CONTAINER_HPP
#define MAIN_HANDLER_CONTAINER_HPP

class container{
private:
  int jobId;
  int exId;
  char str[256];
public:
  container(int, int);
  void containerCreate();
  void jobResourceInsert(const char *,const  char *);
  void jobResourceExtract(const char *,const  char *);
  void exResourceInsert();
  void exResourceExtract();
  void containerStop();
  void containerRemove();
  void containerExecute();
};

#endif //MAIN_HANDLER_CONTAINER_HPP
