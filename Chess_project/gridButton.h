#pragma once

#include "Chess_project.h"
#include <QPushButton>
#include <QGridLayout>

class gridButton : public QPushButton
{
public:
    gridButton(QWidget* parent, int row, int col);

    //Getters
    int getRow() const;
    int getCol() const;

private:
    int row_;
    int col_;
};