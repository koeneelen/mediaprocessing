#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , gameData(":/images/worldmap4.png")
    , controller(gameData)
    , worldView(gameData, &controller, this)
{
    ui->setupUi(this);
    QObject::connect(&controller, &WorldController::protagonistPositionChanged,
                     &worldView, &WorldView::updateProtagonistPosition);

    setCentralWidget(&worldView);
    worldView.show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
