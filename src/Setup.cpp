#include "../include/Setup.h"

#include "../include/Utilities.h"
#include "../include/Interface.h"
#include "../include/IOHandler.h"

#include <cstdlib>
#include <iostream>
#include <memory>

using namespace std;

class Setup::SetupImpl{
	Interface *interface;

public:

	SetupImpl(){
		interface = NULL;
	}

	~SetupImpl(){
		delete interface;
	}

	void help(){
		system("clear");
		cout<<endl;
		cout<<"----  MENU  ----"<<endl;
		cout<<"1   - Create new board"<<endl;
		cout<<"2   - Run algorithm"<<endl;
		cout<<"3   - Print board in debug mode"<<endl;
		cout<<"20  - Solve problems from \"problems.txt\""<<endl;
		cout<<"21  - Solve problems using brute-force"<<endl;
		cout<<"22  - Generate \"problems.txt\" with help"<<endl;
		cout<<"123 - HELP!"<<endl;
		cout<<"357 - Remove app-related *.txt files"<<endl;
		cout<<"0   - Exit"<<endl;
	}

	void run(){
		uint menu = 1;
		while(menu){
			cout<<endl<<"Back to menu..."<<endl;
			switch((menu = Utilities::get_uint())){
				case 1:
					newBoard();
					break;
				case 2:
					algorithm();
					break;
				case 3:
					printDebBoard();
					break;
				case 20:
					IOHandler::solveProblems(0);
					break;
				case 21:
					IOHandler::solveProblems(1);
					break;
				case 22:
					IOHandler::genProblemsTxt();
					break;
				case 0:
					cout<<"Exiting..."<<endl;
					break;
				case 123:
					help();
					break;
				case 357:
					IOHandler::cleanup();
					break;
				default:
					cout<<"Not available!"<<endl;
					break;
			}
		}
	}

	void newBoard(){
		if(interface){
			delete interface;
		}
		cout<<endl<<"Enter following info:";
		cout<<endl<<"Width Height Pawns Rooks Bishops Queens Knights Kings";
		cout<<endl<<"W H P R B Q N K"<<endl;
		uint x = Utilities::get_uint();
		uint y = Utilities::get_uint();
		uint pa = Utilities::get_uint();
		uint ro = Utilities::get_uint();
		uint bi = Utilities::get_uint();
		uint qu = Utilities::get_uint();
		uint kn = Utilities::get_uint();
		uint ki = Utilities::get_uint();
		interface = new Interface(x, y, pa, ro, bi, qu, kn, ki);
		cout<<interface->getConfigStr();
	}

	void algorithm(){
		if(interface){
			interface->algorithm(1);
		} else{
			cout<<endl<<"Board has not been initialized!"<<endl;
		}
	}

	void printDebBoard(){
		if(interface){
			cout<<interface->getBoardStr(1);
		} else{
			cout<<endl<<"Board has not been initialized!"<<endl;
		}
	}
};

Setup::Setup(){
	impl = unique_ptr<SetupImpl>(new SetupImpl());
}

Setup::~Setup() = default;

void Setup::help(){
	impl->help();
}

void Setup::run(){
	impl->run();
}

void Setup::newBoard(){
	impl->newBoard();
}

void Setup::algorithm(){
	impl->algorithm();
}

void Setup::printDebBoard(){
	impl->printDebBoard();
}
