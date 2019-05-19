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
# File: snek.cpp                                                   #
# Description: Defines a class implementing the snek entity.       #
#                                                                  #
# Author: Saskia Simisker, 282598, saskia.simisker@tuni.fi         #
####################################################################
*/

#include "snek.hh"

#include <QBrush>
#include <QPen>

Snek::Snek(QObject *parent, QGraphicsScene *scene, int area_width, int area_height) : QObject(parent), scene_(scene), area_width_(area_width), area_height_(area_height)
{
    const QBrush snek_brush(QColor("#256B24"));
    QGraphicsRectItem* head = scene->addRect(QRect(0, 0, 1, 1),
                                             QPen(Qt::white, 0), snek_brush);
    elements_.push_back(head);
    head->setPos(area_width / 2, area_height / 2);
    // head should always be visible over a new tail segment so it has higher Z
    head->setZValue(1);
}

Snek::~Snek()
{
    for (auto &elem : elements_)
        delete elem;
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

bool Snek::is_collision() const
{
    auto head_position = this->head_position();
    auto it = elements_.begin() + 1;
    for (; it != elements_.end(); ++it) {
        if (head_position == (*it)->pos()) return true;
    }
    return false;
}

bool Snek::fills_screen() const
{
    for (qreal x = 0; x < area_width_; x += 1) {
        for (qreal y = 0; y < area_height_; y += 1) {
            QPointF here = QPointF(x, y);
            if (!is_occupied(here)) return false;
        }
    }
    return true;
}
