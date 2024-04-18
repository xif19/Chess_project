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
        : QMainWindow(parent), ui(new Ui::Chess_projectClass)
    {
        ui->setupUi(this);
        Board board;
        QGridLayout* gridLayout = new QGridLayout(ui->chessFrameWidget);


        init(gridLayout);
        QListWidgetItem* item = new QListWidgetItem(QIcon("chess_piece_rook.png"), "Rook Double Attack");
        ui->listWidget->addItem(item);
        ui->listWidget->addItem("test");
    }

    Chess_project::~Chess_project()
    {
        delete ui;
    }

    void Chess_project::init(QGridLayout* gridLayout) {


        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(0, 0, 0, 0);

        //Preloading images in the vector 
        pieceImages.append(QPixmap("Images/King_B.png"));
        pieceImages.append(QPixmap("Images/King_W.png"));
        pieceImages.append(QPixmap("Images/Queen_B.png"));
        pieceImages.append(QPixmap("Images/Queen_W.png"));
        pieceImages.append(QPixmap("Images/Rook_B.png"));
        pieceImages.append(QPixmap("Images/Rook_W.png"));
        pieceImages.append(QPixmap("Images/Knight_B.png"));
        pieceImages.append(QPixmap("Images/Knight_W.png"));
        pieceImages.append(QPixmap("Images/Pawn_B.png"));
        pieceImages.append(QPixmap("Images/Pawn_W.png"));
        pieceImages.append(QPixmap("Images/Bishop_B.png"));
        pieceImages.append(QPixmap("Images/Bishop_W.png"));

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

        if (ui->listWidget->currentItem()->text() == "Rook Double Attack") {
            for (int col = 0; col < 8; col++) {
                QPushButton* button = gridButtons[0][col];
                putIcon(button, enumImages::KING_W);
            }
        }
    }

    void Chess_project::putIcon(QPushButton* button, enumImages image) {
        QPixmap pixmap(pieceImages[image]);
        QIcon ButtonIcon(pixmap);
        button->setIcon(ButtonIcon);
        button->setIconSize(QSize(50, 50));
    }
}