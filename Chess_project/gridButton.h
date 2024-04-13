#pragma once

#include "Chess_project.h"
#include <QPushButton>
#include <QGridLayout>
#include <qpushbutton.h>

class gridButton : public QPushButton
{
    Q_OBJECT

public:
    gridButton(const QString& text, QWidget* parent = 0);
    gridButton(QWidget* parent, int row, int col);

    //Getters
    int getRow() const;
    int getCol() const;

private:
    int row_;
    int col_;
};