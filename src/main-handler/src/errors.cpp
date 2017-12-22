#include<string.h>
#include "../inc/errors.hpp"

using namespace std;

char errorName[lasti][32];

void errorSetNames(){
	strcpy(errorName[database_driver_defined], "DRIVER ALREADY DEFINED");
	strcpy(errorName[database_no_driver], "NO DRIVER FOR DATABASE");
	strcpy(errorName[database_no_connection], "NO CONNECTION TO DATABASE");
}
