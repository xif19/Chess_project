#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Chess_project.h"
#include <QMouseEvent>
#include <iostream>
#include <iomanip>
#include "Board.h"
#include <QGraphicsView>
#include "gridButton.h"
#include <qpushbutton.h>

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
    //QVector<QVector<gridButton*>> buttons2DVector;

private slots:
    void handleSquareClick(int row, int col);
    
};
