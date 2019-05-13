#include "../include/IOHandler.h"

#include "../include/Interface.h"

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

void IOHandler::solveProblems(){
	ifstream file("problems.txt");
	if(!file.is_open()){
		cout<<endl<<"Could not find \"problems.txt\"...";
		return;
	}
	string line;
	while(!file.eof()){
		getline(file, line);
		if(line[0] == '#' || line.size() == 0){
			continue;
		}
		bool error = 0;
		int data[8] = {0};
		size_t pos = 0;
		for(int i = 0; i < 8; ++i){
			size_t p;
			try{
				if(pos < line.size()){
					data[i] = stoi(line.substr(pos), &p, 10);
				}
			} catch(...){
				error = 1;
				break;
			}
			if(data[i] < 0){
				error = 1;
				break;
			}
			pos += p;
		}
		if(!error){
			Interface board(data[0], data[1], data[2], data[3],
							data[4], data[5], data[6], data[7]);
			board.printConfig();
			board.algorithm();
		}
	}
}
