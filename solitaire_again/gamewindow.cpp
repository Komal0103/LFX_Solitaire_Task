#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <bits/stdc++.h>

GameWindow::GameWindow(QWidget *parent, QString uname)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow)
{
    initial_time = QTime::currentTime();
    ui->setupUi(this);
    timer = new QTimer (this);
    connect (timer, SIGNAL(timeout()), this, SLOT(display_timer()));
    timer->start(1000);
    shuffle_deck();
    assign_cards();
}

void GameWindow::display_timer() {
    QTime current_time = QTime::currentTime();
    int seconds = initial_time.secsTo(current_time);
    int minutes = seconds/60;
    QTime time_to_display(0, minutes, seconds);
    QString time_text = time_to_display.toString("hh:mm:ss");
    ui->lcdNumber->display(time_text);
}

QVector<int> GameWindow::shuffle_deck()
{
    // shuffle the deck in the enum
    unsigned seed = 9;
    QVector<int> to_shuffle_array;
    for (int i=ALL_CARDS::D1; i<=ALL_CARDS::SK; i++) {
        to_shuffle_array.push_back(i);
    }
    std::shuffle (to_shuffle_array.begin(), to_shuffle_array.end(), std::default_random_engine(seed));
    return to_shuffle_array;
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::on_pushButton_clicked()
{
    close();
}


void GameWindow::on_pushButton_3_clicked()
{
    // implement next card displaying functionality of card
}

