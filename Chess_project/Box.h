#pragma once

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
		//Setters
		void setPiece(shared_ptr<Piece> piece);

		/**
	   * Returns true if the case is occupied by a piece
	   *
	   * @param void:
	   *
	   * @return void:
	   */
		bool isOccupied() const;


	private:
		shared_ptr<Piece> piece_;
		bool occupied_;
	};
}

