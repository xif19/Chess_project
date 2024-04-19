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
