#pragma once
#include "Piece.h"
#include <memory>

using namespace std;

class Box
{
public:
	Box() : piece_(nullptr), occupied_(false) {}

	Box(shared_ptr<Piece> piece) : piece_(piece), occupied_(true) {}

	//Getters
	shared_ptr<Piece> getPiece() const;

	void setPiece(shared_ptr<Piece> piece);

	bool isOccupied() const;


private:
	shared_ptr<Piece> piece_;
	bool occupied_;
};

