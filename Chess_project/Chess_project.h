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

class Chess_project : public QMainWindow
{
    Q_OBJECT

public:
    Chess_project(QWidget *parent = nullptr);
    ~Chess_project();
    void mousePressEvent(QMouseEvent* event);
    void handleMousePress(QGraphicsSceneMouseEvent* event);
    void init(QGridLayout* gridLayout);
    

private:
    Ui::Chess_projectClass* ui;
    QGraphicsView* graphicsView;
    std::vector<std::vector<QPushButton*>> gridButtons;

private slots:
    void handleSquareClick();
    void on_acceptMenuButton_clicked();
    
};
