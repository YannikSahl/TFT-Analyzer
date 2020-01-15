#include "mainwindow.h"
#include "analyticswindow.h"
#include <QApplication> // Widgets, Event handling, Mouse movement

// Let's go
int main(int argc, char *argv[])
{
    // Object to handle stuff (see above)
    QApplication a(argc, argv);

    // Create and show main window
    MainWindow mainWin;
    mainWin.show();

    // Handler loop
    return a.exec();
}
