#include "Board.h"


void Board::createBoard() {
	for (int i = 0; i < NB_LINES; i++) {
		for (int j = 0; j < NB_COLUMNS; j++) {
			arrBoard[i][j] = make_shared<Box>();
		}
	}
}

void Board::addPiece(shared_ptr<Piece> piece, pair<int, int> pos) {

	if (pos.first < 0 || pos.first >= NB_LINES || pos.second < 0 || pos.second >= NB_COLUMNS) {
		throw out_of_range("Outside chessboard");
	}

	arrBoard[pos.first][pos.second]->setPiece(piece);

	//If there are more then 3 kings, raise an exception
	if (piece->getType() == Type::KING) {
		kingCount_++;
		if (kingCount_ > 3) {
			throw runtime_error("More than 3 kings!");
		}
	}
}

bool Board::isOccupied(pair<int, int> pos) {
	if (arrBoard[pos.first][pos.second]->getPiece() == nullptr) {
		return false;
	}
	else {
		return true;
	}

}

void Board::movePiece(pair<int, int> posBeginning, pair<int, int> posEnding) {
	if (isOccupied(posBeginning) == true) {
		arrBoard[posBeginning.first][posBeginning.second]->getPiece() = arrBoard[posEnding.first][posEnding.second]->getPiece();
		arrBoard[posBeginning.first][posBeginning.second]->getPiece() = nullptr;
	}
}

shared_ptr<Piece> Board::getPieceAtPos(pair<int, int> pos) {
	if (isOccupied(pos) == true) {
		return arrBoard[pos.first][pos.second]->getPiece();
	}
	else {
		return nullptr;
	}
}

// pair<row, col>
//{Rook_B 0,0}, {Rook_B 3,1}, {King_W 4,5}
void Board::initBoard0() {
	map<shared_ptr<Piece>, pair<int, int>> board0 = { { make_shared<Piece>(Color::BLACK, Type::ROOK),make_pair(0,0)},
		{make_shared<Piece>(Color::BLACK, Type::ROOK), make_pair(3,1)}, { make_shared<Piece>(Color::WHITE, Type::KING), make_pair(4,5)}
	};

	for (auto const& [piece, pos] : board0) {
		addPiece(piece, pos);
	}
}