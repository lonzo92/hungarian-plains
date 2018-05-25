#ifndef MYSCENE_H
#define MYSCENE_H
#include "myelement.h"
#define CARCOST 200
#define TRACKCOST 10
#define PAYLOAD 500
#define PENALTY 250
#define ERASECOST 500
#define MONEY 750 //each station
#define MINDISTANCE 5


class myscene : public QGraphicsScene
{
    Q_OBJECT
public:
    myscene(QObject *par, int Seed, int MaxCars, int MaxStations, int mapx, int mapy, int reptime);
    void placeCar(int color);
    void deleteCar(int color);
    bool placeVillages();
    void place(int t);
    int produceSeed();
    myelement *seekT(int X, int Y);
    myelement *seekG(int X, int Y);
    myelement *seekC(int X, int Y);
    void setSpeed(int co, int v);
    void moveRect(int dx, int dy);
    void rotatePiece();
    void erase();
    int distance(myelement* p1, myelement *p2);
    void attributeStations();
    QString name();
    void increaseEuros(int m);
    void updateTypes();
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void resetSwitches(int i);

    static myPixmapVector *mpv;
    myelement*** matrix;
    QObject *P;
    QStringList names;
    QString message;
    QTimer *timer;
    int  rx, ry, rr, DAY,failures, deliveries, euros,mapsideX, mapsideY, iterator,
    repositionTime, skin, ncars, seed, maxCars, maxStations, minDay;
    myelement *track, *car, *rect, *ptr, *station, *house;
    QList<myelement*> tracks, cars, stations, houses;

signals:
    void changeMoney();
private slots:
    void routine();
};

#endif // MYSCENE_H
