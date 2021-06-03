#include "mainwindow.h"

#include <QMenuBar>

#include "botactor.h"
#include "playeractor.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), newDialog(nullptr)
{
    this->board = new GameScene(this);
    this->viewWidget = new QGraphicsView(this);
    this->viewWidget->setScene(this->board);
    this->viewWidget->setSceneRect(0, 0, 300, 300);
    this->setCentralWidget(this->viewWidget);
    this->viewWidget->setMinimumSize(400, 400);

    QMenu *gMenu = this->menuBar()->addMenu("game");
    gMenu->addAction("new game", this, &MainWindow::newSeries);
    gMenu->addAction("exit", this, &MainWindow::exit);
}


void MainWindow::newSeries()
{
    if (!this->newDialog) {
        this->newDialog = new NewSeriesDialog(this);
        connect(this->newDialog, &NewSeriesDialog::startNewSeries,
                this, &MainWindow::startNewSeries);
    }

    this->newDialog->show();
    this->newDialog->raise();
    this->newDialog->activateWindow();
}

void MainWindow::startNewSeries(QList<Actor *> actors)
{
    this->board->newSeries(actors);
}

void MainWindow::exit()
{

}

MainWindow::~MainWindow()
{

}
