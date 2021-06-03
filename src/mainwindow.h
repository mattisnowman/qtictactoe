#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>

#include "newseriesdialog.h"
#include "gamescene.h"

class Actor;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = 0);

    ~MainWindow();

    void newSeries();

    void startNewSeries(QList<Actor*> actors);

    void exit();

private:

    GameScene *board;

    QGraphicsView *viewWidget;

    NewSeriesDialog *newDialog;

};

#endif // MAINWINDOW_H
