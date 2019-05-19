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

#include "snek.hh"
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
    ~MainWindow() override;

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
     * The game ends if the snek gets in its own way.
     * When a food gets eaten a point is gained and the snek grows.
     */
    void moveSnake();

    /* \brief Show the in-game instructions.
     */
    void on_howButton_clicked();

    /* \brief Show the high scores table.
     */
    void on_scoresButton_clicked();

    /* \brief Pause or resume the game.
     */
    void on_pauseButton_clicked();

    /* \brief Clean-up and restart the game.
     */
    void on_restartButton_clicked();

    /* \brief Adjust the game area.
     */
    void on_sizeButton_clicked();

    /* \brief Update the timer counting how long the game has taken.
     */
    void on_gameSecondElapsed();

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

    /* \brief Handles game's end state.
     *
     * param[in] is_win Whether the game was won or lost.
     */
    void gameEnd(bool is_win);


    Ui::MainWindow ui_;                     /**< Accesses the UI widgets. */
    QGraphicsRectItem* food_ = nullptr;     /**< The food item in the scene. */
    Snek *snek_;                            /**< Contains all snek parts. */
    QGraphicsScene scene_;                  /**< Manages drawable objects. */
    QTimer timer_;                          /**< Triggers the snek to move. */
    QTimer game_timer_;                     /**< Timer for counting time. */
    std::default_random_engine rng_;        /**< Randomizes food locations. */
    QPoint dir_;                            /**< Current direction of motion. */
    bool pause_state_ = false;              /**< Is game currently paused? */
    int points_ = 0;                        /**< Counter for eaten food. */
    int area_width_ = 20;                   /**< Current game area width. */
    int area_height_ = 20;                  /**< Current game area height. */
    int init_timer_value_ = 800;            /**< Default interval of timer. */
    int timer_value_ = init_timer_value_;   /**< Current interval of timer. */
    int timer_min_ = 150;                   /**< Minimum interval of timer. */
    int game_time_elapsed_ = 0;             /**< Counts the time elapsed. */
};  // class MainWindow


#endif  // PRG2_SNAKE2_MAINWINDOW_HH
