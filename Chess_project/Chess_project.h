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
using namespace modele;

namespace vue {
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
        * It doesnt handle when the mouse presses buttons or other widgets. 
        *
        * @param event : Clicking on the screen event
        * 
        * @return nothing
        */
        void mousePressEvent(QMouseEvent* event);
        
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

        void clearBoard();

        void load3KingsImages();

        void clearColor();

        void interactWithPiece(pair<int, int> pos);

        void switchPlayerTurn();

        bool isCheckMate(pair<int, int> kingPos);

        pair<int, int> findPosition(QPushButton* clickedButton);


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

        void turnLabel(const QString text);

    };
}
