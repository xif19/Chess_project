#pragma once
/**
* Cette classe Piece gere les attributs d'une piece d'echec comme sa couleur et son type.
* \file   Piece.h
* \author Maxence Grondin, Thomas Thibodeau et Matthew Hantar
* \date  21 avril 2024
* Créé le 1er avril 2024
*/
enum class Type { KING, QUEEN, PAWN, BISHOP, KNIGHT, ROOK };
enum class Color {BLACK, WHITE};

//Type : KING, QUEEN, PAWN, BISHOP, KNIGHT, ROOK
//Color : BLACK, WHITE
namespace modele {
	class Piece
	{
	public:
		Piece(Color color, Type type);
		~Piece() {};

		//Getters
		Type getType() {
			return type_;
		}

		Color getColor() {
			return color_;
		}

	private:
		Color color_;
		Type type_;
	};

}

