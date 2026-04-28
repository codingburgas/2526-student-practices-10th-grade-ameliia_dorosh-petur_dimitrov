#include "mainwindow.h"
#include "database/database.h"


#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow mainWindow;

    Database::createInstance();

    QFile styleFile(":/styles/styles/app.qss");
    if (styleFile.open(QFile::ReadOnly)) {
        QString style = styleFile.readAll();
        app.setStyleSheet(style);
        styleFile.close();
    }

    mainWindow.show();
    return app.exec();
}
