#pragma once
/**
* 
* This class is used for the pieces algorithms and the game in general
*/
#include "Board.h"

class Game
{
public:
	Game() {
		Board board_ = Board();
		currentPlayer_ = Color::WHITE;
	}

	bool isPiecePlayer(pair<int, int> pos, Color player) {
		if (board_.isOccupied(pos)) {
			return board_.getPieceAtPos(pos)->getColor() == player;
		}
	}

	//TODO: add all the movements for each piece, return all the movements in a vector<pair<int, int>> -> (vector of positions)

	//Getters
	Board getBoard() {
		return board_;
	}

	Color getCurrentPlayer() {
		return currentPlayer_;
	}

private:
	Board board_;
	Color currentPlayer_;
};

