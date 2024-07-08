#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->magnify, SIGNAL(clicked()), this, SLOT(showMaximized()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
