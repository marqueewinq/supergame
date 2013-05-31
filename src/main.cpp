#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.app = &a;
    for (int i = 0; i < argc; i++)
        if (QString(argv[i]).toUpper() == QString("-cheats").toUpper())
            w.enableCheats();

    w.show();
    w.showMaximized();

    return a.exec();
}
