#pragma once
#include "Board.h"

class Game
{

public:
	Game() {
		board_ = make_shared<Board>();
		currentPlayer_ = Color::WHITE;
	}

	/**
	* Checks if the piece is the same one as the color of the player turn. 
	*
	* @param pos : the position of a piece
	* @param playerColor : the good color
	*
	* @return bool 
	*/
	bool isPiecePlayer(pair<int, int> pos, Color playerColor);

	/**
	* Checks if the piece is in the board. 
	*
	* @param pos : the position of a piece
	*
	* @return bool
	*/
	bool isPositionInBoard(pair<int, int> pos);

	/**
	* Looks at the specified king check
	*
	* @param pos : the position of a piece
	* @param playerColor : the good color
	*
	* @return bool
	*/
	bool isKingCheck(pair<int, int> pos, Color color);

	/**
	* This function gets the good moves for the specified piece.
	*
	* @param pos : the position of a piece
	*
	* @return a vector of positions
	*/
	vector<pair<int, int>> getMoveValidPiece(pair<int, int> pos);

	/**
	* This function looks if the king is valid and also, the bool parameter
	* disables the check function. 
	*
	* @param pos : the position of a piece
	* @param withCheck : if we look at the check or not
	*
	* @return a vector of positions
	*/
	vector<pair<int, int>> getMoveValidKing(pair<int, int> pos, bool withCheck);

	/**
	* The valid moves for the Queen
	*
	* @param pos : the position of a piece
	*
	* @return a vector of positions
	*/
	vector<pair<int, int>> getMoveValidQueen(pair<int, int> pos);

	/**
	* The valid moves for the Pawn
	*
	* @param pos : the position of a piece
	*
	* @return a vector of positions
	*/
	vector<pair<int, int>> getMoveValidPawn(pair<int, int> pos);

	/**
	* The valid moves for the Bishop
	*
	* @param pos : the position of a piece
	*
	* @return a vector of positions
	*/
	vector<pair<int, int>> getMoveValidBishop(pair<int, int> pos);

	/**
	* The valid moves for the Knight
	*
	* @param pos : the position of a piece
	*
	* @return a vector of positions
	*/
	vector<pair<int, int>> getMoveValidKnight(pair<int, int> pos);

	/**
	* The valid moves for the Rook
	*
	* @param pos : the position of a piece
	*
	* @return a vector of positions
	*/
	vector<pair<int, int>> getMoveValidRook(pair<int, int> pos);

	//Getters
	shared_ptr<Board> getBoard() {
		return board_;
	}

	Color getCurrentPlayer() {
		return currentPlayer_;
	}

	//Setters
	void setCurrentPlayer(Color newPlayer) {
		currentPlayer_ = newPlayer;
	}

private:
	shared_ptr<Board> board_;
	Color currentPlayer_;
	int BOARD_MAX_SIZE = 8;
};



