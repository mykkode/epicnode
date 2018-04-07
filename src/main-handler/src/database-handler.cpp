#include "../inc/database-handler.hpp"
#include "../inc/errors.hpp"

void preparedStatement::bindInt(int i, int j){
    pstmt->setInt(i, j);
}
void preparedStatement::bindString(int *i, string j){
    pstmt->setString(*i, j);
}
void preparedStatement::bindString(int i, string j){
    pstmt->setString(i, j);
}
int preparedStatement::next(){
    return result->next();
}
int preparedStatement::getInt(string column){
    return result->getInt(column);
}
void preparedStatement::execute(){
    result.reset(pstmt->executeQuery());
}
void preparedStatement::executeUpdate(){
    pstmt->executeUpdate();
}
void preparedStatement::getMoreResults(){
    if (pstmt->getMoreResults())
    {
        result.reset(pstmt->getResultSet());
    }
}


dataBaseHandler::dataBaseHandler(){
    state = 0;
    // 0 = nothing done
    // 1 = got driver instance
    // 2 = connected
}
  void dataBaseHandler::begin(){
    if(state != 0){
      throw(database_driver_defined);
    }
    else{
      driver = get_driver_instance();
      state = 1;
    }
  }
  void dataBaseHandler::connect(string server, string user, string password, string db){
    if(state != 1){
      throw(database_no_driver);
    }
    try{
      connection.reset(driver->connect(server, user, password));
      connection->setSchema(db);

      state = 2;
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
      printf("~~~THROWN~~~ DATABASE-HANDLER.CPP - CONNECT");
    }
  }
//
  void dataBaseHandler::prepareStatement(preparedStatement * psLocal, string preparedQuerry){
    if(state!=2){
      throw(database_no_connection);
    }
    else{
      try{
        psLocal->pstmt.reset(connection->prepareStatement(preparedQuerry));
      }
      catch(...){
        printf("~~~THROWN~~~ DATABASE-HANDLER.CPP - PREPARE STATEMENT");
      }
    }
  }

