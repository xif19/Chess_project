/**
* Cette classe Piece gere les attributs d'une piece d'echec comme sa couleur et son type.
* \file   Piece.cpp
* \author Maxence Grondin, Thomas Thibodeau et Matthew Hantar
* \date  21 avril 2024
* Créé le 1er avril 2024
*/

#include "Piece.h"

namespace modele {
	Piece::Piece(Color color, Type type) {
		color_ = color;
		type_ = type;
	}
}