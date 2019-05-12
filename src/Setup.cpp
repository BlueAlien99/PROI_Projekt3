#include "../include/Setup.h"

#include "../include/Utilities.h"
#include "../include/Interface.h"

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
		cout<<endl;
		cout<<"----  MENU  ----"<<endl;
		cout<<"1 - Create new board"<<endl;
		cout<<"2 - Run algorithm"<<endl;
		cout<<"3 - Print board in debug mode"<<endl;
		cout<<"0 - Exit"<<endl;
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
				case 0:
					cout<<"Exiting..."<<endl;
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
		interface->printConfig();
	}

	void algorithm(){
		if(interface){
			interface->algorithm();
		} else{
			cout<<endl<<"Board has not been initialized!"<<endl;
		}
	}

	void printDebBoard(){
		if(interface){
			interface->printBoard(1);
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
