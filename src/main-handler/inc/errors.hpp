using namespace std;

#ifndef ERRORS_H
#define ERRORS_H

enum errors:int{
	database_driver_defined, database_no_driver, database_no_connection, lasti
};

extern char errorName[lasti][32];

void errorSetNames();

#endif