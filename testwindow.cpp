#include "testwindow.h"
#include "ui_testwindow.h"

TestWindow::TestWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TestWindow)
{
    ui->setupUi(this);
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    CardTest *card_test = new CardTest();
    card_test->setCardParams();

    layout->addWidget(card_test);
    setCentralWidget(card_test);
    resize(400, 300);
}

TestWindow::~TestWindow()
{
    delete ui;
}
