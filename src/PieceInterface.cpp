#include "../include/PieceInterface.h"

#include "../include/Piece.h"

#include <cstdlib>
#include <vector>

using namespace std;

template <class T>
PieceInterface<T>::PieceInterface(int n){
	if(n > 0){
		pieces.push_back(new T);
	}
	while(--n > 0){
		pieces.push_back(new T(*pieces[0]));
	}
}

template <class T>
PieceInterface<T>::~PieceInterface(){
	while(pieces.size()){
		delete pieces.back();
		pieces.pop_back();
	}
}

template <class T>
int PieceInterface<T>::getID(){
	if(pieces.size() > 0){
		return pieces[0]->getID();
	}
	return -100;
}

template <class T>
void PieceInterface<T>::setLocation(uint n, int x, int y){
	if(n < pieces.size()){
		pieces[n]->setLocation(x, y);
	}
}

template <class T>
pair<int,int> PieceInterface<T>::getLocation(uint n){
	if(n < pieces.size()){
		return pieces[n]->getLocation();
	}
	return make_pair(-2, -2);
}

template <class T>
int PieceInterface<T>::moveChar(){
	if(pieces.size() > 0){
		return pieces[0]->moveChar();
	}
	return -1;
}

template <class T>
vector<pair<int,int> > PieceInterface<T>::moveSquares(){
	if(pieces.size() > 0){
		return pieces[0]->moveSquares();
	}
	vector<pair<int,int> > vec;
	return vec;
}

template <class T>
int PieceInterface<T>::getCount(){
	return pieces.size();
}

template class PieceInterface<Pawn>;
template class PieceInterface<Rook>;
template class PieceInterface<Bishop>;
template class PieceInterface<Queen>;
template class PieceInterface<Knight>;
template class PieceInterface<King>;
