#pragma once
enum class Type { KING, QUEEN, PAWN, BISHOP, KNIGHT, ROOK };
enum class Color {BLACK, WHITE};

class Piece
{	
public:
	Piece(Color color, Type type) {
		color_ = color;
		type_ = type;
	}
	~Piece() {};

private:
	Color color_;
	Type type_;
};

