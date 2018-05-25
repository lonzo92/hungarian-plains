#ifndef MYELEMENT_H
#define MYELEMENT_H
#include <QtCore>
#include <QtGui>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QPixmap>
#include <QGraphicsView>
#include <QColor>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <QGraphicsRectItem>
#include "mypixmapvector.h"

#include <QDebug>


#define CARIX -6
#define CARIY -14
#define CARIW 12
#define CARIH 28
#define PI 3.14159265
#define T_SPAN 100 //milliseconds
#define MOVEMENTS 10.0
#define MOVEMENT 10
#define HOUSES 16

class myelement : public QGraphicsItem
{
public:
    myelement(int t, int x, int y, int col);
    myelement(int x0, int y0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void setType(int t, int col);
    QString describe();
    void madvance();
    void rotate(int R, int tr=0);
    void next();
    myelement* nextSwitch();
    myelement* nextStation();

    int link[4];
    bool exists;
    QString letter;
    static bool selfStop;
    static myPixmapVector* mpv;
    static QObject *parent;
    myelement *ptr, *ptr1, *dest;
    int X, Y, type, r, r0, color, v,dxl, dyl, drl, houses, payload;
    QPixmap icon;
    QBrush brush;
    QFont font;
    QPen pen;
};

#endif // MYELEMENT_H
