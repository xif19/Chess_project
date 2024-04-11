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

Chess_project::Chess_project(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Chess_projectClass)
{
    ui->setupUi(this);


    QGridLayout* gridLayout = new QGridLayout(ui->chessFrameWidget);
    gridLayout->setSpacing(0);
    gridLayout->setContentsMargins(0, 0, 0, 0);
    Board board;

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            QPushButton* button = new QPushButton(this);
            button->setFixedSize(50, 50);
            button->setStyleSheet("QPushButton { margin: 0; padding: 0; background-color: " + QString(((row + col) % 2 == 0) ? "white" : "lightgray") + "; }");
            gridLayout->addWidget(button, row, col);

            connect(button, &QPushButton::clicked, this, [=]() { handleSquareClick(row, col); });
        }
    }

}

Chess_project::~Chess_project()
{
    delete ui;
}

void Chess_project::mousePressEvent(QMouseEvent* event) {
    qDebug() << event->pos();
}

void Chess_project::handleSquareClick(int row, int col)
{
    qDebug() << "Square clicked at: (" << row << ", " << col << ")";
    
}

