#include "mynwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MynWindow w;
    w.show();

    return a.exec();
}
