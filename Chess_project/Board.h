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
	   * Creates a 2d array representing the board
	   *
	   * @param piece: void
	   *
	   * @return bool: void
	   */
		void createBoard();
 
		/**
	   * Add a new piece on the board with the specified position, type and color
	   *
	   * @param piece: shared_ptr<Piece> 
	   * @param pos: pair<int, int>
	   *
	   * @return void:
	   */
		void addPiece(shared_ptr<Piece> piece, pair<int, int> pos);

		/**
	   * Removes an existing piece on the board with the specified position, type and color
	   *
	   * @param piece: shared_ptr<Piece>
	   * @param pos: pair<int, int>
	   *
	   * @return void:
	   */
		void removePiece(shared_ptr<Piece> piece, pair<int, int> pos);


		/**
	   * Returns true if a piece exists at this position
	   *
	   * @param pos: pair<int, int>
	   *
	   * @return bool:
	   */
		bool isOccupied(pair<int, int> pos);

		/**
	   * Moves a piece from its orignal position to a new position and takes the opponent's piece if necessary
	   *
	   * @param posBeginning: pair<int, int>
	   * @param posEnding: pair<int, int>
	   *
	   * @return void:
	   */
		void movePiece(pair<int, int> posBeginning, pair<int, int> posEnding);

		/**
	   * Takes the opponent's piece and adds it to the array of taken pieces
	   *
	   * @param pos: pair<int, int>
	   *
	   * @return void:
	   */
		void takePiece(pair<int, int> piecePos);

		shared_ptr<Piece> getPieceAtPos(pair<int, int> pos);

		/**
	   * initialize a game state with 1 black king and 2 white rooks
	   *
	   * @param void:
	   *
	   * @return void:
	   */
		void initBoard0();

		
		/**
	   * initialize a game state with 3 kings
	   *
	   * @param void:
	   *
	   * @return void:
	   */
		void initBoard1();

		/**
	   * initialize an endgame scenario with the white queen along with few other pieces
	   *
	   * @param void:
	   *
	   * @return void:
	   */
		void initBoard2();

		/**
	   * initialize a default starting chess game state
	   *
	   * @param void:
	   *
	   * @return void:
	   */
		void initBoard3();


		/**
	   * Resets the 2d array of pieces
	   *
	   * @param void:
	   *
	   * @return void:
	   */
		void cleanBackendBoard();

		void setPosKing(pair<int, int> actualPos, pair<int, int> newPos);

		pair<int, int> getPosKing(Color playerTurn);

		//getters

		pair<int, int> getWhiteKing() const {
			return posWhiteKing_;
		}

		pair<int, int> getBlackKing() const {
			return posBlackKing_;
		}

		const vector<std::shared_ptr<Piece>>& getDeadWhitePieces() const {
			return vectDeadWhitePieces;
		}

		const vector<std::shared_ptr<Piece>>& getDeadBlackPieces() const {
			return vectDeadBlackPieces;
		}

		Color getTakenPieceColor() const {
			return takenPieceColor;
		}

		//setters
		void setWhiteKing(pair<int, int> whiteKingPos) {
			posWhiteKing_ = whiteKingPos;
		}

		void setBlackKing(pair<int, int> blackKingPos) {
			posBlackKing_ = blackKingPos;
		}

		/**
	   * Clears the vector of taken white pieces and frees up the memory
	   *
	   * @param piece: void
	   *
	   * @return bool: void
	   */
		void clearDeadWhitePieces() {
			vectDeadWhitePieces.clear();
		}
		/**
	   * Clears the vector of taken black pieces and frees up the memory
	   *
	   * @param piece: void
	   *
	   * @return bool: void
	   */
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
