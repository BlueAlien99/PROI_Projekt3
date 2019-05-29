#include "../include/Interface.h"

#include "../include/PieceInterface.h"
#include "../include/IOHandler.h"
#include "../include/Utilities.h"

#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>
#include <vector>
#include <set>

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

	bool algoBrute(){
		bool result = 0;
		set<string> perms;
		cout<<endl<<"Generating permutations..."<<endl;
		try{
			Utilities::getPermutations(getConfigStrChain(), &perms);
		} catch(string ex){
			cout<<endl<<ex<<endl;
			return 0;
		} catch(...){
			return 0;
		}
		int pass = 0;
		for(auto i = perms.begin(); i != perms.end(); ++i){
			cout<<"Algorithm pass "<<++pass<<" out of "<<perms.size();
			cout<<": "<<*i<<endl;
			delete [] board;
			board = new int [x*y] ();
			string str = *i;
			bool success = 1;
			int set = 0;
			for(auto j = str.begin(); j != str.end(); ++j){
				switch(*j){
					case 'P':
						{
							PieceInterface<Pawn> inPa(1);
							success = algoPlace(&inPa, 0, 0, 1, str.size()-set);
						}
						break;
					case 'R':
						{
							PieceInterface<Rook> inRo(1);
							success = algoPlace(&inRo, 0, 0, 1, str.size()-set);
						}
						break;
					case 'B':
						{
							PieceInterface<Bishop> inBi(1);
							success = algoPlace(&inBi, 0, 0, 1, str.size()-set);
						}
						break;
					case 'Q':
						{
							PieceInterface<Queen> inQu(1);
							success = algoPlace(&inQu, 0, 0, 1, str.size()-set);
						}
						break;
					case 'K':
						{
							PieceInterface<King> inKi(1);
							success = algoPlace(&inKi, 0, 0, 1, str.size()-set);
						}
						break;
					case 'N':
						{
							PieceInterface<Knight> inKn(1);
							success = algoPlace(&inKn, 0, 0, 1, str.size()-set);
						}
						break;
					default:
						cout<<"Fatal error (algoBrute)"<<endl;
						exit(EXIT_FAILURE);
				}
				if(!success){
					break;
				}
				++set;
			}
			if(success){
				result = 1;
				break;
			}
		}
		return result;
	}

	bool algorithmFindSolution(bool interact, bool batch, bool result, int *flag){
		if(interact && !batch){
			vector<int> data;
			try{
				IOHandler::findSolution(getConfigStrPlain(), &data);
				if(x*y != data.size()){
					throw 404;
				}
				*flag = 0;
				for(uint i = 0; i < x*y; ++i){
					board[i] = data[i];
				}
			} catch(int er){
				if(er == 100){
					*flag = 1;
				}
			} catch(...){
				// Do nothing
			}
		}
		if(*flag == 0 || *flag == 1){
			cout<<endl<<"Solution imported from \"solutions.txt\"!"<<endl;
			if(*flag == 0){
				cout<<getBoardStr();
				result = 1;
			}
			else if(*flag == 1){
				cout<<endl<<"Placement impossible!"<<endl;
				result = 0;
			}
			char c;
			cout<<endl<<"Run algorithm anyway? (y/n)"<<endl;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin.get(c);
			if(c == 'y'){
				*flag = -1;
			}
		}
		return result;
	}

	bool algorithmBruteAndExport(bool interact, bool batch, bool result){
		bool brute = 0;
		if(interact && !batch && !result){
			char c;
			cout<<endl<<"Use brute-force? (y/n)"<<endl;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin.get(c);
			if(c == 'y'){
				brute = 1;
			}
		}
		if(brute || (interact && batch && !result)){
			result = algoBrute();
			if(result){
				cout<<getBoardStr();
			} else{
				cout<<endl<<"Placement impossible!"<<endl;
			}
			IOHandler::saveSolution(result, getConfigStrPlain(), getBoardStrPlain());
		}
		bool save = 0;
		if(interact && !batch){
			char c;
			cout<<endl<<"Export results? (y/n)"<<endl;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin.get(c);
			if(c == 'y'){
				save = 1;
			}
		}
		if(batch || save){
			IOHandler::exportVisualised(result, getConfigStr(), getBoardStr());
		}
		return result;
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

	string getBoardStrPlain(){
		string str = "";
		for(uint i = 0; i < x*y; ++i){
			str += to_string(board[i]) + ' ';
		}
		str = str.substr(0, str.size()-1);
		return str;
	}

	string getConfigStrPlain(){
		string str = "";
		str += to_string(x) + ' ' + to_string(y);
		str += ' ' + to_string(pawns->getCount());
		str += ' ' + to_string(rooks->getCount());
		str += ' ' + to_string(bishops->getCount());
		str += ' ' + to_string(queens->getCount());
		str += ' ' + to_string(knights->getCount());
		str += ' ' + to_string(kings->getCount());
		return str;
	}

	string getConfigStrChain(){
		string pa = string(pawns->getCount(), 'P');
		string ro = string(rooks->getCount(), 'R');
		string bi = string(bishops->getCount(), 'B');
		string qu = string(queens->getCount(), 'Q');
		string kn = string(knights->getCount(), 'N');
		string ki = string(kings->getCount(), 'K');
		return pa+ro+bi+qu+kn+ki;
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
		} else if(x > 100){
			x = 100;
		}
		y = yy;
		if(!y){
			y = 1;
		} else if(y > 100){
			y = 100;
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

	bool algorithm(bool interact, bool batch){
		bool result = 0;
		int flag = -1;
		result = algorithmFindSolution(interact, batch, result, &flag);
		if(flag != 0 && flag != 1){
			delete [] board;
			board = new int [x*y] ();
			int fig = pawns->getCount() + rooks->getCount() + bishops->getCount()
					+ kings->getCount() + knights->getCount() + queens->getCount();
			if(algoPlace<King>(kings, 0, 0, 1, fig)
					&& algoPlace<Rook>(rooks, 0, 0, 1, (fig -= kings->getCount()))
					&& algoPlace<Bishop>(bishops, 0, 0, 1, (fig -= rooks->getCount()))
					&& algoPlace<Queen>(queens, 0, 0, 1, (fig -= bishops->getCount()))
					&& algoPlace<Pawn>(pawns, 0, 0, 1, (fig -= queens->getCount()))
					&& algoPlace<Knight>(knights, 0, 0, 1, (fig -= pawns->getCount()))){
				cout<<getBoardStr();
				result = 1;
			} else{
				cout<<endl<<"Placement impossible!"<<endl;
				result = 0;
			}
			IOHandler::saveSolution(result, getConfigStrPlain(), getBoardStrPlain());
		}
		result = algorithmBruteAndExport(interact, batch, result);
		return result;
	}

	string getBoardStr(bool debug = 0){
		string str = "";
		str += "\n   ";
		for(uint i = 0; i < x; ++i){
			str += to_string(i%10) + ' ';
		}
		str += '\n';
		for(uint i = 0; i < y; ++i){
			str += '\n' + to_string(i%10) + "  ";
			for(uint j = 0; j < x; ++j){
				if(debug && board[i*x + j] > 0){
					if(board[i*x + j] > 9){
						str += '*';
					} else{
						str += to_string(abs(board[i*x + j])%10);
					}
				}
				else if(board[i*x + j] > 0){
					str += '-';
				} else{
					switch(board[i*x + j]){
						case 0:
							str += '-';
							break;
						case -10:
							str += 'P';
							break;
						case -20:
							str += 'R';
							break;
						case -30:
							str += 'B';
							break;
						case -40:
							str += 'Q';
							break;
						case -50:
							str += 'N';
							break;
						case -60:
							str += 'K';
							break;
						default:
							str += 'x';
					}
				}
				str += ' ';
			}
		}
		str += '\n';
		return str;
	}

	string getConfigStr(){
		string str = "";
		str += '\n';
		str += "Width   = " + to_string(x) + '\n';
		str += "Height  = " + to_string(y) + '\n';
		str += "Pawns   = " + to_string(pawns->getCount()) + '\n';
		str += "Rooks   = " + to_string(rooks->getCount()) + '\n';
		str += "Bishops = " + to_string(bishops->getCount()) + '\n';
		str += "Queens  = " + to_string(queens->getCount()) + '\n';
		str += "Knights = " + to_string(knights->getCount()) + '\n';
		str += "Kings   = " + to_string(kings->getCount()) + '\n';
		return str;
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

bool Interface::algorithm(bool interact, bool batch){
	return impl->algorithm(interact, batch);
}

string Interface::getBoardStr(bool debug){
	return impl->getBoardStr(debug);
}

string Interface::getConfigStr(){
	return impl->getConfigStr();
}
