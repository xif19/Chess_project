#include "Game.h"
#include "Board.h"
#include "Piece.h"


#if __has_include("gtest/gtest.h")
#include "gtest/gtest.h"
#endif
#ifdef TEST

TEST(Game, inbound) {
	Game game;
	EXPECT_EQ(game.isPositionInBoard(make_pair(2, 3), true);
	EXPECT_EQ(game.isPositionInBoard(make_pair(12, 34), false);
}

TEST(Board, pieceInBoard) {
	Board board;
	Piece piece(Color::WHITE, Type::Piece);
	board.addPiece(make_shared<piece>, make_pair(3, 3));
	EXPECT_EQ(board.isOccupied(make_pair(3, 3)), true);
	EXPECT_EQ(board.isOccupied(make_pair(4, 4)), false);
}
TEST(Board, movePieceTest) {
	Board board;
	Piece piece(Color::WHITE, Type::Piece);
	board.addPiece(make_shared<piece>, make_pair(3, 3));

	board.movePiece(make_pair(3, 3), make_pair(3, 4));

	EXPECT_EQ(board.isOccupied(make_pair(3, 3)), false);
	EXPECT_EQ(board.isOccupied(make_pair(3, 4)), true);
}

#endif
