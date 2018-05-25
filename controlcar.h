#ifndef CONTROLCAR_H
#define CONTROLCAR_H
#include "myscene.h"

class controlCar : public QGraphicsItem
{
public:
    controlCar(myelement *O);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void set();

    static myPixmapVector* mpv;
    static myscene *scene;
    int X, Y;
    myelement *origin, *nextSW, *nextST;
    QPixmap iconLoad;

    QFont font;
    QPen pen;
};

#endif // CONTROLCAR_H
