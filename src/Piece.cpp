#include "../include/Piece.h"

#include <vector>

using namespace std;

Piece::Moves::Moves()
: id(-100), count(1), v(0), h(0), d(0) {}

Piece::Piece(){
	mv = new Moves();
	loc = make_pair(-1, -1);
}

Piece::~Piece(){
	if(--mv->count == 0){
		delete mv;
	}
}

Piece::Piece(const Piece &piece){
	mv = piece.mv;
	++mv->count;
	loc = piece.loc;
}

int Piece::getID(){
	return mv->id;
}

void Piece::setLocation(int x, int y){
	loc = make_pair(x, y);
}

std::pair<int,int> Piece::getLocation(){
	return make_pair(loc.first, loc.second);
}

int Piece::moveChar(){
	return mv->v + 2*mv->h + 4*mv->d;
}

vector<pair<int,int> > Piece::moveSquares(){
	return mv->sq;
}

int Piece::getRelativeValue(){
	return -1;
}

Pawn::Pawn(){
	mv->id = -10;
	mv->sq.push_back(make_pair(1, 1));
	mv->sq.push_back(make_pair(1, -1));
	mv->sq.push_back(make_pair(-1, -1));
	mv->sq.push_back(make_pair(-1, 1));
}

int Pawn::getRelativeValue(){
	return 1;
}

Rook::Rook(){
	mv->id = -20;
	mv->v = 1;
	mv->h = 1;
}

int Rook::getRelativeValue(){
	return 5;
}

Bishop::Bishop(){
	mv->id = -30;
	mv->d = 1;
}

int Bishop::getRelativeValue(){
	return 3;
}

Queen::Queen(){
	mv->id = -40;
	mv->v = 1;
	mv->h = 1;
	mv->d = 1;
}

int Queen::getRelativeValue(){
	return 9;
}

Knight::Knight(){
	mv->id = -50;
	mv->sq.push_back(make_pair(1, 2));
	mv->sq.push_back(make_pair(2, 1));
	mv->sq.push_back(make_pair(2, -1));
	mv->sq.push_back(make_pair(1, -2));
	mv->sq.push_back(make_pair(-1, -2));
	mv->sq.push_back(make_pair(-2, -1));
	mv->sq.push_back(make_pair(-2, 1));
	mv->sq.push_back(make_pair(-1, 2));
}

int Knight::getRelativeValue(){
	return 3;
}

King::King(){
	mv->id = -60;
	mv->sq.push_back(make_pair(0, 1));
	mv->sq.push_back(make_pair(1, 1));
	mv->sq.push_back(make_pair(1, 0));
	mv->sq.push_back(make_pair(1, -1));
	mv->sq.push_back(make_pair(0, -1));
	mv->sq.push_back(make_pair(-1, -1));
	mv->sq.push_back(make_pair(-1, 0));
	mv->sq.push_back(make_pair(-1, 1));
}
