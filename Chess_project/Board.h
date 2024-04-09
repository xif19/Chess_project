#pragma once
#include <map>
#include "Piece.h"
#include <string>
#include <vector>

using namespace std;
class Board
{
public:
	Board() {

	}

	~Board() {};

private:
	const int NB_LINES = 8;
	const int NB_COLUMNS = 8;
	
	vector<Piece> arrBoard; 
};

