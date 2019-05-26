#ifndef PIECE_H
#define PIECE_H

#include <vector>

class Piece{
protected:
	struct Moves{
		int id;
		int count;
		bool v, h, d;
		std::vector<std::pair<int,int> > sq;
		Moves();
	};
	Moves *mv;
	std::pair<int,int> loc;
public:
	Piece();
	virtual ~Piece();
	Piece(const Piece &piece);
	int getID();
	void setLocation(int x, int y);
	std::pair<int,int> getLocation();
	int moveChar();
	std::vector<std::pair<int,int> > moveSquares();
	virtual int getRelativeValue();
};

class Pawn: public Piece{
public:
	Pawn();
	int getRelativeValue();
};

class Rook: public Piece{
public:
	Rook();
	int getRelativeValue();
};

class Bishop: public Piece{
public:
	Bishop();
	int getRelativeValue();
};

class Queen: public Piece{
public:
	Queen();
	int getRelativeValue();
};

class Knight: public Piece{
public:
	Knight();
	int getRelativeValue();
};

class King: public Piece{
public:
	King();
};

#endif
