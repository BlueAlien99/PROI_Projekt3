#include "../include/Tests.h"
#include "../include/Setup.h"

#include <cstdlib>
#include <ctime>

int main(){
	std::srand(std::time(0));
	Tests tests;
	tests.run();
	Setup setup;
	setup.help();
	setup.run();
	return 0;
}
