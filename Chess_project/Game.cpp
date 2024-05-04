#include "Game.h"


namespace modele{
	bool Game::isPiecePlayer(pair<int, int> pos, Color playerColor) {
		if (board_->isOccupied(pos)) {
			return board_->getPieceAtPos(pos)->getColor() == playerColor;
		}
	}

	bool Game::isPositionInBoard(pair<int, int> pos) {
		int x = pos.first;
		int y = pos.second;
		return x >= 0 && x < BOARD_MAX_SIZE&& y >= 0 && y < BOARD_MAX_SIZE;
	}

	bool Game::isKingCheck(pair<int, int> pos, Color color) {
		for (int i = 0; i < BOARD_MAX_SIZE; i++) {
			for (int j = 0; j < BOARD_MAX_SIZE; j++) {
				pair<int, int> box = make_pair(i, j);
				if (board_->isOccupied(box)) {
					shared_ptr<Piece> piece = board_->getPieceAtPos(box);
					if (piece && piece->getColor() != color) { // Verification of the non null pointer
						vector<pair<int, int>> possibleMoves;
						if (piece->getType() == Type::KING)
							possibleMoves = getMoveValidKing(box, false);
						else
							possibleMoves = getMoveValidPiece(box);
						for (const auto& possibleTake : possibleMoves) {
							if (possibleTake == pos)
								return true;
						}
					}
				}
			}
		}
		return false;
	}

	vector<pair<int, int>> Game::getMoveValidPiece(pair<int, int> pos) {
		switch (board_->getPieceAtPos(pos)->getType()) {
		case Type::KING:
			return getMoveValidKing(pos, true); break;
		case Type::QUEEN:
			return getMoveValidQueen(pos); break;
		case Type::PAWN:
			return getMoveValidPawn(pos); break;
		case Type::BISHOP:
			return getMoveValidBishop(pos); break;
		case Type::KNIGHT:
			return getMoveValidKnight(pos); break;
		case Type::ROOK:
			return getMoveValidRook(pos); break;
		}
	}

	vector<pair<int, int>> Game::getMoveValidKing(pair<int, int> pos, bool withCheck) {
		vector<pair<int, int>> directions = { make_pair(1,1), make_pair(-1,1), make_pair(1,-1), make_pair(-1,-1), make_pair(0,1), make_pair(1,0), make_pair(0,-1), make_pair(-1,0) };
		vector<pair<int, int>> moveSetValid;
		for (const auto& direction : directions) {
			pair<int, int> futurPos = make_pair(pos.first + direction.first, pos.second + direction.second);
			if (isPositionInBoard(futurPos)) {
				if (board_->isOccupied(futurPos)) {
					if (board_->getPieceAtPos(futurPos)->getColor() != board_->getPieceAtPos(pos)->getColor()) {
						if (withCheck) {
							if (!isKingCheck(futurPos, board_->getPieceAtPos(pos)->getColor()))//king not in check
								moveSetValid.push_back(futurPos);
						}
						else
							moveSetValid.push_back(futurPos);
					}
				}
				else {
					if (withCheck) {
						if (!isKingCheck(futurPos, board_->getPieceAtPos(pos)->getColor()))//king not in check
							moveSetValid.push_back(futurPos);
					}
					else
						moveSetValid.push_back(futurPos);
				}
			}
		}
		return moveSetValid;
	}

	vector<pair<int, int>> Game::getMoveValidQueen(pair<int, int> pos) {
		vector<pair<int, int>> directions = { make_pair(1,1), make_pair(-1,1), make_pair(1,-1), make_pair(-1,-1), make_pair(0,1), make_pair(1,0), make_pair(0,-1), make_pair(-1,0) };
		vector<pair<int, int>> moveSetValid;
		for (const auto& direction : directions) {
			int j = 1;
			bool flag = true;
			while (j < BOARD_MAX_SIZE && flag) {
				pair<int, int> futurPos = make_pair(pos.first + (direction.first * j), pos.second + (direction.second * j));
				if (!isPositionInBoard(futurPos)) {
					flag = false;
					continue;
				}
				if (board_->isOccupied(futurPos)) {
					if (board_->getPieceAtPos(futurPos)->getColor() != board_->getPieceAtPos(pos)->getColor())
						moveSetValid.push_back(futurPos);
					flag = false;
				}
				else
					moveSetValid.push_back(futurPos);
				j++;
			}
		}
		return moveSetValid;
	}

	vector<pair<int, int>> Game::getMoveValidPawn(pair<int, int> pos) {
		vector<pair<int, int>> directions;
		if (board_->getPieceAtPos(pos)->getColor() == Color::BLACK)
			directions = { make_pair(-1,1), make_pair(-1,-1), make_pair(-1,0) };//Black
		else
			directions = { make_pair(1,1), make_pair(1,-1), make_pair(1,0) };//White
		vector<pair<int, int>> moveSetValid;
		for (const auto& direction : directions) {
			pair<int, int> futurPos = make_pair(pos.first + direction.first, pos.second + direction.second);
			if (isPositionInBoard(futurPos)) {
				if (direction.second == 0) {//aller devant
					if (!board_->isOccupied(futurPos))
						moveSetValid.push_back(futurPos);
				}
				else if (board_->isOccupied(futurPos) && //diagonal
					board_->getPieceAtPos(futurPos)->getColor() != board_->getPieceAtPos(pos)->getColor())
					moveSetValid.push_back(futurPos);
			}
		}
		return moveSetValid;
	}

	vector<pair<int, int>> Game::getMoveValidBishop(pair<int, int> pos) {
		vector<pair<int, int>> directions = { make_pair(1,1), make_pair(-1,1), make_pair(1,-1), make_pair(-1,-1) };
		vector<pair<int, int>> moveSetValid;
		for (const auto& direction : directions) {
			int j = 1;
			bool flag = true;
			while (j < BOARD_MAX_SIZE && flag) {
				pair<int, int> futurPos = make_pair(pos.first + (direction.first * j), pos.second + (direction.second * j));
				if (!isPositionInBoard(futurPos)) {
					flag = false;
					continue;
				}
				if (board_->isOccupied(futurPos)) {
					if (board_->getPieceAtPos(futurPos)->getColor() != board_->getPieceAtPos(pos)->getColor())
						moveSetValid.push_back(futurPos);
					flag = false;
				}
				else
					moveSetValid.push_back(futurPos);
				j++;
			}
		}
		return moveSetValid;
	}

	vector<pair<int, int>> Game::getMoveValidKnight(pair<int, int> pos) {
		vector<pair<int, int>> moveSet = {
			make_pair(pos.first + 2,pos.second + 1),
			make_pair(pos.first + 1,pos.second + 2),
			make_pair(pos.first - 1,pos.second + 2),
			make_pair(pos.first - 2,pos.second + 1),
			make_pair(pos.first + 1,pos.second - 2),
			make_pair(pos.first + 2,pos.second - 1),
			make_pair(pos.first - 2,pos.second - 1),
			make_pair(pos.first - 1,pos.second - 2) };
		vector<pair<int, int>> moveSetValid;
		for (const auto& position : moveSet) {
			if (isPositionInBoard(position)) {
				if (board_->isOccupied(position)) {
					if (board_->getPieceAtPos(position)->getColor() != board_->getPieceAtPos(pos)->getColor())
						moveSetValid.push_back(position);
				}
				else
					moveSetValid.push_back(position);
			}
		}
		return moveSetValid;
	}

	vector<pair<int, int>> Game::getMoveValidRook(pair<int, int> pos) {
		vector<pair<int, int>> directions = { make_pair(0,1), make_pair(1,0), make_pair(0,-1), make_pair(-1,0) };
		vector<pair<int, int>> moveSetValid;
		for (const auto& direction : directions) {
			int j = 1;
			bool flag = true;
			while (j < BOARD_MAX_SIZE && flag) {
				pair<int, int> futurPos = make_pair(pos.first + (direction.first * j), pos.second + (direction.second * j));
				if (!isPositionInBoard(futurPos)) {
					flag = false;
					continue;
				}
				if (board_->isOccupied(futurPos)) {
					if (board_->getPieceAtPos(futurPos)->getColor() != board_->getPieceAtPos(pos)->getColor())
						moveSetValid.push_back(futurPos);
					flag = false;
				}
				else
					moveSetValid.push_back(futurPos);
				j++;
			}
		}
		return moveSetValid;
	}
}