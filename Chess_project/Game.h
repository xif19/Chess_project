#pragma once
/**
* 
* This class is used for the pieces algorithms and the game in general
*/
#include "Board.h"
namespace modele {
	class Game
	{

	public:
		Game() {
			Board board_ = Board();
			currentPlayer_ = Color::WHITE;
		}

		bool isPiecePlayer(pair<int, int> pos, Color playerColor) {
			if (board_.isOccupied(pos)) {
				return board_.getPieceAtPos(pos)->getColor() == playerColor;
			}
		}

		bool isPositionInBoard(pair<int, int> pos) {
			int x = pos.first;
			int y = pos.second;
			return x >= 0 && x < BOARD_MAX_SIZE && y >= 0 && y < BOARD_MAX_SIZE;
		}

		bool isKingCheck(pair<int, int> pos, Color color) {
			for (int i = 0;i < BOARD_MAX_SIZE;i++) {
				for (int j = 0;j < BOARD_MAX_SIZE;j++) {
					if (board_.isOccupied(make_pair(i, j))) {
						if (board_.getPieceAtPos(make_pair(i, j))->getColor() != color) {
							vector<pair<int, int>> possibleMoves = getMoveValidPiece(make_pair(i, j));
							for (const auto& possibleTake : possibleMoves) {
								if (possibleTake == pos)
									return false;
							}
						}
					}
				}
			}
			return true;
		}
		//TODO: add all the movements for each piece, return all the movements in a vector<pair<int, int>> -> (vector of positions)
		vector<pair<int, int>> getMoveValidPiece(pair<int, int> pos) {
			switch (board_.getPieceAtPos(pos)->getType()) {
			case Type::KING:
				return getMoveValidKing(pos); break;
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

		vector<pair<int, int>> getMoveValidKing(pair<int, int> pos) {
			vector<pair<int, int>> directions = { make_pair(1,1), make_pair(-1,1), make_pair(1,-1), make_pair(-1,-1), make_pair(0,1), make_pair(1,0), make_pair(0,-1), make_pair(-1,0) };
			vector<pair<int, int>> moveSetValid;
			for (const auto& direction : directions) {
				pair<int, int> futurPos = make_pair(pos.first+ direction.first,pos.second + direction.second);
				if (isPositionInBoard(futurPos)) {
					if (board_.isOccupied(futurPos)) {
						if (board_.getPieceAtPos(futurPos)->getColor() != board_.getPieceAtPos(pos)->getColor())
							if(!isKingCheck(futurPos, board_.getPieceAtPos(pos)->getColor()))//king not in check
								moveSetValid.push_back(futurPos);
					}
					if (!isKingCheck(futurPos, board_.getPieceAtPos(pos)->getColor()))//king not in check
						moveSetValid.push_back(futurPos);
				}
			}
			return moveSetValid;
		}

		vector<pair<int, int>> getMoveValidQueen(pair<int, int> pos) {
			vector<pair<int, int>> directions = { make_pair(1,1), make_pair(-1,1), make_pair(1,-1), make_pair(-1,-1), make_pair(0,1), make_pair(1,0), make_pair(0,-1), make_pair(-1,0) };
			vector<pair<int, int>> moveSetValid;
			for (const auto& direction : directions) {
				int j = 1;
				bool flag = true;
				while (j < BOARD_MAX_SIZE - 1 && flag) {
					pair<int, int> futurPos = make_pair(direction.first * j, direction.second * j);
					if (!isPositionInBoard(futurPos)) {
						flag = false;
						continue;
					}
					if (board_.isOccupied(futurPos)) {
						if (board_.getPieceAtPos(futurPos)->getColor() != board_.getPieceAtPos(pos)->getColor())
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

		vector<pair<int, int>> getMoveValidPawn(pair<int, int> pos) {
			vector<pair<int, int>> directions;
			if(board_.getPieceAtPos(pos)->getColor() == Color::BLACK)
				directions = { make_pair(1,1), make_pair(1,-1), make_pair(1,0)};//Black
			else
				directions = { make_pair(-1,1), make_pair(-1,-1), make_pair(-1,0) };//White
			vector<pair<int, int>> moveSetValid;
			for (const auto& direction : directions) {
				pair<int, int> futurPos = make_pair( pos.first + direction.first, pos.second + direction.second);
				if (isPositionInBoard(futurPos)){
					if (futurPos.second == 0) {//aller devant
						if(!board_.isOccupied(futurPos))
							moveSetValid.push_back(futurPos);
					}
					else if(board_.isOccupied(futurPos)&& //diagonal
						board_.getPieceAtPos(futurPos)->getColor() != board_.getPieceAtPos(pos)->getColor())
						moveSetValid.push_back(futurPos);
				}
			}
			return moveSetValid;
		}

		vector<pair<int, int>> getMoveValidBishop(pair<int, int> pos) {
			vector<pair<int, int>> directions = { make_pair(1,1), make_pair(-1,1), make_pair(1,-1), make_pair(-1,-1) };
			vector<pair<int, int>> moveSetValid;
			for (const auto& direction : directions) {
				int j = 1;
				bool flag = true;
				while (j < BOARD_MAX_SIZE - 1 && flag) {
					pair<int, int> futurPos = make_pair(direction.first * j, direction.second * j);
					if (!isPositionInBoard(futurPos)) {
						flag = false;
						continue;
					}
					if (board_.isOccupied(futurPos)) {
						if (board_.getPieceAtPos(futurPos)->getColor() != board_.getPieceAtPos(pos)->getColor())
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

		vector<pair<int, int>> getMoveValidKnight(pair<int, int> pos) {
			vector<pair<int, int>> moveSet = {
				make_pair(pos.first + 2,pos.second + 1),
				make_pair(pos.first + 1,pos.second + 2),
				make_pair(pos.first - 1,pos.second + 2),
				make_pair(pos.first - 2,pos.second + 1),
				make_pair(pos.first + 1,pos.second - 2),
				make_pair(pos.first + 2,pos.second - 1),
				make_pair(pos.first - 2,pos.second - 1),
				make_pair(pos.first - 1,pos.second - 2), };
			vector<pair<int, int>> moveSetValid;
			for (const auto& position : moveSet) {
				if (isPositionInBoard(position))
					if (board_.getPieceAtPos(position)->getColor() != board_.getPieceAtPos(pos)->getColor())//si on verifie pour une piece mais qu'on est pas sur que la position existe, on va avoir une erreur donc on doit separer
						moveSetValid.push_back(position);
				return moveSetValid;
			}
		}

		vector<pair<int, int>> getMoveValidRook(pair<int, int> pos) {
			vector<pair<int, int>> directions = { make_pair(0,1), make_pair(1,0), make_pair(0,-1), make_pair(-1,0) };
			vector<pair<int, int>> moveSetValid;
			for (const auto& direction : directions) {
				int j = 1;
				bool flag = true;
				while (j < BOARD_MAX_SIZE && flag) {
					pair<int, int> futurPos = make_pair(pos.first + (direction.first * j), pos.second+(direction.second * j));
					if (!isPositionInBoard(futurPos)) {
						flag = false;
						continue;
					}
					if (board_.isOccupied(futurPos)) {
						if (board_.getPieceAtPos(futurPos)->getColor() != board_.getPieceAtPos(pos)->getColor())
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
		//Getters
		Board getBoard() {
			return board_;
		}

		Color getCurrentPlayer() {
			return currentPlayer_;
		}

	private:
		Board board_;
		Color currentPlayer_;
		int BOARD_MAX_SIZE = 8;
	};

}

