#include "../include/Tests.h"
#include "../include/Setup.h"

int main(){
	Tests tests;
	tests.run();
	Setup setup;
	setup.help();
	setup.run();
	return 0;
}
