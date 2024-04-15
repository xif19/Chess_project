#pragma once
#include <map>
#include "Piece.h"
#include "Box.h"
#include <string>
#include <vector>
#include <QWidget>

using namespace std;
class Board
{
public:
	Board() {
		createBoard();
	}
	~Board() {};

	void createBoard() {
		for (int i = 0; i < NB_LINES; i++) {
			for (int j = 0; j < NB_COLUMNS; j++) {
				arrBoard[i][j] = make_shared<Box>();
			}
		}
	}

	void addingPiece(shared_ptr<Piece> piece, pair<int, int> pos) {
		arrBoard[pos.first][pos.second]->getPiece() = piece;
	}

	bool isOccupied(pair<int, int> pos) {
		if (arrBoard[pos.first][pos.second]->getPiece() == nullptr) {
			return false;
		}
		return true;
	}

	void movePiece(pair<int, int> posBeginning, pair<int, int> posEnding) {
		if (isOccupied(posBeginning) == true) {
			arrBoard[posBeginning.first][posBeginning.second]->getPiece() = arrBoard[posEnding.first][posEnding.second]->getPiece();
			arrBoard[posBeginning.first][posBeginning.second]->getPiece() = nullptr;
		}
	}

	shared_ptr<Piece> getPieceAtPos(pair<int, int> pos) {
		if (isOccupied(pos) == true) {
			return arrBoard[pos.first][pos.second]->getPiece();
		}
		else {
			return nullptr;
		}
	}


private:
	static const int NB_LINES = 8;
	static const int NB_COLUMNS = 8;
	
	 shared_ptr<Box> arrBoard[NB_LINES][NB_COLUMNS]; 
};

