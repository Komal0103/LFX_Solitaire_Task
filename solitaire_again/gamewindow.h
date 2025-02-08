#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include "card.h"
#include "cardpile.h"
#include "stack.h"

// the number of cards in each pile is (index of pile + 1)

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr, QString uname = NULL);
    void display_timer();
    QVector<int> shuffle_deck();
    void assign_cards();
    ~GameWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::GameWindow *ui;
    QTimer *timer;
    QTime initial_time;
    enum ALL_CARDS : int {
        D1, D2, D3, D4, D5, D6, D7, D8, D9, DJ, DQ, DK,
        H1, H2, H3, H4, H5, H6, H7, H8, H9, HJ, HQ, HK,
        C1, C2, C3, C4, C5, C6, C7, C8, C9, CJ, CQ, CK,
        S1, S2, S3, S4, S5, S6, S7, S8, S9, SJ, SQ, SK, JOKER
    };
    // have removed JOKER card
};

#endif // GAMEWINDOW_H
