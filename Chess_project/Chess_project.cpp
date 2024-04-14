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

    clickedButton->setStyleSheet("background-color: red");
    
    //Trouver la position du bouton dans le gridPane
    int row = -1, col = -1;
    for (size_t i = 0; i < gridButtons.size(); ++i) {
        auto it = std::find(gridButtons[i].begin(), gridButtons[i].end(), clickedButton);
        if (it != gridButtons[i].end()) {
            row = i;
            col = it - gridButtons[i].begin();
            break;
        }
    }

    qDebug() << "Pos Button: " << row << ", " << col;
}

void Chess_project::on_acceptMenuButton_clicked(){
    
    //QMessageBox::information(this, "title", ui->listWidget->currentItem()->text());
    
    ui->listWidget->currentItem()->setBackground(Qt::red);
}
