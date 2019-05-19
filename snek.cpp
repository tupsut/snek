#include "snek.hh"

#include <QBrush>
#include <QPen>

Snek::Snek(QObject *parent, QGraphicsScene *scene, int area_width, int area_height) : QObject(parent), scene_(scene), area_width_(area_width), area_height_(area_height)
{
    const QBrush snek_brush(QColor("#256B24"));
    QGraphicsRectItem* head = scene->addRect(QRect(0, 0, 1, 1), QPen(Qt::white, 0), snek_brush);
    elements_.push_back(head);
    head->setPos(area_width / 2, area_height / 2);
    // head should always be visible over a new tail segment so it has higher Z
    head->setZValue(1);
}

void Snek::propagate_tail()
{
    auto it = elements_.rbegin();
    for (; it != elements_.rend() - 1; ++it) {
        auto elem = *it;
        auto next = *(it + 1);
        elem->setPos(next->pos());
    }
}

void Snek::move_head(QPoint direction)
{
    auto head = elements_.front();
    const QPointF old_head_pos = head->scenePos();
    const QPointF new_head_pos = old_head_pos + direction;
    head->setPos(new_head_pos);

    // continuous playfield; out of bounds -> head moves to opposite side
    if (head->x() > area_width_-1) head->setPos(0, new_head_pos.y());
    if (head->x() < 0) head->setPos(area_width_-1, new_head_pos.y());
    if (head->y() > area_height_-1) head->setPos(new_head_pos.x(), 0);
    if (head->y() < 0) head->setPos(new_head_pos.x(), area_height_-1);
}

QPointF Snek::head_position() const
{
    return elements_.front()->pos();
}

void Snek::extend()
{
    const QRectF rect(0, 0, 1, 1);
    // TODO pretty colours
    const QBrush snek_brush(QColor("#253B24"));
    QGraphicsRectItem* body = scene_->addRect(rect, QPen(Qt::white, 0), snek_brush);
    body->setPos(this->head_position());
    elements_.push_back(body);
}

bool Snek::is_occupied(QPointF point) const
{
    for (auto elem : elements_) {
        if (elem->pos() == point) {
            return true;
        }
    }
    return false;
}
