#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "gamewindow.h"
#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class GameBoard;
}
QT_END_NAMESPACE

class GameBoard : public QMainWindow
{
    Q_OBJECT

public:
    GameBoard(QWidget *parent = nullptr);
    ~GameBoard();

private slots:
    void on_pushButton_clicked();
    void signal_slot_function();

private:
    Ui::GameBoard *ui;
    GameWindow *game;
    QTimer *timer;
};
#endif // GAMEBOARD_H
