#include "gameboard.h"
#include "./ui_gameboard.h"
#include <QDebug>
#include <QDateTime>

GameBoard::GameBoard(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameBoard)
{
    ui->setupUi(this);
    timer = new QTimer (this);
    connect (timer, SIGNAL(timeout()), this, SLOT(signal_slot_function()));
    timer->start(1000);
}

GameBoard::~GameBoard()
{
    delete ui;
}

void GameBoard::on_pushButton_clicked()
{
    QString username = ui->lineEdit->text();
    ui->label->setText("Starting Game Now...");
    hide();
    game = new GameWindow(this, username);
    game->show();
}

void GameBoard::signal_slot_function()
{
    QTime time = QTime::currentTime();
    QString time_text = time.toString("hh:mm:ss");
    ui->label_3_dt->setText(time_text);
}

