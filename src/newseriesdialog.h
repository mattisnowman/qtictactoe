#ifndef NEWSERIESDIALOG_H
#define NEWSERIESDIALOG_H

#include <QDialog>

class QComboBox;
class QLineEdit;


class Actor;

class NewSeriesDialog : public QDialog
{
    Q_OBJECT

public:

    NewSeriesDialog(QWidget *parent = nullptr);

    void generateActorsAndStart();

public slots:

    void updateDialog();

signals:
    void startNewSeries(QList<Actor *> actors);

private:
    QComboBox *player1, *player2, *ai1, *ai2;

    QLineEdit *name1, *name2;

};

#endif // NEWSERIESDIALOG_H
