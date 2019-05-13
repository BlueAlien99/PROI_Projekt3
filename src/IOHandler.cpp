#include "../include/IOHandler.h"

#include <fstream>
#include <iostream>

using namespace std;

void IOHandler::genProblemsTxt(){
	ofstream file("problems.txt");
	if(!file.is_open()){
		cout<<endl<<"This should NOT happen! (IOHandler::genProblemsTxt)";
		return;
	}
	file<<"# Each config must be entered in a new line"<<endl;
	file<<"# Lines starting with '#' will be omitted"<<endl;
	file<<"# All numbers must be non-negative integers"<<endl;
	file<<"# Following info is required (separated by space):"<<endl;
	file<<"# Width Height Pawns Rooks Bishops Queens Knights Kings"<<endl;
	file<<"# W H P R B Q N K"<<endl;
	file<<endl;
	file.close();
}
