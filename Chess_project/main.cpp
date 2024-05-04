/**
*  This program is a chess game made using C++ and Qt. 
* \file   td6.cpp
* \author Maxence Grondin, Thomas Thibodeau et Matthew Hantar
* \date   3 mai 2024
* Créé le  1 avril 2024
*/

#include "Chess_project.h"
#include <QtWidgets/QApplication>
#include <memory>




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    vue::Chess_project w;
    w.show();
    
    return a.exec();
}
