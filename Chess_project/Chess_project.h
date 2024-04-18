#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Chess_project.h"
#include <QMouseEvent>
#include <iostream>
#include <iomanip>
#include "Board.h"
#include <QGraphicsView>
#include <qpushbutton.h>
#include <QMessageBox>

namespace vue {
    enum enumImages { KING_B = 0, KING_W, QUEEN_B, QUEEN_W, ROOK_B, ROOK_W, KNIGHT_B, KNIGHT_W, PAWN_B, PAWN_W, BISHOP_B, BISHOP_W};
    class Chess_project : public QMainWindow
    {
        Q_OBJECT

    public:
        Chess_project(QWidget* parent = nullptr);
        ~Chess_project();
        void mousePressEvent(QMouseEvent* event);
        void handleMousePress(QGraphicsSceneMouseEvent* event);
        void init(QGridLayout* gridLayout);
        void putIcon(QPushButton* button, enumImages image);

    private:
        Ui::Chess_projectClass* ui;
        QGraphicsView* graphicsView;
        vector<vector<QPushButton*>> gridButtons;
        QVector<QPixmap> pieceImages;


    private slots:
        void handleSquareClick();
        void on_acceptMenuButton_clicked();

    };
}
