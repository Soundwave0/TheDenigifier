#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Set application properties
    app.setApplicationName("The Denigifier");
    app.setApplicationVersion("0.1");
    app.setOrganizationName("Soundwave0");

    MainWindow window;
    window.show();

    return app.exec();
}
