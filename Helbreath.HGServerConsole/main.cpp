#include <stdio.h>
#include "cApplicationStartup.h"

int main() {
	cApplicationStartup *applicationStartup = new cApplicationStartup();
	applicationStartup->Startup();
}