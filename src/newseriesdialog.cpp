#include "newseriesdialog.h"

#include <QGridLayout>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>
#include <QLabel>
#include <QDebug>

#include "botactor.h"
#include "playeractor.h"


NewSeriesDialog::NewSeriesDialog(QWidget *parent):
    QDialog(parent)
{

    this->setWindowTitle("new series");

    QGridLayout *l = new QGridLayout(this);

    l->addWidget(new QLabel("Player 1:", this), 0, 0, 1, 1);
    l->addWidget(new QLabel("Player 2:", this), 1, 0, 1, 1);

    player1 = new QComboBox(this);
    player1->addItems({"human", "computer"});
    player1->setCurrentIndex(0);
    l->addWidget(player1, 0, 1, 1, 1);

    connect(player1, SIGNAL(currentIndexChanged(int)),
            this, SLOT(updateDialog()));

    player2 = new QComboBox(this);
    player2->addItems({"human", "computer"});
    player2->setCurrentIndex(1);
    l->addWidget(player2, 1, 1, 1, 1);

    connect(player2, SIGNAL(currentIndexChanged(int)),
            this, SLOT(updateDialog()));

    l->addWidget(new QLabel("Who plays?", this), 0, 2, 1, 1);
    l->addWidget(new QLabel("Who plays?", this), 1, 2, 1, 1);

    ai1 = new QComboBox(this);
    ai1->addItems({"GoodBot", "WeiredBot", "GuessBot"});
    l->addWidget(ai1, 0, 3, 1, 1);

    ai2 = new QComboBox(this);
    ai2->addItems({"GoodBot", "WeiredBot", "GuessBot"});
    l->addWidget(ai2, 1, 3, 1, 1);


    name1 = new QLineEdit(this);
    name1->setText("Not a robot");
    l->addWidget(name1, 0, 3, 1, 1);

    name2 = new QLineEdit(this);
    name2->setText("Not a robot");
    l->addWidget(name2, 1, 3, 1, 1);


    ai1->setVisible(false);
    name2->setVisible(false);


    QPushButton *cancelB = new QPushButton("cancel", this);
    connect(cancelB, &QPushButton::pressed,
            this, &NewSeriesDialog::reject);

    QPushButton *okB = new QPushButton("start", this);
    connect(okB, &QPushButton::pressed,
            this, &NewSeriesDialog::generateActorsAndStart);

    QHBoxLayout *h = new QHBoxLayout();
    l->addLayout(h, 2, 0, 1, 4);
    h->addStretch();
    h->addWidget(cancelB);
    h->addWidget(okB);

    okB->setFocus();
}

void NewSeriesDialog::updateDialog()
{
    name1->setVisible((this->player1->currentIndex()==0));
    ai1->setVisible((this->player1->currentIndex()!=0));

    name2->setVisible((this->player2->currentIndex()==0));
    ai2->setVisible((this->player2->currentIndex()!=0));
}

void NewSeriesDialog::generateActorsAndStart()
{
    Actor *player1, *player2;
    if (this->player1->currentIndex()==0)
    {
        player1 = new PlayerActor(nullptr, 0, this->name1->text());
    }
    else
    {
        BotActor::Strategy s;
        switch (ai1->currentIndex())
        {
            case 0:
                s = BotActor::quickestWin;
            break;
            case 1:
                s = BotActor::highestProbability;
            break;
            case 2:
                s = BotActor::random;
        }
        player1 = new BotActor(nullptr, 0, ai1->currentText(), s);
    }
    if (this->player2->currentIndex()==0)
    {
        player2 = new PlayerActor(nullptr, 1, this->name2->text());
    }
    else
    {
        BotActor::Strategy s;
        switch (ai2->currentIndex())
        {
            case 0:
                s = BotActor::quickestWin;
            break;
            case 1:
                s = BotActor::highestProbability;
            break;
            case 2:
                s = BotActor::random;
        }
        player2 = new BotActor(nullptr, 1, ai2->currentText(), s);
    }

    emit startNewSeries({player1, player2});

    this->accept();
}
