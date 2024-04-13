#include "gridButton.h"

gridButton::gridButton(QWidget* parent, int row, int col) : QPushButton(parent), row_(row), col_(col) {
    setFixedSize(50, 50);
    setStyleSheet("QPushButton { margin: 0; padding: 0; background-color: " + QString(((row + col) % 2 == 0) ? "white" : "lightgray") + "; }");
}

int gridButton::getRow() const {
    return row_;
}

int gridButton::getCol() const {
    return col_;
}