#include "../include/Interface.h"

#include "../include/PieceInterface.h"

#include <cstdlib>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class Interface::InterfaceImpl{
	PieceInterface<Pawn> *pawns;
	PieceInterface<Rook> *rooks;
	PieceInterface<Bishop> *bishops;
	PieceInterface<Queen> *queens;
	PieceInterface<Knight> *knights;
	PieceInterface<King> *kings;
	int *board;
	uint x, y;

	template <class T>
	bool algoPlace(PieceInterface<T> *piece, uint xx, uint yy, int n, int fig){
		if(n > piece->getCount()){
			return 1;
		}
		for(uint i = yy*x + xx; i < x*y; ++i){
			uint ny = i/x;
			uint nx = i - x*ny;
			if(isSqFree(nx, ny) == -1){
				cout<<"algoPlace out of board: "<<nx<<' '<<ny;
				exit(EXIT_FAILURE);
			}
			if(!isSqFree(nx, ny)){
				continue;
			}
			if(checkStroke(nx, ny, piece->moveChar()) &&
					checkSquare(nx, ny, piece->moveSquares())){
				markStroke(nx, ny, 1, piece->moveChar());
				markSquare(nx, ny, 1, piece->moveSquares());
				board[i] = piece->getID();
				piece->setLocation(n-1, nx, ny);
				if(countFree() >= fig-1
						&& algoPlace<T>(piece, nx, ny, n+1, fig-1)){
					return 1;
				}
				piece->setLocation(n-1, -1, -1);
				markSquare(nx, ny, -1, piece->moveSquares());
				markStroke(nx, ny, -1, piece->moveChar());
				board[i] = 0;
			}
		}
		return 0;
	}

	bool checkStroke(uint xx, uint yy, int type){
		if(type & 1){
			for(uint i = xx; i < x*y; i += x){
				if(board[i] < 0){
					return 0;
				}
			}
		}
		if(type & 2){
			for(uint i = yy*x; i < (yy+1)*x; i += 1){
				if(board[i] < 0){
					return 0;
				}
			}
		}
		if(type & 4){
			for(uint i = xx; i < x*y; i += x){
				int pos = abs((int)(yy-(i/x)));
				if((int)(xx-pos) >= 0 && board[i-pos] < 0){
					return 0;
				}
				if(xx+pos < x && board[i+pos] < 0){
					return 0;
				}
			}
		}
		return 1;
	}

	bool checkSquare(uint xx, uint yy, vector<pair<int,int> > vec){
		for(uint i = 0; i < vec.size(); ++i){
			if((int)(xx+vec[i].first) >= 0 && xx+vec[i].first < x
			&& (int)(yy+vec[i].second) >= 0 && yy+vec[i].second < y
			&& board[(yy+vec[i].second)*x + xx+vec[i].first] < 0){
				return 0;
			}
		}
		return 1;
	}

	void markStroke(uint xx, uint yy, int v, int type){
		if(type & 1){
			for(uint i = xx; i < x*y; i += x){
				board[i] += v;
			}
		}
		if(type & 2){
			for(uint i = yy*x; i < (yy+1)*x; i += 1){
				board[i] += v;
			}
		}
		if(type & 4){
			for(uint i = xx; i < x*y; i += x){
				int pos = abs((int)(yy-(i/x)));
				if((int)(xx-pos) >= 0){
					board[i-pos] += v;
				}
				if(xx+pos < x){
					board[i+pos] += v;
				}
			}
		}
	}

	void markSquare(uint xx, uint yy, int v, vector<pair<int,int> > vec){
		for(uint i = 0; i < vec.size(); ++i){
			if((int)(xx+vec[i].first) >= 0 && xx+vec[i].first < x
			&& (int)(yy+vec[i].second) >= 0 && yy+vec[i].second < y){
				board[(yy+vec[i].second)*x + xx+vec[i].first] += v;
			}
		}
	}

	int countFree(){
		int fr = 0;
		for(uint i = 0; i < x*y; ++i){
			if(board[i] == 0){
				++fr;
			}
		}
		return fr;
	}

public:

	InterfaceImpl(uint xx, uint yy, uint pa, uint ro,
				uint bi, uint qu, uint kn, uint ki){
		pawns = new PieceInterface<Pawn>(pa);
		rooks = new PieceInterface<Rook>(ro);
		bishops = new PieceInterface<Bishop>(bi);
		queens = new PieceInterface<Queen>(qu);
		knights = new PieceInterface<Knight>(kn);
		kings = new PieceInterface<King>(ki);
		x = xx;
		if(!x){
			x = 1;
		}
		y = yy;
		if(!y){
			y = 1;
		}
		board = new int [x*y] ();
	}

	~InterfaceImpl(){
		delete pawns;
		delete rooks;
		delete bishops;
		delete queens;
		delete knights;
		delete kings;
		delete [] board;
	}

	int isSqFree(uint xx, uint yy){
		if(xx >= x || yy >= y){
			return -1;
		}
		else if(board[yy*x + xx] == 0){
			return 1;
		} else{
			return 0;
		}
	}

	bool algorithm(){
		int fig = pawns->getCount() + rooks->getCount() + bishops->getCount()
				+ kings->getCount() + knights->getCount() + queens->getCount();
		if(algoPlace<King>(kings, 0, 0, 1, fig)
				&& algoPlace<Rook>(rooks, 0, 0, 1, (fig -= kings->getCount()))
				&& algoPlace<Bishop>(bishops, 0, 0, 1, (fig -= rooks->getCount()))
				&& algoPlace<Queen>(queens, 0, 0, 1, (fig -= bishops->getCount()))
				&& algoPlace<Pawn>(pawns, 0, 0, 1, (fig -= queens->getCount()))
				&& algoPlace<Knight>(knights, 0, 0, 1, (fig -= pawns->getCount()))){
			printBoard(0);
			return 1;
		} else{
			cout<<endl<<"Placement impossible!"<<endl;
			return 0;
		}
	}

	void printBoard(bool debug){
		cout<<endl<<"   ";
		for(uint i = 0; i < x; ++i){
			cout<<i%10<<' ';
		}
		cout<<endl;
		for(uint i = 0; i < y; ++i){
			cout<<endl<<i%10<<"  ";
			for(uint j = 0; j < x; ++j){
				if(debug && board[i*x + j] > 0){
					if(board[i*x + j] > 9){
						cout<<'*';
					} else{
						cout<<abs(board[i*x + j])%10;
					}
				}
				else if(board[i*x + j] > 0){
					cout<<'-';
				} else{
					switch(board[i*x + j]){
						case 0:
							cout<<'-';
							break;
						case -10:
							cout<<'P';
							break;
						case -20:
							cout<<'R';
							break;
						case -30:
							cout<<'B';
							break;
						case -40:
							cout<<'Q';
							break;
						case -50:
							cout<<'N';
							break;
						case -60:
							cout<<'K';
							break;
						default:
							cout<<'x';
					}
				}
				cout<<' ';
			}
		}
		cout<<endl;
	}

	void printConfig(){
		cout<<endl;
		cout<<"Width   = "<<x<<endl;
		cout<<"Height  = "<<y<<endl;
		cout<<"Pawns   = "<<pawns->getCount()<<endl;
		cout<<"Rooks   = "<<rooks->getCount()<<endl;
		cout<<"Bishops = "<<bishops->getCount()<<endl;
		cout<<"Queens  = "<<queens->getCount()<<endl;
		cout<<"Knights = "<<knights->getCount()<<endl;
		cout<<"Kings   = "<<kings->getCount()<<endl;
	}
};

Interface::Interface(uint xx, uint yy, uint pa, uint ro,
					uint bi, uint qu, uint kn, uint ki){
	impl = unique_ptr<InterfaceImpl>(new InterfaceImpl(xx, yy, pa, ro,
													bi, qu, kn, ki));
}

Interface::~Interface() = default;

int Interface::isSqFree(uint xx, uint yy){
	return impl->isSqFree(xx, yy);
}

bool Interface::algorithm(){
	return impl->algorithm();
}

void Interface::printBoard(bool debug){
	impl->printBoard(debug);
}

void Interface::printConfig(){
	impl->printConfig();
}
