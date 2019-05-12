#include "../include/Utilities.h"

#include <cstdlib>
#include <iostream>

#define INT_MAX_DIGITS 9

using namespace std;

uint Utilities::get_uint(){
	string str;
	uint index = 0;
	uint num;
	cin>>str;
	while(index < str.size()){
		if(isdigit(str[index])){
			break;
		}
		++index;
	}
	if(index < str.size()){
		str = str.substr(index, INT_MAX_DIGITS);
		num = stoi(str);
	} else{
		num = 0;
	}
	return num;
}
