#pragma once
#include <map>
#include "Piece.h"
#include "Box.h"
#include <string>
#include <vector>

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

private:
	static const int NB_LINES = 8;
	static const int NB_COLUMNS = 8;
	
	 shared_ptr<Box> arrBoard[NB_LINES][NB_COLUMNS]; 
};

