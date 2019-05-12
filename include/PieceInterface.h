#ifndef PIECEINTERFACE_H
#define PIECEINTERFACE_H

#include "Piece.h"

#include <cstdlib>
#include <vector>

template <class T>
class PieceInterface{
	std::vector<T*> pieces;
public:
	PieceInterface(int n = 0);
	~PieceInterface();
	int getID();
	void setLocation(uint n, int x, int y);
	std::pair<int,int> getLocation(uint n);
	int moveChar();
	std::vector<std::pair<int,int> > moveSquares();
	int getCount();
};

#endif
