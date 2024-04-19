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
namespace vue {

    Chess_project::Chess_project(QWidget* parent)
        : QMainWindow(parent), ui(new Ui::Chess_projectClass), board()
    {
        ui->setupUi(this);
        //GridLayout in the widget specified for the chess frame
        QGridLayout* gridLayout = new QGridLayout(ui->chessFrameWidget);
        initBoard(gridLayout);

        //TODO: add this in a function 
        //The different options in the list widget 
        QListWidgetItem* item = new QListWidgetItem(QIcon("Images/Rook_W"), "Rook Double Attack");
        ui->listWidget->addItem(item);
        ui->listWidget->addItem("test");
    }

    Chess_project::~Chess_project()
    {
        delete ui;
        
    }
    
    void Chess_project::initBoard(QGridLayout* gridLayout) {


        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(0, 0, 0, 0);

        //Preloading images in the vector 
        pieceImages.append(QPixmap("Images/King_B.png")); //0
        pieceImages.append(QPixmap("Images/King_W.png")); //1
        pieceImages.append(QPixmap("Images/Queen_B.png")); //2
        pieceImages.append(QPixmap("Images/Queen_W.png")); //3 
        pieceImages.append(QPixmap("Images/Rook_B.png")); //4 
        pieceImages.append(QPixmap("Images/Rook_W.png")); // 5
        pieceImages.append(QPixmap("Images/Knight_B.png")); //6 
        pieceImages.append(QPixmap("Images/Knight_W.png")); //7
        pieceImages.append(QPixmap("Images/Pawn_B.png")); //8
        pieceImages.append(QPixmap("Images/Pawn_W.png")); //9
        pieceImages.append(QPixmap("Images/Bishop_B.png")); //10
        pieceImages.append(QPixmap("Images/Bishop_W.png")); // 11


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

    void Chess_project::handleSquareClick()
    {

        //Gets the specified button
        QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());

        //Add image if theres nothing 
        if (clickedButton->icon().isNull()) {
            QIcon ButtonIcon(pieceImages[enumImages::PAWN_B]);
            clickedButton->setIcon(ButtonIcon);
            clickedButton->setIconSize(QSize(50, 50));
        }
        else {
            //Remove the image if theres something 
            clickedButton->setIcon(QIcon());
        }

        //Find position in the gridPane
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
    }

    void Chess_project::on_acceptMenuButton_clicked() {

        ui->listWidget->currentItem()->setBackground(Qt::red);

        //TODO: make sure to delete all the board and reset everything when this button is pressed a second time.
        //Checks if the clicked item is the one that matches the text
        if (ui->listWidget->currentItem()->text() == "Rook Double Attack") {
            board.cleanBackendBoard();
            clearBoard();
            board.initBoard0();
            loadPiecesOnBoard();
        }

        if (ui->listWidget->currentItem()->text() == "test") {
            board.cleanBackendBoard();
            clearBoard();
        }
    }

    void Chess_project::loadPiecesOnBoard() {
        for (int col = 0; col < 8; col++) {
            for (int row = 0; row < 8; row++) {
                pair<int, int> position = make_pair(row, col);
                if (board.isOccupied(position) == true) {
                    shared_ptr<Piece> piece = board.getPieceAtPos(position);
                    QPushButton* button = gridButtons[row][col];
                    putIcon(button, findImage(piece));
                }
            }
        }
    }
    
    void Chess_project::clearBoard() {
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