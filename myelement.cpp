#include "myelement.h"
#include "myscene.h"

int lx(int out){return (out%2==0 ? out==0 ? 0 : 0 : out==1 ? 1: -1)*UNIT;}

int ly(int out){return (out%2==0 ? out==0 ? -1 : 1 : out==1 ? 0: 0)*UNIT;}

float factor=1/MOVEMENTS;

bool myelement::selfStop=true;
myPixmapVector* myelement::mpv=NULL;
QObject* myelement::parent;

myelement::myelement(int t, int x, int y, int col)
{//standard constructor
    setPos(mapToParent(x,y));
    X=x;
    Y=y;
    r=r0=dxl=dyl=drl=v=payload=0; exists=true;
    setFlag(QGraphicsItem::ItemIsSelectable,true);
    pen.setColor(Qt::white);
    font.setUnderline(false);
    font.setBold(true);
    if(t==11) exists=false;
    setType(t, col);
    dest=NULL;
}

myelement::myelement(int x0, int y0)
{//cursor rectangle
    type=-1;
    setPos(mapToParent(x0,y0));
    brush.setStyle(Qt::Dense4Pattern);
    brush.setColor(Qt::darkBlue);
    setZValue(4);
}

QRectF myelement::boundingRect() const
{
    if(type!=11) return QRectF(-UNIT/2,-UNIT/2,UNIT,UNIT);
    else return QRectF(CARIX,CARIY,CARIW,CARIH);
}

void myelement::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(type==-1){
        painter->setBrush(brush);
        painter->drawRect(-UNIT/2,-UNIT/2,UNIT,UNIT);
        return;
    }
    if(type!=11)
    {
        painter->drawPixmap(-UNIT/2,-UNIT/2,UNIT,UNIT,icon);
        if(type>=7 && type<=9){
            painter->setPen(pen);
            painter->setFont(font);
            painter->drawText(QRect(-UNIT/2,-UNIT, letter.length()*UNIT/2, UNIT/2), Qt::AlignLeft, letter);
        }
    }
    else
        painter->drawPixmap(CARIX,CARIY,CARIW,CARIH,icon);
}

void myelement::mousePressEvent(QGraphicsSceneMouseEvent *event)
{//change type for switches
    switch(type){
    case 3: setType(5,0); break;
    case 5: setType(3,0); break;
    case 4: setType(6,0); break;
    case 6: setType(4,0); break;
    }
    QGraphicsItem::mousePressEvent(event);
}

void myelement::setType(int t, int col)
{
    link[0]=-1;         link[1]=-1;        link[2]=-1;         link[3]=-1;
    if(t!=-1)
        type=t;

    setZValue(1);
    icon=mpv->icons[type];
    switch (type){
    case 0:// straight
        if(r==0  || r==180){link[0]=2;         link[1]=-1;        link[2]=0;         link[3]=-1;}
        if(r==90 || r==270){link[0]=-1;        link[1]=3;         link[2]=-1;        link[3]=1;}
        break;
    case 1:// curve
        if(r==0  ){link[0]=-1;        link[1]=2;         link[2]=1;         link[3]=-1;}
        if(r==90 ){link[0]=-1;        link[1]=-1;        link[2]=3;         link[3]=2;}
        if(r==180){link[0]=3;         link[1]=-1;        link[2]=-1;        link[3]=0;}
        if(r==270){link[0]=1;         link[1]=0;         link[2]=-1;        link[3]=-1;}
        break;
    case 2:// cross
        link[0]=2;        link[1]=3;        link[2]=0;        link[3]=1;
        break;
    case 3:// switch 2 3 0 1
        if(r==0  ){link[0]=2;         link[1]=2;         link[2]=0;         link[3]=-1;}
        if(r==90 ){link[0]=-1;        link[1]=3;         link[2]=3;         link[3]=1;}
        if(r==180){link[0]=2;         link[1]=-1;        link[2]=0;         link[3]=0;}
        if(r==270){link[0]=1;         link[1]=3;         link[2]=-1;        link[3]=1;}
        break;
    case 4:// switch 2 3 0 1
        if(r==0  ){link[0]=2;         link[1]=-1;        link[2]=0;         link[3]=2;}
        if(r==90 ){link[0]=3;         link[1]=3;         link[2]=-1;        link[3]=1;}
        if(r==180){link[0]=2;         link[1]=0;         link[2]=0;         link[3]=-1;}
        if(r==270){link[0]=-1;        link[1]=3;         link[2]=1;         link[3]=1;}
        break;
    case 5:// switch 2 3 0 1
        if(r==0  ){link[0]=2;         link[1]=2;         link[2]=1;         link[3]=-1;}
        if(r==90 ){link[0]=-1;        link[1]=3;         link[2]=3;         link[3]=2;}
        if(r==180){link[0]=3;         link[1]=-1;        link[2]=0;         link[3]=0;}
        if(r==270){link[0]=1;         link[1]=0;         link[2]=-1;        link[3]=1;}
        break;
    case 6:// switch
        if(r==0  ){link[0]=2;         link[1]=-1;        link[2]=3;         link[3]=2;}
        if(r==90 ){link[0]=3;         link[1]=3;         link[2]=-1;        link[3]=0;}
        if(r==180){link[0]=1;         link[1]=0;         link[2]=0;         link[3]=-1;}
        if(r==270){link[0]=-1;        link[1]=2;         link[2]=1;         link[3]=1;}
        break;
    case 7:// emtpy station
        setZValue(2);
        payload=0;
        break;
    case 10:
        icon=mpv->house();
        break;
    case 11:
        color=col%16;
        letter=mpv->letters[color];
        icon=mpv->caricons.value(color*3+v+1);
        setZValue(3);
        break;
    default: // cargo and passengers stations
        setZValue(2);
    }
    update();
}

QString myelement::describe()
{
    QString S;
    if(!exists) return "emtpy";
    QTextStream stream(&S);
    if(type==11){
        stream<<letter;
        if(payload>0 && !(dest==NULL))
            stream << " to " << dest->letter;
    }
    if((type==7 || type==8) && dest!=NULL)
        stream << "to " << dest->letter;
    setToolTip(S);
    return S;
}

void myelement::madvance()
{
    if(!exists) return;
    setRotation(r0+drl);
    r0+=drl;
    moveBy(dxl,dyl);
}

void myelement::rotate(int R, int tr)
{
    r= tr==0 ? (r+R)%360: tr%360; r0=r;
    setRotation(r);
    setType(type,color);
    if(type==11){
        dest=NULL;
        payload=0;
    }
}

void myelement::next()
{
    if(!exists) return;
    setPos(X,Y);
    int x=0, y=0;
    r0=r; dxl=dyl=drl=0;
    myscene *reference = static_cast<myscene*> (parent);
    ptr = reference->seekT(X,Y);
    if(ptr==NULL) return;

    if((selfStop && ptr->dest!=NULL)&&(dest==ptr->dest || (payload==0 && ptr->dest->payload>0))){
        v=0;
        reference->changeMoney();
        setType(type,color);
    }
    int in, out;
    if(v==0){
        if(ptr->dest!=NULL && ptr->dest==dest){//the car is near its destination
            reference->increaseEuros(payload);
            reference->deliveries++;
            payload=0;
            dest=NULL;
            describe();
            return;
        }
        if((ptr->dest!=NULL && ptr->dest->payload>0) && (payload<=0 && dest==NULL)){
            payload=ptr->dest->payload;
            dest=ptr->dest->dest;
            describe();
            ptr->dest->setType(7,0);
            dest->describe();
            dest->update();
            return;
        }
        return;
    }
    in = v>0 ? (r/90+2)%4 : r/90;

    out=ptr->link[in]>=0 ? ptr->link[in] : (in+2)%4;

    x=lx(out);
    y=ly(out);
    ptr1 = reference->seekT(X+x,Y+y);
    if (ptr1==NULL || ptr1->link[(out+2)%4]==-1) return;

    r= v>=0 ? (out%4)*90 : ((out+2)%4)*90;

    if(reference->seekC(x+X,y+Y)!=NULL){
        r=r0;
        return;
    }
    dxl=x*factor;
    dyl=y*factor;
    drl=r-r0;

    if(drl== 270) drl=-90;
    if(drl==-270) drl= 90;

    drl=drl*factor;
    X+=x;
    Y+=y;
}

myelement *myelement::nextSwitch()
{
    if(!exists || v==0) return NULL;
    int x=0, y=0, tx=X, ty=Y, in, out=r/90;
    myscene *reference = static_cast<myscene*> (parent);
    ptr = reference->seekT(tx,ty);
    if(ptr==NULL) return NULL;
    in = v>0 ? (out+2)%4 : out;
    for(int a=0; a<30; a++){//checks 30 tiles in the future
        in = (out+2)%4;
        out=ptr->link[in]>=0 ? ptr->link[in] : (in+2)%4;

        x=lx(out);
        y=ly(out);
        ptr = reference->seekT(tx+x,ty+y);
        if (ptr==NULL || ptr->link[(out+2)%4]==-1) return NULL;

        tx+=x;
        ty+=y;
    }
    return NULL;
}
