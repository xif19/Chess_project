#pragma once
/**
* Cette classe gere le contenu du board, soit le tableau en deux dimension contenant des Box. Elle gere aussi le fait de bouger les pieces.
* \file   Board.h
* \author Maxence Grondin, Thomas Thibodeau et Matthew Hantar
* \date  21 avril 2024
* Cr�� le 1er avril 2024
*/

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

		shared_ptr<Piece> getPieceAtPos(pair<int, int> pos);

		// pair<row, col>
		//{Rook_B 0,0}, {Rook_B 3,1}, {King_W 4,5}
		void initBoard0();

		//3 kings
		void initBoard1();

		void cleanBackendBoard();


	private:
		static const int NB_LINES = 8;
		static const int NB_COLUMNS = 8;

		shared_ptr<Box> arrBoard[NB_LINES][NB_COLUMNS];
		int kingCount_ = 0; // Counter for king pieces
	};
}
