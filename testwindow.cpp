#include "testwindow.h"
#include "ui_testwindow.h"

TestWindow::TestWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TestWindow)
{
    ui->setupUi(this);
    card_test = new CardTest();
    testScene = new QGraphicsScene(0, 0, 400, 400, this);
    testScene->addItem(card_test);
    ui->testView->setScene(testScene);
    ui->testView->setRenderHint(QPainter::Antialiasing);
    ui->testView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    ui->testView->setFixedSize(200, 200);
    ui->testView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->testView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

TestWindow::~TestWindow()
{
    delete ui;
}
