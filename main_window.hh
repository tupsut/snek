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
# File: main_window.hh                                             #
# Description: Declares a class implementing a UI for the game.    #
#                                                                  #
# Author: Saskia Simisker, 282598, saskia.simisker@tuni.fi         #
####################################################################
*/

#ifndef PRG2_SNAKE2_MAINWINDOW_HH
#define PRG2_SNAKE2_MAINWINDOW_HH

#include "ui_main_window.h"
#include "scorefile.hh"

#include <QGraphicsScene>
#include <QMainWindow>
#include <QTimer>
#include <random>
#include <QMessageBox>
#include <QInputDialog>
#include <vector>


/* \class MainWindow
 * \brief Implements the main window through which the game is played.
 */
class MainWindow: public QMainWindow {
    Q_OBJECT

public:

    /* \brief Construct a MainWindow.
     *
     * \param[in] parent The parent widget of this MainWindow.
     */
    explicit MainWindow(QWidget* parent = nullptr);

    /* \brief Destruct a MainWindow.
     */
    ~MainWindow() override = default;

    /* \brief Change the snek's bearing when certain keys get pressed.
     *
     * \param[in] event Contains data on pressed and released keys.
     */
    void keyPressEvent(QKeyEvent* event) override;


private slots:

    /* \brief Start the game.
     */
    void on_playButton_clicked();

    /* \brief Move the snek by a square and check for collisions.
     *
     * The game ends if a wall or the snek itself gets in the way.
     * When a food gets eaten a point is gained and the snek grows.
     */
    void moveSnake();


    void on_howButton_clicked();

    void on_scoresButton_clicked();

    void on_pauseButton_clicked();

    void on_sizeButton_clicked();

private:

    /* \brief Make the play field visible and fit it into the view.
     *
     * Should be called every time the field's size changes.
     */
    void adjustSceneArea();

    /* \brief Randomly generates a new location for the food after it has been
     * eaten.
     */
    void moveFood();


    Ui::MainWindow ui_;                     /**< Accesses the UI widgets. */
    QGraphicsRectItem* food_ = nullptr;     /**< The food item in the scene. */
    std::vector<QGraphicsRectItem*> snek_;  /**< snek in the scene. */
    QGraphicsScene scene_;                  /**< Manages drawable objects. */
    QTimer timer_;                          /**< Triggers the snek to move. */
    std::default_random_engine rng_;        /**< Randomizes food locations. */
    QPoint dir_;                            /**< Current direction of motion. */
    bool pause_state_;                      /**< Is game currently paused? */
    int points_;                            /**< Counter for eaten food. */
    int area_width_ = 20;                   /**< Current game area width. */
    int area_height_ = 20;                  /**< Current game area height. */
    int timer_value_ = 1000;                /**< Current value of timer. */
};  // class MainWindow


#endif  // PRG2_SNAKE2_MAINWINDOW_HH
