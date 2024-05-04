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

	//If there are more than 2 kings, raise an exception
	if (piece->getType() == Type::KING) {
		kingCount_++;
		if (kingCount_ > 2) {
			throw runtime_error("More than 2 kings!");
		}
	}
}

void Board::removePiece(shared_ptr<Piece> piece, pair<int, int> pos) {
	if (pos.first < 0 || pos.first >= NB_LINES || pos.second < 0 || pos.second >= NB_COLUMNS) {
		throw out_of_range("Outside chessboard");
	}

	arrBoard[pos.first][pos.second]->setPiece(nullptr);

	if (piece->getType() == Type::KING) {
		kingCount_--;
	}
}

bool Board::isOccupied(pair<int, int> pos) {
	return !(arrBoard[pos.first][pos.second]->getPiece() == nullptr);
}

void Board::movePiece(pair<int, int> posBeginning, pair<int, int> posEnding) {
	if (isOccupied(posBeginning)) {
		if (getPieceAtPos(posBeginning)->getType() == Type::KING){
			setPosKing(posBeginning, posEnding);
		}
		if (isOccupied(posEnding))
			takePiece(posEnding);
		arrBoard[posEnding.first][posEnding.second]->setPiece(arrBoard[posBeginning.first][posBeginning.second]->getPiece());
		arrBoard[posBeginning.first][posBeginning.second]->setPiece(nullptr);
	}
}

void Board::takePiece(pair<int, int> piecePos) {
	shared_ptr<Piece> piece = getPieceAtPos(piecePos);
	if (piece->getColor() == Color::BLACK) {
		vectDeadBlackPieces.push_back(piece);
		takenPieceColor = Color::BLACK;
	}
	else {
		vectDeadWhitePieces.push_back(piece);
		takenPieceColor = Color::WHITE;
	}
	arrBoard[piecePos.first][piecePos.second]->setPiece(nullptr);
}

shared_ptr<Piece> Board::getPieceAtPos(pair<int, int> pos) {
	if (isOccupied(pos) == true) {
		return arrBoard[pos.first][pos.second]->getPiece();
	}
	else {
		return nullptr;
	}
}

void Board::setPosKing(pair<int, int> actualPos, pair<int, int> newPos) {
	shared_ptr<Piece> piece = getPieceAtPos(actualPos);
	if (piece != nullptr && piece->getType() == Type::KING) {
		if (piece->getColor() == Color::BLACK)
			setBlackKing(newPos);
		else if (piece->getColor() == Color::WHITE)
			setWhiteKing(newPos);
	}
}

pair<int, int> Board::findKing(Color playerColor) {
	for (int i = 0; i < NB_LINES; ++i) {
		for (int j = 0; j < NB_COLUMNS; ++j) {
			if (isOccupied(make_pair(i, j))) {
				if (getPieceAtPos(make_pair(i, j))->getType() == Type::KING && getPieceAtPos(make_pair(i, j))->getColor() == playerColor)
					return make_pair(i, j);
			}
		}
	}
	return make_pair(-1, -1); //A position that doesn't exist 
}

pair<int,int> Board::getPosKing(Color playerTurn) {
	if (playerTurn == Color::BLACK)
		return getBlackKing();
	else if(playerTurn == Color::WHITE)
		return getWhiteKing();
}

// pair<row, col>
//{Rook_B 0,0}, {Rook_B 3,1}, {King_W 4,5}
void Board::initBoard0() {
	map<shared_ptr<Piece>, pair<int, int>> board0 = { { make_shared<Piece>(Color::WHITE, Type::ROOK),make_pair(4,3)},
		{make_shared<Piece>(Color::WHITE, Type::ROOK), make_pair(3,1)}, { make_shared<Piece>(Color::BLACK, Type::KING), make_pair(5,5)}
	};
	setBlackKing(make_pair(-1, -1));
	setWhiteKing(make_pair(-1,-1));
	for (auto const& [piece, pos] : board0) {
		addPiece(piece, pos);
	}
}


void Board::initBoard1() {
	map<shared_ptr<Piece>, pair<int, int>> board0 = { { make_shared<Piece>(Color::BLACK, Type::ROOK),make_pair(3,3)},{ make_shared<Piece>(Color::BLACK, Type::KING),make_pair(1,1)},
		{make_shared<Piece>(Color::WHITE, Type::QUEEN), make_pair(5,6)}, { make_shared<Piece>(Color::WHITE, Type::BISHOP), make_pair(0,5)},
		{make_shared<Piece>(Color::WHITE, Type::PAWN), make_pair(0,3)}, {make_shared<Piece>(Color::WHITE, Type::ROOK), make_pair(7,7)},
		{make_shared<Piece>(Color::WHITE, Type::KNIGHT), make_pair(6,7)}
	};
	setBlackKing(make_pair(-1, -1));
	setWhiteKing(make_pair(-1, -1));
	for (auto const& [piece, pos] : board0) {
		addPiece(piece, pos);
	}
}

void Board::initBoard2() {
	map<shared_ptr<Piece>, pair<int, int>> board0 = { 
		//White pieces
		{ make_shared<Piece>(Color::WHITE, Type::ROOK),make_pair(0,0)},{ make_shared<Piece>(Color::WHITE, Type::KNIGHT),make_pair(0,1)},
		{make_shared<Piece>(Color::WHITE, Type::BISHOP), make_pair(0,2)}, { make_shared<Piece>(Color::WHITE, Type::QUEEN), make_pair(0,3)},
		{make_shared<Piece>(Color::WHITE, Type::KING), make_pair(0,4)}, {make_shared<Piece>(Color::WHITE, Type::BISHOP), make_pair(0,5)},
		{make_shared<Piece>(Color::WHITE, Type::KNIGHT), make_pair(0,6)}, {make_shared<Piece>(Color::WHITE, Type::ROOK), make_pair(0,7)},
		{make_shared<Piece>(Color::WHITE, Type::PAWN), make_pair(1,0)}, {make_shared<Piece>(Color::WHITE, Type::PAWN), make_pair(1,1)}, 
		{make_shared<Piece>(Color::WHITE, Type::PAWN), make_pair(1,2)}, {make_shared<Piece>(Color::WHITE, Type::PAWN), make_pair(1,3)}, 
		{make_shared<Piece>(Color::WHITE, Type::PAWN), make_pair(1,4)}, {make_shared<Piece>(Color::WHITE, Type::PAWN), make_pair(1,5)}, 
		{make_shared<Piece>(Color::WHITE, Type::PAWN), make_pair(1,6)}, {make_shared<Piece>(Color::WHITE, Type::PAWN), make_pair(1,7)}, 

		//Black pieces
		{ make_shared<Piece>(Color::BLACK, Type::ROOK),make_pair(7,0)},{ make_shared<Piece>(Color::BLACK, Type::KNIGHT),make_pair(7,1)},
		{make_shared<Piece>(Color::BLACK, Type::BISHOP), make_pair(7,2)}, { make_shared<Piece>(Color::BLACK, Type::KING), make_pair(7,3)},
		{make_shared<Piece>(Color::BLACK, Type::QUEEN), make_pair(7,4)}, {make_shared<Piece>(Color::BLACK, Type::BISHOP), make_pair(7,5)},
		{make_shared<Piece>(Color::BLACK, Type::KNIGHT), make_pair(7,6)}, {make_shared<Piece>(Color::BLACK, Type::ROOK), make_pair(7,7)},
		{make_shared<Piece>(Color::BLACK, Type::PAWN), make_pair(6,0)}, {make_shared<Piece>(Color::BLACK, Type::PAWN), make_pair(6,1)},
		{make_shared<Piece>(Color::BLACK, Type::PAWN), make_pair(6,2)}, {make_shared<Piece>(Color::BLACK, Type::PAWN), make_pair(6,3)},
		{make_shared<Piece>(Color::BLACK, Type::PAWN), make_pair(6,4)}, {make_shared<Piece>(Color::BLACK, Type::PAWN), make_pair(6,5)},
		{make_shared<Piece>(Color::BLACK, Type::PAWN), make_pair(6,6)}, {make_shared<Piece>(Color::BLACK, Type::PAWN), make_pair(6,7)}
	};
	setBlackKing(make_pair(-1, -1));
	setWhiteKing(make_pair(-1, -1));
	for (auto const& [piece, pos] : board0) {
		addPiece(piece, pos);
	}
}

void Board::cleanBackendBoard() {
	for (int i = 0; i < NB_LINES; i++) {
		for (int j = 0; j < NB_COLUMNS; j++) {
			pair<int, int> pos = make_pair(i, j);
			if (isOccupied(pos)) {
				removePiece(getPieceAtPos(pos), pos);
			}
		}
	}
}

