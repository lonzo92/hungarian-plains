#include "controlcar.h"

myPixmapVector* controlCar::mpv=NULL;
myscene* controlCar::scene=NULL;

controlCar::controlCar(myelement *O)
{
    origin=O;
    X=0;
    Y=origin->color*60;
    setPos(mapToParent(X,Y));
    setFlag(QGraphicsItem::ItemIsSelectable,true);
    nextSW=nextST=NULL;
    pen.setColor(Qt::black);
    font.setUnderline(false);
    font.setBold(true);
}

QRectF controlCar::boundingRect() const
{
    return QRectF(0,0,6*UNIT,3*UNIT);
}

void controlCar::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    set();
    painter->drawPixmap(0,0,CARIW*2,CARIH*2,origin->icon);
    painter->drawPixmap(CARIW*2,0,90,30,iconLoad);
    if(origin->dest!=NULL)
    {
        QString S;
        S.setNum(origin->payload);
        painter->drawPixmap(CARIW*2,30,UNIT,UNIT,origin->dest->icon);
        painter->setPen(pen);
        painter->setFont(font);
        painter->drawText(QRect(CARIW*2+30,30, origin->dest->letter.length()*UNIT/2, UNIT/2), Qt::AlignLeft, origin->dest->letter+" "+S+"€");
    }
    if(nextSW!=NULL)
    {
        painter->drawPixmap(CARIW*2,0,UNIT,UNIT,nextSW->icon);
    }
    if(nextST!=NULL)
    {
        painter->drawPixmap(CARIW*2+UNIT,0,UNIT,UNIT,nextST->icon);
        painter->setPen(pen);
        painter->setFont(font);
        painter->drawText(QRect(-UNIT/2,-UNIT, nextST->letter.length()*UNIT/2, UNIT/2), Qt::AlignLeft, nextST->letter);
    }
}

void controlCar::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF pos;
    int v=0;
    pos=event->pos();
    if((pos.x()>=0 && pos.x()<=CARIW*2)&&(pos.y()>=0 && pos.y()<=CARIH*2)){
        if(event->button()==Qt::RightButton)v=-1;
        if(event->button()==Qt::LeftButton)v= +1;
        if(origin->exists){
            origin->v= mpv->resizeSpeed(origin->v+v);
            origin->setType(11,origin->color);
        }
        else{
            scene->placeCar(origin->color);
        }
    }
}


void controlCar::set()
{
    int b=0;
    if(!origin->exists) b=0;
    else if(origin->exists && origin->payload==0) b=1;
    else if(origin->exists && origin->payload>0)  b=2;
    iconLoad=mpv->latCarIcon[b];
}

