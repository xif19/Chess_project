#include "Box.h"

shared_ptr<Piece> Box::getPiece() const {
	return piece_;
}

void Box::setPiece(shared_ptr<Piece> piece) {
	piece_ = piece;
	occupied_ = (piece != nullptr);
}

bool Box::isOccupied() const {
	return occupied_;
}