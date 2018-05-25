#include "controlpanel.h"

myscene* controlPanel::scene=NULL;
myPixmapVector* controlPanel::mpv=NULL;

controlPanel::controlPanel(QObject *par)
{
    setBackgroundBrush(mpv->panelBrush());
    for(int i=0; i<16;i++){
        cars.append(new controlCar(scene->cars[i]));
        addItem(cars[i]);
    }
}

void controlPanel::setUp()
{
    clear();
    cars.clear();
    for(int i=0; i<16;i++){
        cars.append(new controlCar(scene->cars[i]));
        addItem(cars[i]);
    }
}

