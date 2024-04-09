#include "Chess_project.h"
#include <iostream>
#include <iomanip>

Chess_project::Chess_project(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Chess_projectClass)
{
    ui->setupUi(this);
}

Chess_project::~Chess_project()
{}


void Chess_project::mousePressEvent(QMouseEvent* event) {
    qDebug() << event->pos();
}

