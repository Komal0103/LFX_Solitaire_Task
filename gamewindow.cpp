#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <bits/stdc++.h>
#include <QDebug>
#include <QSettings>

GameWindow::GameWindow(QWidget *parent, QString uname)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    ui->label->setText(uname);
    restoreSettings();
    initial_time = QTime::currentTime();
    timer = new QTimer (this);
    connect (timer, SIGNAL(timeout()), this, SLOT(display_timer()));
    timer->start(1000);
    QVector<int> shuffled = shuffle_deck();
    assign_cards(shuffled);

    scene = new QGraphicsScene(0, 0, 400, 400, this);
    scene->addItem(stack);
    ui->cardStack->setScene(scene);
    ui->cardStack->setRenderHint(QPainter::Antialiasing);
    ui->cardStack->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    ui->cardStack->setFixedSize(200, 200);

    int view_height = ui->foundationD->height();
    int view_width = ui->foundationD->width();

    // set up foundations
    d_scene = new QGraphicsScene(0, 0, view_width, view_height, this);
    d = new Foundation(view_width, view_height);
    d_scene->addItem(d);
    ui->foundationD->setScene(d_scene);
    ui->foundationD->setRenderHint(QPainter::Antialiasing);
    ui->foundationD->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    h_scene = new QGraphicsScene(0, 0, view_width, view_height, this);
    h = new Foundation(view_width, view_height);
    h_scene->addItem(h);
    ui->foundationH->setScene(h_scene);
    ui->foundationH->setRenderHint(QPainter::Antialiasing);
    ui->foundationH->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    c_scene = new QGraphicsScene(0, 0, view_width, view_height, this);
    c = new Foundation(view_width, view_height);
    c_scene->addItem(h);
    ui->foundationC->setScene(c_scene);
    ui->foundationC->setRenderHint(QPainter::Antialiasing);
    ui->foundationC->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    s_scene = new QGraphicsScene(0, 0, view_width, view_height, this);
    s = new Foundation(view_width, view_height);
    s_scene->addItem(h);
    ui->foundationS->setScene(s_scene);
    ui->foundationS->setRenderHint(QPainter::Antialiasing);
    ui->foundationS->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
}

void GameWindow::display_timer() {
    QTime current_time = QTime::currentTime();
    int seconds = initial_time.msecsTo(current_time);
    QTime time_to_display(0, 0);
    time_to_display = time_to_display.addMSecs(seconds);
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

void GameWindow::assign_cards(QVector<int> shuffled_deck)
{
    QVector<int> for_stack(24);
    for (int i=0; i<24; ++i) {
        for_stack[i] = shuffled_deck[i];
    }
    stack = new Stack(for_stack);
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::on_pushButton_clicked()
{
    close();
}

void GameWindow::on_saveAndExit_clicked()
{
    QSettings settings("hehe", "Solitaire");
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());
    close();
}

void GameWindow::restoreSettings() {
    QSettings settings("hehe", "Solitaire");
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray());
}

void GameWindow::on_next_clicked()
{
    qDebug() << "handing over functionality to Stack function";
    stack->switch_to_next_card();
}
