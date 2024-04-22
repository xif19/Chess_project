/**
* Cette classe gere les attributs d'une box et son contenu.
* \file   Box.h
* \author Maxence Grondin, Thomas Thibodeau et Matthew Hantar
* \date  21 avril 2024
* Créé le 1er avril 2024
*/

#include "Box.h"

namespace modele {
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
}