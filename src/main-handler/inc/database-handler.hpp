using namespace std;

#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

class preparedStatement{
friend class dataBaseHandler;
private:
  unique_ptr < sql::PreparedStatement > pstmt;
  unique_ptr < sql::ResultSet > result;
public:
  void bindInt(int *i, int *j);
  void bindInt(int i, int *j);
  void bindString(int *i, string j);
  void bindString(int i, string j);
  int next();
  int getInt(string column);
  void execute();
  void executeUpdate();
  void getMoreResults();
};

class dataBaseHandler{
private:
  int state;
  sql::Driver * driver;
  unique_ptr < sql::Connection > connection;
  unique_ptr < sql::PreparedStatement > pstmt;
public:
  dataBaseHandler();
  void begin();
  void connect(string server, string user, string password, string db);
  void prepareStatement(preparedStatement * pslocal, string preparedQuerry);

};

#endif

