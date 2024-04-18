#pragma once
enum class Type { KING, QUEEN, PAWN, BISHOP, KNIGHT, ROOK };
enum class Color {BLACK, WHITE};

//Type : KING, QUEEN, PAWN, BISHOP, KNIGHT, ROOK
//Color : BLACK, WHITE
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

