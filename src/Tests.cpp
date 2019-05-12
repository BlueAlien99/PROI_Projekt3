#include "../include/Tests.h"

#include "../include/Interface.h"

//#define NDEBUG

#include <cassert>
#include <iostream>

using namespace std;

void Tests::run(){
	char c;
	cout<<"Do you want to run self test? (y/n)"<<endl;
	cin.get(c);
	if(c == 'y'){
		assert(test1());
		assert(test2());
		assert(test3());
		assert(!test4());
		assert(test5());
	}
}

bool Tests::test1(){
	cout<<endl<<"**** BEGINNING OF TEST 1 ****"<<endl;
	Interface interface(6, 6, 2, 0, 6, 0, 2, 0);
	interface.printConfig();
	bool ret = interface.algorithm();
	cout<<endl<<"Expected: POSSIBLE"<<endl;
	cout<<endl<<"**** END OF TEST 1 ****"<<endl;
	return ret;
}

bool Tests::test2(){
	cout<<endl<<"**** BEGINNING OF TEST 2 ****"<<endl;
	Interface interface(5, 4, 0, 1, 0, 0, 1, 4);
	interface.printConfig();
	bool ret = interface.algorithm();
	cout<<endl<<"Expected: POSSIBLE"<<endl;
	cout<<endl<<"**** END OF TEST 2 ****"<<endl;
	return ret;
}

bool Tests::test3(){
	cout<<endl<<"**** BEGINNING OF TEST 3 ****"<<endl;
	Interface interface(3, 5, 10);
	interface.printConfig();
	bool ret = interface.algorithm();
	cout<<endl<<"Expected: POSSIBLE"<<endl;
	cout<<endl<<"**** END OF TEST 3 ****"<<endl;
	return ret;
}

bool Tests::test4(){
	cout<<endl<<"**** BEGINNING OF TEST 4 ****"<<endl;
	Interface interface(6, 6, 0, 0, 0, 7, 0, 0);
	interface.printConfig();
	bool ret = interface.algorithm();
	cout<<endl<<"Expected: IMPOSSIBLE"<<endl;
	cout<<endl<<"**** END OF TEST 4 ****"<<endl;
	return ret;
}

bool Tests::test5(){
	cout<<endl<<"**** BEGINNING OF TEST 5 ****"<<endl;
	Interface interface(8, 8, 7, 2, 2, 1, 2, 1);
	interface.printConfig();
	bool ret = interface.algorithm();
	cout<<endl<<"Expected: POSSIBLE"<<endl;
	cout<<endl<<"**** END OF TEST 5 ****"<<endl;
	return ret;
}
