/*
####################################################################
# TIE-02201 Ohjelmointi 2: Perusteet, K2019                        #
# TIE-02207 Programming 2: Basics, S2019                           #
#                                                                  #
# Project4: snek: The Revengeance                                  #
# Program description: "While revenge is served cold and vengeance #
#                       is served hot revengeance is often seen    #
#                       served with Cajun with a side of onion     #
#                       rings and often dumplings in the Orient."  #
#                       - urbandictionary                          #
#                                                                  #
# File: main_window.cpp                                            #
# Description: Defines a class implementing a UI for the game.     #
#                                                                  #
# Author: Saskia Simisker, 282598, saskia.simisker@tuni.fi         #
####################################################################
*/

#include "main_window.hh"
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QDir>

const QPoint LEFT = QPoint(-1, 0);
const QPoint UP = QPoint(0, -1);
const QPoint RIGHT = QPoint(1, 0);
const QPoint DOWN = QPoint(0, 1);

const QPen pen(Qt::white, 0);

MainWindow::MainWindow(QWidget* parent):
    QMainWindow(parent) {

    ui_.setupUi(this);
    ui_.graphicsView->setScene(&scene_);

    connect(&timer_, &QTimer::timeout, this, &MainWindow::moveSnake);
}

MainWindow::~MainWindow()
{
    delete snek_;
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
   if ((event->key() == Qt::Key_Up or event->key() == Qt::Key_W)
           and dir_ != DOWN) dir_ = UP;
   if ((event->key() == Qt::Key_Left or event->key() == Qt::Key_A)
           and dir_ != RIGHT) dir_ = LEFT;
   if ((event->key() == Qt::Key_Down or event->key() == Qt::Key_S)
           and dir_ != UP) dir_ = DOWN;
   if ((event->key() == Qt::Key_Right or event->key() == Qt::Key_D)
           and dir_ != LEFT) dir_ = RIGHT;
}

void MainWindow::on_playButton_clicked() {
    // button state switches, play and size off to prevent unintended behaviour
    ui_.pauseButton->setEnabled(true);
    ui_.restartButton->setEnabled(true);
    ui_.playButton->setEnabled(false);
    ui_.sizeButton->setEnabled(false);

    // defaults - dir unset to prevent accidental snek moving
    pause_state_ = false;
    dir_ = QPoint(0, 0);
    points_ = 0;

    // seeding based on current time
    long seed1 = std::chrono::system_clock::now().time_since_epoch().count();
    rng_.seed(static_cast<unsigned>(seed1));

    // create snek and head
    snek_ = new Snek(this, &scene_, area_width_, area_height_);

    // food item generation
    const QRectF rect(0, 0, 1, 1);
    const QBrush food_brush(Qt::black);
    food_ = scene_.addRect(rect, pen, food_brush);
    moveFood();


    adjustSceneArea();
    timer_.start(timer_value_);
}

void MainWindow::moveSnake() {
    // propagate body elements' locations
    snek_->propagate_tail();

    // update head location
    snek_->move_head(dir_);

    // food eating behaviour
    if (food_->scenePos() == snek_->head_position()) {
        points_ += 1;
        moveFood();

        // generate new snek segment
        snek_->extend();

        // difficulty increase
        timer_.stop();
        if (timer_value_ > 50) timer_value_ -= 3;
        timer_.start(timer_value_);
    }
}

void MainWindow::adjustSceneArea() {
    const QRectF area(0, 0, area_width_, area_height_);
    scene_.setSceneRect(area);
    ui_.graphicsView->fitInView(area);
}

void MainWindow::moveFood()
{
    QPoint new_loc = QPoint();
    while (true) {
        new_loc.setX(static_cast<int>(rng_()) % area_width_);
        new_loc.setY(static_cast<int>(rng_()) % area_height_);
        if (!snek_->is_occupied(new_loc)) break;
    }
    food_->setPos(new_loc);
}

void MainWindow::on_howButton_clicked()
{
    QMessageBox howBox;
    howBox.setText("<b>Instructions</b>"
                   "<p>snek is a classic game best known from certain models of"
                   " Nokia cell phones from the 1990s and 2000s.</p>"
                   "<p>The objective of the game is to feed the snek until it "
                   "fills the entire game area, without colliding into any "
                   "obstacles or the snek itself in that time.</p>"
                   "<b>Control scheme:</b><br>"
                   "W: Up<br>"
                   "A: Left<br>"
                   "S: Down<br>"
                   "D: Right");
    howBox.exec();
}

void MainWindow::on_scoresButton_clicked()
{
    QMessageBox scoresBox;

    Scorefile file;
    auto text = file.get_contents();

    scoresBox.setText(text);
}

void MainWindow::on_pauseButton_clicked()
{
    if (!pause_state_) {
        timer_.stop();
        ui_.pauseButton->setText("Resume");
        pause_state_ = true;
    }
    else {
        timer_.start(timer_value_);
        ui_.pauseButton->setText("Pause");
        pause_state_ = false;
    }
}

void MainWindow::on_sizeButton_clicked()
{
    bool width_ok;
    bool height_ok;
    int new_width = QInputDialog::getInt(this, tr("Game area width"),
                                            tr("Enter new game area width:"),
                                            area_width_, 1, 50, 1, &width_ok);
    int new_height = QInputDialog::getInt(this, tr("Game area height"),
                                          tr("Enter new game area height:"),
                                          area_height_, 1, 50, 1, &height_ok);
    if (width_ok) area_width_ = new_width;
    if (height_ok) area_height_ = new_height;
}
