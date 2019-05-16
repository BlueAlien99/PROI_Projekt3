#include "../include/Utilities.h"

#include <cstdlib>
#include <iostream>
#include <string>
#include <set>

#define INT_MAX_DIGITS 9
#define STR_MAX_LENGTH 11

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

void Utilities::getPermutations(string str, set<string> *perms, uint lock){
	if(str.size() > STR_MAX_LENGTH){
		string thr = "String longer than " + to_string(STR_MAX_LENGTH) + '!';
		throw thr;
	}
	if(lock >= str.size()-1){
		perms->insert(str);
		return;
	}
	for(uint i = lock; i < str.size(); ++i){
		string stri = str;
		iter_swap(stri.begin()+lock, stri.begin()+i);
		getPermutations(stri, perms, lock+1);
	}
}
