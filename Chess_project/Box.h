#pragma once
#include "Piece.h"
#include <memory>

using namespace std;

class Box 
{
public:

	Box() {
		occupied_ = false;
	}

	Box(shared_ptr<Piece> piece) {
		piece_ = piece;
		occupied_ = true;
	};

private:
	shared_ptr<Piece> piece_;
	bool occupied_;
};

