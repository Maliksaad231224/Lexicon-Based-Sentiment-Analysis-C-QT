#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QIcon icon(":/ico/Icon/movies-thor-hammer-thor-2-the-dark-world-wallpaper-preview.jpg");


    a.setWindowIcon(icon);
    MainWindow w;

    w.show();
    return a.exec();
}
