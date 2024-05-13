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

	//Setters
	void setFirstTurn(bool firstTurn) {
		firstTurn_ = firstTurn;
	}

	//Getters
	Type getType() {
		return type_;
	}

	Color getColor() {
		return color_;
	}

	bool getFirstTurn() {
		return firstTurn_;
	}

private:
	Color color_;
	Type type_;
	bool firstTurn_;
};



