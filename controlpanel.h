#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H
#include "controlcar.h"

class controlPanel : public QGraphicsScene
{
public:
    controlPanel(QObject *par);
    void setUp();

    static myscene* scene;
    static myPixmapVector* mpv;
    QList<controlCar*> cars;
};

#endif // CONTROLPANEL_H
