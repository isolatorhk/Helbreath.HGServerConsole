#include <stdio.h>
#include "cApplicationStartup.h"
#include <exception>

int main() {
	try {
		cApplicationStartup *applicationStartup = new cApplicationStartup();
		applicationStartup->Startup();
	}	
	catch(std::exception& e) {
		PutLogList(e.what());
	}
	catch (...) {
		PutLogList("Exception occured");
	}
}