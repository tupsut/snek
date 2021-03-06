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
# File: snek.hh                                                    #
# Description: Declares a class implementing the snek entity.      #
#                                                                  #
# Author: Saskia Simisker, 282598, saskia.simisker@tuni.fi         #
####################################################################
*/

#ifndef SNEK_HH
#define SNEK_HH

#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsScene>

class Snek : public QObject
{
    Q_OBJECT

public:

    /* \brief Construct a Snek.
     *
     * \param[in] parent The parent widget of the object.
     */
    explicit Snek(QObject *parent, QGraphicsScene *scene, int area_width,
                  int area_height);

    /* \brief Destruct the Snek.
     */
    ~Snek();

    /* \brief Update the locations of snek segments other than the head.
     */
    void propagate_tail();

    /* \brief Update the location of snek head based on player input.
     *
     * \param[in] direction Directional QPoint to be added to current location.
     */
    void move_head(QPoint direction);

    /* \brief Return the current location of the snek's head.
     */
    QPointF head_position() const;

    /* \brief Add a new segment to the snek.
     */
    void extend();

    /* \brief Returns a bool stating whether the given position is occupied by
     * the snek.
     *
     * \param[in] point QPointF to be checked.
     */
    bool is_occupied(QPointF point) const;

    /* \brief Returns a bool stating whether the head of the snek has collided
     * with another segment of the body.
     */
    bool is_collision() const;

    /* \brief Checks whether the snek fills all of the screen, except for the
     * location of the food element.
     *
     * \param[in] food_pos Position of the food element.
     */
    bool fills_screen() const;

private:
    std::vector<QGraphicsRectItem*> elements_;  /**< snek parts in the scene. */
    QGraphicsScene *scene_;                     /**< ptr to mainwindow scene. */
    const int area_width_;                      /**< Game area width. */
    const int area_height_;                     /**< Game area height. */
};

#endif // SNEK_HH
