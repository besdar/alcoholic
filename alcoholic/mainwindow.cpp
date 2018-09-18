#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <unistd.h> //sleep
#include "card.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QActionGroup * ColCards = new QActionGroup(this); //for radiobutton at MenuBar
    ColCards->addAction(ui->action36);
    ColCards->addAction(ui->action52);
    ColCards->addAction(ui->action54);
    QActionGroup * GameRules = new QActionGroup(this);
    GameRules->addAction(ui->notstandardgametype);
    GameRules->addAction(ui->standartgametype);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_triggered()
{
    unsigned short CardCounts = 36;                        //easy
    if (ui->action52->isChecked()) {CardCounts = 52;}      //medium
    else if (ui->action54->isChecked()) {CardCounts = 54;} //hardcore
    else {CardCounts = 36;} //if not sure
    bool GameRule; // 1 for standard mode, 0 for poddavki
    if (ui->notstandardgametype->isChecked()) {GameRule = false;}
    else {GameRule = true;}

    Coloda player1(CardCounts); //new Coloda of 1st player from Jockers only
    Coloda player2(CardCounts);
    int player1ball = 0, player2ball = 0; //balls of each player
    player1.shuffle();

    CardCounts/=2; //sharing
    player2 = player1.share(CardCounts);
    ui->label_3->setText(QString::number(player1.getcolvo())+" карт");
    ui->label_3->repaint();
    ui->cardsplayer2->setText(QString::number(player2.getcolvo())+" карт");
    ui->cardsplayer2->repaint();

    //actually game:
    for (unsigned short i = 0; i < CardCounts; i++) {
        if (player1.getcard(i).getvalue() > player2.getcard(i).getvalue()) {player1ball++;}
        else if (player1.getcard(i).getvalue() < player2.getcard(i).getvalue()) {player2ball++;}
        ui->picplayer1->setPixmap(player1.getcard(i).getpic());
        ui->picplayer1->repaint();
        ui->picplayer2->setPixmap(QPixmap(player2.getcard(i).getpic()));
        ui->picplayer2->repaint();
        ui->ochkoplayer1->setText(QString::number(player1ball));
        ui->ochkoplayer1->repaint();
        ui->ochkoplayer2->setText(QString::number(player2ball));
        ui->ochkoplayer2->repaint();
        sleep(1);
    }
    if (GameRule) {
        if (player1ball > player2ball) {QMessageBox::about(this, "Поздравляю!", "Выиграл игрок №1");}
        else if (player1ball < player2ball) {QMessageBox::about(this, "Поздравляю!", "Выиграл игрок №2");}
        else {QMessageBox::about(this, "Поздравляю!", "Сыграна ничья");}
    }
    else {
        if (player1ball < player2ball) {QMessageBox::about(this, "Поздравляю!", "Выиграл игрок №1");}
        else if (player1ball > player2ball) {QMessageBox::about(this, "Поздравляю!", "Выиграл игрок №2");}
        else {QMessageBox::about(this, "Поздравляю!", "Сыграна ничья");}
    }
}
