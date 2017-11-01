#include "easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

int main(int argc, const char** argv) {
	easyloggingpp::Configurations confFromFile("myconfiguration_file");  // Load configuration from file
	easyloggingpp::Loggers::reconfigureAllLoggers(confFromFile); // Re-configures all the loggers to current configuration file

	LOG(TRACE)   << "***** trace log  *****";  
	LOG(DEBUG)   << "***** debug log  *****";  
	LOG(ERROR)   << "***** error log  *****";  
	LOG(WARNING) << "***** warning log  *****";  
	LOG(INFO)    << "***** info log  *****";  

	return 0;
}

