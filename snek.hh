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

private:
    std::vector<QGraphicsRectItem*> elements_;  /**< snek in the scene. */
    QGraphicsScene *scene_;                     /**< ptr to mainwindow scene. */
    int area_width_;                            /**< Current game area width. */
    int area_height_;                           /**< Current game area height. */
};

#endif // SNEK_HH
