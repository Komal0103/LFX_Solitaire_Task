#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QWidget>
#include <QVBoxLayout>
#include "cardtest.h"
#include "stacktest.h"

namespace Ui {
class TestWindow;
}

class TestWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TestWindow(QWidget *parent = nullptr);
    ~TestWindow();

private:
    Ui::TestWindow *ui;
    QGraphicsScene *testScene;
    CardTest* card_test;
    StackTest *stack_test;
};

#endif // TESTWINDOW_H
