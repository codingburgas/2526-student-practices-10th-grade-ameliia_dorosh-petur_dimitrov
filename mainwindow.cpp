#include "mainwindow.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent){

    setWindowTitle("Kino-Plex");
    setMinimumSize(1100,700);
    resize(1400, 860);



}

MainWindow::~MainWindow()
{

}
