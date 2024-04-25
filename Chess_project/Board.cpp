/**
* Cette classe gere le contenu du board, soit le tableau en deux dimension contenant des Box. Elle gere aussi le fait de bouger les pieces.
* \file   Board.h
* \author Maxence Grondin, Thomas Thibodeau et Matthew Hantar
* \date  21 avril 2024
* Créé le 1er avril 2024
*/

#include "Board.h"

namespace modele {
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
		if (arrBoard[pos.first][pos.second]->getPiece() == nullptr) {
			return false;
		}
		else {
			return true;
		}

	}

	void Board::movePiece(pair<int, int> posBeginning, pair<int, int> posEnding) {
		if (isOccupied(posBeginning)) {
			if (isOccupied(posEnding))
				takePiece(posEnding);
			arrBoard[posEnding.first][posEnding.second]->setPiece(arrBoard[posBeginning.first][posBeginning.second]->getPiece());
			arrBoard[posBeginning.first][posBeginning.second]->setPiece(nullptr);
		}
	}

	void Board::takePiece(pair<int, int> piecePos) {
		shared_ptr<Piece> piece = getPieceAtPos(piecePos);
		arrBoard[piecePos.first][piecePos.second]->setPiece(nullptr);
		if (piece->getColor() == Color::BLACK)
			deadBlackPiece.push_back(piece);
		else
			deadWhitePiece.push_back(piece);
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
		map<shared_ptr<Piece>, pair<int, int>> board0 = { { make_shared<Piece>(Color::WHITE, Type::ROOK),make_pair(4,3)},
			{make_shared<Piece>(Color::WHITE, Type::ROOK), make_pair(3,1)}, { make_shared<Piece>(Color::BLACK, Type::KING), make_pair(4,5)}
		};

		for (auto const& [piece, pos] : board0) {
			addPiece(piece, pos);
		}
	}

	void Board::initBoard1() {
		map<shared_ptr<Piece>, pair<int, int>> board0 = { { make_shared<Piece>(Color::BLACK, Type::KING),make_pair(0,0)},
			{make_shared<Piece>(Color::BLACK, Type::KING), make_pair(3,3)}, { make_shared<Piece>(Color::WHITE, Type::KING), make_pair(5,5)}
		};

		for (auto const& [piece, pos] : board0) {
			addPiece(piece, pos);
		}
	}

	void Board::initBoard2() {
		map<shared_ptr<Piece>, pair<int, int>> board0 = { { make_shared<Piece>(Color::BLACK, Type::ROOK),make_pair(3,3)},{ make_shared<Piece>(Color::BLACK, Type::KING),make_pair(0,0)},
			{make_shared<Piece>(Color::WHITE, Type::QUEEN), make_pair(5,6)}, { make_shared<Piece>(Color::WHITE, Type::BISHOP), make_pair(0,5)},
			{make_shared<Piece>(Color::WHITE, Type::PAWN), make_pair(0,3)}, {make_shared<Piece>(Color::WHITE, Type::ROOK), make_pair(7,7)},
			{make_shared<Piece>(Color::WHITE, Type::KNIGHT), make_pair(6,7)}
		};

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

}