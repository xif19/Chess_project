
/**
* Cette classe gere le comportement de la partie, l'initialisation du jeu et de ses composants ainsi que la gestions du lien entre le front end et le back end.
* \file   Chess_project.h
* \author Maxence Grondin, Thomas Thibodeau et Matthew Hantar
* \date  21 avril 2024
* Cr�� le 1er avril 2024
*/

#include "Chess_project.h"
#include <iostream>
#include <iomanip>
#include <QLabel>
#include <QPainter>
#include <QtGui>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <qpushbutton.h>

using namespace modele;
namespace vue {

    Chess_project::Chess_project(QWidget* parent)
        : QMainWindow(parent), ui(new Ui::Chess_projectClass), game()
    {
        ui->setupUi(this);
        //GridLayout in the widget specified for the chess frame
        QGridLayout* gridLayout = new QGridLayout(ui->chessFrameWidget);
        initBoard(gridLayout);
        turnLabel("WHITE'S TURN");

        
        //TODO: add this in a function 
        //The different options in the list widget 
        QListWidgetItem* item = new QListWidgetItem(QIcon("Images/Rook_W"), "Rook Double Attack");
        ui->listWidget->addItem(item);
        QListWidgetItem* item2 = new QListWidgetItem(QIcon("Images/King_B"), "TRIPLE KING THREAT");
        ui->listWidget->addItem(item2);
        QListWidgetItem* item3 = new QListWidgetItem(QIcon("Images/Queen_B"), "The Queen's Testing Gardens");
        ui->listWidget->addItem(item3);
        
        game.getBoard().deadWhitePiece.push_back(Type::KING);
       
    }

    void Chess_project::updateDeadWhitePiecesVBox() {
        // Clear the existing items in the vbox
        QLayoutItem* item;
        while ((item = ui->deadWhitePiecesVbox->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }

        // Iterate through the deadWhitePiece vector
        qDebug() << game.getBoard().deadWhitePiece.size();
        for (const auto& piece : game.getBoard().deadWhitePiece) {
            // Create a label to display the image of the dead piece
            QLabel* label = new QLabel(this);
            QPixmap pixmap = pieceImages[enumImages::KING_W];
            label->setPixmap(pixmap.scaled(50, 50)); // Adjust size if needed
            ui->deadWhitePiecesVbox->addWidget(label);
        }
    }


    Chess_project::~Chess_project()
    {
        delete ui;

        for (int col = 0; col < 8; col++) {
            for (int row = 0; row < 8; row++) {
                  QPushButton* button = gridButtons[row][col];
                  delete button;
            }
        }
        
    }
    
    void Chess_project::initBoard(QGridLayout* gridLayout) {


        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(0, 0, 0, 0);

        //Preloading images in the vector 
        pieceImages.append(QPixmap("Images/King_W.png")); //0
        pieceImages.append(QPixmap("Images/King_B.png")); //1
        pieceImages.append(QPixmap("Images/Queen_W.png")); //2
        pieceImages.append(QPixmap("Images/Queen_B.png")); //3 
        pieceImages.append(QPixmap("Images/Rook_W.png")); //4 
        pieceImages.append(QPixmap("Images/Rook_B.png")); // 5
        pieceImages.append(QPixmap("Images/Knight_W.png")); //6 
        pieceImages.append(QPixmap("Images/Knight_B.png")); //7
        pieceImages.append(QPixmap("Images/Pawn_W.png")); //8
        pieceImages.append(QPixmap("Images/Pawn_B.png")); //9
        pieceImages.append(QPixmap("Images/Bishop_W.png")); //10
        pieceImages.append(QPixmap("Images/Bishop_B.png")); // 11


        //Creates the chessboard and connects every button to the handleSquareClick method
        for (int row = 0; row < 8; ++row) {
            vector<QPushButton*> rowButtons;
            for (int col = 0; col < 8; ++col) {
                QPushButton* button = new QPushButton(this);
                button->setFixedSize(50, 50);
                button->setStyleSheet("QPushButton { margin: 0; padding: 0; background-color: " + QString(((row + col) % 2 == 0) ? "white" : "lightgray") + "; }");
                gridLayout->addWidget(button, row, col);

                connect(button, &QPushButton::clicked, this, &Chess_project::handleSquareClick);

                rowButtons.push_back(button);
            }
            gridButtons.push_back(rowButtons);
        }

    }

    void Chess_project::mousePressEvent(QMouseEvent* event) {
        qDebug() << event->pos();
    }

    /**
    * Everytime a square (button) on the grid layout is clicked, this
    *   function is called.
    *
    * @param nothing
    *
    * @return nothing
    */
    void Chess_project::handleSquareClick()
    {   
        clearColor();

        //Gets the specified button
        QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());

        //get position
        pair<int, int> pos = findPosition(clickedButton);

        //The logic to move piece and everything else surrounding the board
        interactWithPiece(pos);


    }

    void Chess_project::turnLabel(const QString text)
    {
        ui->turnLabel->setText(text);
    }

    void Chess_project::on_acceptMenuButton_clicked() {

        try {
            if (ui->listWidget->currentItem()->text() == "Rook Double Attack") {
                game.getBoard().cleanBackendBoard();
                clearBoard();
                game.getBoard().initBoard0();
                loadPiecesOnBoard();
            }

            if (ui->listWidget->currentItem()->text() == "TRIPLE KING THREAT") {
                game.getBoard().cleanBackendBoard();
                clearBoard();
                game.getBoard().initBoard1();
                loadPiecesOnBoard();
            }

            if (ui->listWidget->currentItem()->text() == "The Queen's Testing Gardens") {
                game.getBoard().cleanBackendBoard();
                clearBoard();
                game.getBoard().initBoard2();
                loadPiecesOnBoard();
            }
        }
        catch (const runtime_error& e) {
            load3KingsImages();
            QMessageBox::critical(this, "HUGE ERROR", QString("This is not real chess: %1").arg(e.what()));
            clearBoard();

        }
    }

    void Chess_project::interactWithPiece(pair<int, int> pos) {

        /*
        * It checks if a piece has already been clicked, if yes it proceeds to move it.
        * Else, it gets the piece and checks all the possible moves available.
        */
        if (isPieceClicked) {
            // Check if it's a valid move
            auto it = std::find(allPossibleMoves.begin(), allPossibleMoves.end(), pos);
            if (it != allPossibleMoves.end()) {
                // Move the piece
                if (game.getBoard().isOccupied(oldPos)) {
                    game.getBoard().movePiece(oldPos, pos);
                    QPushButton* oldButton = gridButtons[oldPos.first][oldPos.second];
                    oldButton->setIcon(QIcon());

                    QPushButton* newButton = gridButtons[pos.first][pos.second];
                    putIcon(newButton, findImage(currentPiece));

                    
                    qDebug() << "piece moved";
                    switchPlayerTurn();
                }
            }
            else {
                qDebug() << "Nope bad move";
            }

            // Reset 
            isPieceClicked = false;
            allPossibleMoves.clear();
            clearColor();
            oldPos = {};
            currentPiece = nullptr;
        }
        else {
            // When a new piece is clicked
            if (game.getBoard().isOccupied(pos)) {
                currentPiece = game.getBoard().getPieceAtPos(pos);
                if (currentPiece->getColor() == game.getCurrentPlayer()) {
                    QPushButton* ownButton = gridButtons[pos.first][pos.second];
                    ownButton->setStyleSheet("background-color: green");

                    allPossibleMoves = game.getMoveValidPiece(pos);
                    oldPos = pos;
                    isPieceClicked = true;

                    for (int i = 0; i < allPossibleMoves.size(); i++) {
                        QPushButton* button = gridButtons[allPossibleMoves[i].first][allPossibleMoves[i].second];
                        button->setStyleSheet("background-color: lightgreen");
                    }
                }
            }
        }
    }

    void Chess_project::switchPlayerTurn() {
        if (game.getCurrentPlayer() == Color::BLACK) {
            game.setCurrentPlayer(Color::WHITE);
            turnLabel("Tour du joueur Blanc");
        }
        else {
            game.setCurrentPlayer(Color::BLACK);
            turnLabel("Tour du joueur Noir");
            updateDeadWhitePiecesVBox();
        }
    }

   

    pair<int, int> Chess_project::findPosition(QPushButton* clickedButton) {
        int row = -1, col = -1;
        for (size_t i = 0; i < gridButtons.size(); i++) {
            auto it = std::find(gridButtons[i].begin(), gridButtons[i].end(), clickedButton);
            if (it != gridButtons[i].end()) {
                row = i;
                col = it - gridButtons[i].begin();
                break;
            }
        }
        qDebug() << "Pos Button: " << row << ", " << col;
        return make_pair(row, col);
    }

    void Chess_project::clearColor() {
        for (int col = 0; col < 8; col++) {
            for (int row = 0; row < 8; row++) {
                QPushButton* button = gridButtons[row][col];
                button->setStyleSheet("QPushButton { margin: 0; padding: 0; background-color: " + QString(((row + col) % 2 == 0) ? "white" : "lightgray") + "; }");
            }
        }
    }

    void Chess_project::loadPiecesOnBoard() {
        for (int col = 0; col < 8; col++) {
            for (int row = 0; row < 8; row++) {
                pair<int, int> position = make_pair(row, col);
                if (game.getBoard().isOccupied(position) == true) {
                    shared_ptr<Piece> piece = game.getBoard().getPieceAtPos(position);
                    QPushButton* button = gridButtons[row][col];
                    putIcon(button, findImage(piece));
                }
            }
        }
    }

    void Chess_project::load3KingsImages() {
        QPushButton* button = gridButtons[0][0];
        putIcon(button, enumImages::KING_B);

        QPushButton* button1 = gridButtons[3][3];
        putIcon(button1, enumImages::KING_B);

        QPushButton* button3 = gridButtons[5][5];
        putIcon(button3, enumImages::KING_W);
    }
    
    void Chess_project::clearBoard() {
        clearColor();
        for (int col = 0; col < 8; col++) {
            for (int row = 0; row < 8; row++) {
                QPushButton* button = gridButtons[row][col];
                button->setIcon(QIcon());
            }
        }
    }

    void Chess_project::putIcon(QPushButton* button, enumImages image) {
        QPixmap pixmap(pieceImages[image]);
        QIcon ButtonIcon(pixmap);
        button->setIcon(ButtonIcon);
        button->setIconSize(QSize(50, 50));
    }


    bool Chess_project::findColor(shared_ptr<Piece> piece) {
        if (piece->getColor() == Color::BLACK) {
            return 0;
        }
        else {
            return 1;
        }
    }


    enumImages Chess_project::findImage(shared_ptr<Piece> piece) {
        //Type King, Queen, Rook, Knight, Pawn, Bishop
        bool color = findColor(piece);
        switch (piece->getType()) {
            // 0 = black, 1 = white
            case Type::KING:
                if (color) {
                    return enumImages::KING_B;
                }
                else {
                    return enumImages::KING_W;
                }
                break;
            case Type::QUEEN:
                if (color) {
                    return enumImages::QUEEN_B;
                }
                else {
                    return enumImages::QUEEN_W;
                }
                break;
            case Type::ROOK:
                if (color) {
                    return enumImages::ROOK_B;
                }
                else {
                    return enumImages::ROOK_W;
                }
                break;
            case Type::KNIGHT:
                if (color) {
                    return enumImages::KNIGHT_B;
                }
                else {
                    return enumImages::KNIGHT_W;
                }
                break;
            case Type::PAWN:
                if (color) {
                    return enumImages::PAWN_B;
                }
                else {
                    return enumImages::PAWN_W;
                }
                break;
            case Type::BISHOP:
                if (color) {
                    return enumImages::BISHOP_B;
                }
                else {
                    return enumImages::BISHOP_W;
                }
                break;
        }
    }


}