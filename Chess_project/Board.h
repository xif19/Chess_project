#pragma once

#include <map>
#include "Box.h"
#include <string>
#include <vector>
#include <QWidget>
#include "ObservableVector.h"

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

		void cleanBackendBoard();

		ObservableVector<shared_ptr<Piece>> deadWhitePiece;
		ObservableVector<shared_ptr<Piece>> deadBlackPiece;


	private:
		static const int NB_LINES = 8;
		static const int NB_COLUMNS = 8;


		
		shared_ptr<Box> arrBoard[NB_LINES][NB_COLUMNS];
		int kingCount_ = 0; // Counter for king pieces
	};
}
