#pragma once
/**
* Cette classe gere les attributs d'une box et son contenu.
* \file   Box.h
* \author Maxence Grondin, Thomas Thibodeau et Matthew Hantar
* \date  21 avril 2024
* Cr�� le 1er avril 2024
*/

#include "Piece.h"
#include <memory>

using namespace std;
namespace modele {
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
}

