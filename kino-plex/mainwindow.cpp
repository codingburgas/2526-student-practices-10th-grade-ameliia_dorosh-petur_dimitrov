#include "mainwindow.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QPixmap>
#include "pages/logandregisterpage.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent){

    setWindowTitle("Kino-Plex");
    setMinimumSize(1100,700);
    resize(1400, 860);

    // this just showss the logandregisterpage first as a central widget
    LogAndRegisterPage *authPage = new LogAndRegisterPage(this);
    setCentralWidget(authPage);


}

MainWindow::~MainWindow()
{

}
