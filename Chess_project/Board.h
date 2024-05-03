#pragma once

#include <map>
#include "Box.h"
#include <string>
#include <vector>
#include <QWidget>

using namespace std;

namespace modele {
	class Board
	{
	public:
		Board() {
			createBoard();
		}
		~Board() {};

		/**
		* Creates a new board of shared pointers of Box objects
		*/
		void createBoard();

		void addPiece(shared_ptr<Piece> piece, pair<int, int> pos);

		void removePiece(shared_ptr<Piece> piece, pair<int, int> pos);

		bool isOccupied(pair<int, int> pos);

		void movePiece(pair<int, int> posBeginning, pair<int, int> posEnding);

		void takePiece(pair<int, int> piecePos);

		shared_ptr<Piece> getPieceAtPos(pair<int, int> pos);

		// pair<row, col>
		//{Rook_B 0,0}, {Rook_B 3,1}, {King_W 4,5}
		void initBoard0();

		//3 kings
		void initBoard1();

		void initBoard2();

		void initBoard3();

		void cleanBackendBoard();

		void setPosKing(pair<int, int> actualPos, pair<int, int> newPos);

		pair<int, int> getPosKing(Color playerTurn);

		//getters
		pair<int, int> getWhiteKing() {
			return posWhiteKing_;
		}

		pair<int, int> getBlackKing() {
			return posBlackKing_;
		}

		const vector<std::shared_ptr<Piece>>& getDeadWhitePieces() const {
			return vectDeadWhitePieces;
		}

		const vector<std::shared_ptr<Piece>>& getDeadBlackPieces() const {
			return vectDeadBlackPieces;
		}

		Color getTakenPieceColor() {
			return takenPieceColor;
		}

		//setters
		void setWhiteKing(pair<int, int> whiteKingPos) {
			posWhiteKing_ = whiteKingPos;
		}

		void setBlackKing(pair<int, int> blackKingPos) {
			posBlackKing_ = blackKingPos;
		}

		void clearDeadWhitePieces() {
			vectDeadWhitePieces.clear();
		}

		void clearDeadBlackPieces() {
			vectDeadBlackPieces.clear();
		}

	private:
		static const int NB_LINES = 8;
		static const int NB_COLUMNS = 8;

		vector<shared_ptr<Piece>> vectDeadWhitePieces;
		vector<shared_ptr<Piece>> vectDeadBlackPieces;
		pair<int, int> posWhiteKing_;
		pair<int, int> posBlackKing_;
		Color takenPieceColor;
		shared_ptr<Box> arrBoard[NB_LINES][NB_COLUMNS];
		int kingCount_ = 0; // Counter for king pieces
	};
}
