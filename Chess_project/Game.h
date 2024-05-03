#pragma once
#include "Board.h"
namespace modele {
	class Game
	{

	public:
		Game() {
			board_ = make_shared<Board>();
			currentPlayer_ = Color::WHITE;
		}

		bool isPiecePlayer(pair<int, int> pos, Color playerColor);

		bool isPositionInBoard(pair<int, int> pos);

		bool isKingCheck(pair<int, int> pos, Color color);

		//TODO: add all the movements for each piece, return all the movements in a vector<pair<int, int>> -> (vector of positions)
		vector<pair<int, int>> getMoveValidPiece(pair<int, int> pos);

		vector<pair<int, int>> getMoveValidKing(pair<int, int> pos, bool withCheck);

		vector<pair<int, int>> getMoveValidQueen(pair<int, int> pos);

		vector<pair<int, int>> getMoveValidPawn(pair<int, int> pos);

		vector<pair<int, int>> getMoveValidBishop(pair<int, int> pos);

		vector<pair<int, int>> getMoveValidKnight(pair<int, int> pos);

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

}

