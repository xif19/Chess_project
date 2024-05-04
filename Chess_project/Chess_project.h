#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Chess_project.h"
#include <QMouseEvent>
#include <iostream>
#include <iomanip>
#include "Game.h"
#include <QGraphicsView>
#include <qpushbutton.h>
#include <QMessageBox>
#include <algorithm>



enum enumImages { KING_B = 0, KING_W, QUEEN_B, QUEEN_W, ROOK_B, ROOK_W, KNIGHT_B, KNIGHT_W, PAWN_B, PAWN_W, BISHOP_B, BISHOP_W};

class Chess_project : public QMainWindow
{
    Q_OBJECT

public:
    Chess_project(QWidget* parent = nullptr);
    ~Chess_project();

    /**
    * Initializes the frontend board with a grid layout of buttons.
    * It also adds each image in the vector pieceImages for preloading.
    *
    * @param gridLayout: specified grid layout created in the constructor
    * 
    * @return nothing
    */
    void initBoard(QGridLayout* gridLayout);
        
    /**
    * Handles the times when the mouse is pressed on the screen.
    * It doesnt handle when the mouse is pressed on the buttons or other widgets.
    *
    * @param button: It's a square of the chessboard
    * @param image: The chosen piece's image
    * 
    * @return nothing
    */
    void putIcon(QPushButton* button, enumImages image);

    /**
    * It looks at the array of boxes from the Board class and it matches 1 to 1
    *   what exists already exists in the backend to the frontend. Use this 
    *   method everytime you want to load the pieces after a new init of pieces  
    *   in the Board class. 
    *
    * @param nothing
    *
    * @return nothing
    */
    void loadPiecesOnBoard();

    /**
    * Finds the color of a specified piece on the backend board 
    *
    * @param piece: It's the given piece
    *
    * @return bool: 0 is for black pieces/ 1 is for white pieces
    */
    bool findColor(shared_ptr<Piece> piece);

    /**
    * Finds the specified image of a given piece on the backend board
    *
    * @param piece: It's the given piece
    *
    * @return enumImages 
    */
    enumImages findImage(shared_ptr<Piece> piece);

    /**
    * Clears the frontend board by setting all the icons to null 
    *
    * @param void
    *
    * @return void
    */
    void clearBoard();

    /**
    * It's to load the pieces of the thrown error. It's mostly because the error 
    * of 3 kings is activated in the backend and that makes it so the frontend is 
    * never loaded. This function is just to show the board that has an error 
    * quickly. 
    *
    * @param void
    *
    * @return void
    */
    void load3KingsImages();

    /**
    * Resets the colors of the squares. 
    *
    * @param void
    *
    * @return void
    */
    void clearColor();

    /**
    * This function manages all the movement of the pieces depending on their
    * moves. It lets the user click on the pieces and show the good movements.
    *
    * @param pos: The position of a piece
    *
    * @return void
    */
    void interactWithPiece(pair<int, int> pos);

    /**
    * After a movement has been done, it switched the turns. 
    *
    * @param void
    *
    * @return void
    */
    void switchPlayerTurn();

    /**
    * It checks if the king is checkmate and if he is, the game
    * ends. 
    *
    * @param kingPos : The position of the king
    *
    * @return bool
    */
    bool isCheckMate(pair<int, int> kingPos);

    /**
    * It checks if the king is checkmate and if he is, the game
    * ends.
    *
    * @param kingPos : The position of the king
    *
    * @return bool
    */
    pair<int, int> findPosition(QPushButton* clickedButton);

    /**
    * It clears the board and shows a critical message to end the game
    *
    * @param void
    *
    * @return void
    */
    void showCheckMate();

    /**
    * It updates the two vertical layouts whenever a new piece dies. 
    *
    * @param color : The color of the vertical layout to refresh
    *
    * @return void
    */
    void displayDeadPieces(Color color);

    /**
    * It clears the specified layout of dead pieces
    *
    * @param layout 
    *
    * @return void
    */
    void clearDeadPiecesLayout(QLayout* layout);

    /**
    * It clears all the frontend layouts of dead pieces after a game is
    * finished. 
    *
    * @param layout
    *
    * @return void
    */
    void clearAllDeadPiecesLayouts();

private:
    Ui::Chess_projectClass* ui;
    QGraphicsView* graphicsView;
    vector<vector<QPushButton*>> gridButtons;
    QVector<QPixmap> pieceImages;

    //Everything for moving pieces
    vector<pair<int, int>> allPossibleMoves;
    shared_ptr<Piece> currentPiece;
    pair<int, int> oldPos;
    bool isPieceClicked = false;

    Game game;


private slots:
    /**
    * Everytime a square (button) on the grid layout is clicked, this
    *   function is called. 
    *
    * @param nothing
    *
    * @return nothing
    */
    void handleSquareClick();

    /**
    * Manages when the user has clicked the accept button after it has 
    *   clicked something from the list widget with all the different 
    *   choices of boards. 
    *
    * @param nothing
    *
    * @return nothing
    */
    void on_acceptMenuButton_clicked();

    /**
    * Changes the text of the turn.
    *
    * @param text 
    *
    * @return nothing
    */
    void turnLabel(const QString text);

};

