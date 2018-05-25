#include "myscene.h"

int base(int i){return i>0 ? i : 0;}

int floorTo(int a, int b){return a-a%b;}

float distance1(int x1, int y1, int x2, int y2){
    return sqrt(pow(x2-x1,2)+pow(y2-y1,2));
}

myPixmapVector* myscene::mpv=NULL;

myscene::myscene(QObject *par, int Seed, int MaxCars, int MaxStations, int mapx, int mapy, int reptime)
{
    minDay=1000*MaxStations;
    DAY=600*MaxStations;//1 minute for each station
    iterator=DAY+reptime-10;
    timer=NULL;
    repositionTime=reptime;
    seed= Seed==0 ? produceSeed() : Seed;
    qsrand(seed);
    mapsideX=mapx;
    mapsideY=mapy;
    matrix= new myelement**[mapsideX];
    for(int i=0; i<mapsideX; i++)
        matrix[i]=new myelement* [mapsideY];

    setSceneRect(-UNIT,-UNIT,UNIT*(mapsideX+1),UNIT*(mapsideY+1));
    P=par;
    myelement::parent=this;
    myelement::selfStop=true;
    maxCars=MaxCars;
    maxStations=MaxStations;
    rr=0;
    names=mpv->names();
    for(int a=0; a<mapsideX;a++)
        for(int b=0; b<mapsideY;b++)
            matrix[a][b]=NULL;

    euros=maxStations*MONEY;
    changeMoney();
    setBackgroundBrush(mpv->backBrush());

    rx=ry=UNIT*2;
    rect= new myelement(rx,ry);
    addItem(rect);

    setFocusItem(rect);
    for(int i=0; i<16;i++)
        cars.append(new myelement(11, 0,0, i));
    ncars=0;
    if(placeVillages()){
        deliveries=stations.count();
        timer = new QTimer(this);
        timer->start(T_SPAN);
        connect(timer, SIGNAL(timeout()), this, SLOT(routine()));
    }
    else{
        message="ERROR 01";
        changeMoney();
    }
}

void myscene::placeCar(int color)
{
    if(rx<0 || rx>=UNIT*mapsideX || ry<0 || ry>=UNIT*mapsideY) return;
    myelement* C=seekC(rx,ry);
    if(C!=NULL || ncars==maxCars) return;
    ncars++;
    cars.value(color)->exists=true;
    cars.value(color)->setPos(rx,ry);
    cars.value(color)->X=rx;
    cars.value(color)->Y=ry;
    addItem(cars.value(color));
}

void myscene::deleteCar(int color)
{
    ncars--;
    cars.value(color)->exists=false;
    cars.value(color)->payload=0;
    cars.value(color)->dest=NULL;
    removeItem(cars.value(color));
}

bool myscene::placeVillages()
{
int px, py, hx=0, hy=0;
    for(int i=0;i<maxStations; i++){
        px=3+qrand()%(mapsideX-6);
        py=3+qrand()%(mapsideY-6);
        bool allowance=true;

        int rand=qrand()%8;
        if(rand==0){hx=-2;hy=-2;}
        if(rand==1){hx=0; hy=-2;}
        if(rand==2){hx=2; hy=-2;}
        if(rand==3){hx=2; hy=0;}
        if(rand==4){hx=2; hy=2;}
        if(rand==5){hx=0; hy=2;}
        if(rand==6){hx=0; hy=-2;}
        if(rand==7){hx=-2;hy=0;}
        for(int j=0; j<stations.count(); j++){//check distance with existing stations
            int tx =stations.value(j)->X;
            int ty =stations.value(j)->Y;
            if(distance1((px+hx)*UNIT,(py+hy)*UNIT,tx,ty)<=60) allowance=false;
        }
        if(allowance){
            track = new myelement(7, (px+hx)*UNIT,(py+hy)*UNIT, 0);
            addItem(track);
            stations.append(track);
            track->letter=name();
            track->describe();
            matrix[px+hx][py+hy]=track;
        }
        for(int i=0; i<5; i++){
            for(int j=0; j<5;j++){
                hx=i-2;
                hy=j-2;
                if((hx==-2 && hy==-2)||(hx==-2 && hy==2)||(hx==2 && hy==-2)||(hx==2 && hy==2)){}
                else{
                    if(seekG((px+hx)*UNIT,(py+hy)*UNIT)==NULL){
                        track = new myelement(10,(px+hx)*UNIT,(py+hy)*UNIT, 0);
                        track->rotate((qrand()%4)*90);
                        addItem(track);
                        matrix[px+hx][py+hy]=track;
                        houses.append(track);
                    }
                }
            }
        }
    }
    if(stations.count()<=1)
        return false;

    for(int i = 0; i< stations.count() ; i++){
        int R=i;
        while(R==i)
            R=qrand()%stations.count();
        stations.value(i)->dest=stations.value(R);
        stations.value(i)->describe();
    }
    return true;
}

void myscene::place(int t)
{
    if(rx<0 || rx>=UNIT*mapsideX || ry<0 || ry>=UNIT*mapsideY) return;
    ptr=seekG(rx,ry);
    if(ptr!=NULL){
        if(ptr->type==7 || ptr->type==8)
            return;
        else
            erase();
    }
    int r= rr;
    track = new myelement(t, rx,ry, 0);
    addItem(track);
    track->rotate(0,r*90);
    track->setType(t,0);
    if(t>=0 && t <=6)
        tracks.append(track);
    matrix[rx/UNIT][ry/UNIT]=track;
    attributeStations();
    changeMoney();
}

int myscene::produceSeed()
{
    int e=QTime::currentTime().msec();
    int b=QTime::currentTime().second();
    int c=QTime::currentTime().minute();
    int d=QTime::currentTime().hour();
    return (e*b*c*d+e*1000*3600+b*3600+c*60+d)%999999999;
}

myelement *myscene::seekT(int X, int Y)
{
    if(X<0 || X>=UNIT*mapsideX || Y<0 || Y>=UNIT*mapsideY)
        return NULL;
    track=matrix[X/UNIT][Y/UNIT];
    if(track!=NULL && track->type>=0 && track->type<=6)
        return track;
    else
        return NULL;
}

myelement *myscene::seekG(int X, int Y)
{
    if(X<0 || X>=UNIT*mapsideX || Y<0 || Y>=UNIT*mapsideY)
        return NULL;
    return matrix[X/UNIT][Y/UNIT];
}

myelement *myscene::seekC(int X, int Y)
{
    for(int a=0; a<cars.count(); a++){
        if(cars.value(a)->exists && cars.value(a)->X==X && cars.value(a)->Y==Y)
            return cars.value(a);
    }
    return NULL;
}

void myscene::setSpeed(int co, int v)
{
    if(cars[co]->exists){
        cars[co]->v= mpv->resizeSpeed(cars[co]->v+v);
        cars[co]->setType(11,co);
    }
    else{
        placeCar(co);
    }
}

void myscene::moveRect(int dx, int dy)
{
        rx+=dx;
        ry+=dy;
        rect->moveBy(dx,dy);
        ptr=seekG(rx,ry);
        if(ptr!=NULL)
            qDebug()<< ptr->dest;
        update();
}

void myscene::rotatePiece()
{
    if(rx<0 || rx>=UNIT*mapsideX || ry<0 || ry>=UNIT*mapsideY) return;
    rr=(rr+1)%4;
    ptr=seekC(rx,ry);
    if(ptr!=NULL){
        ptr->rotate(90);
        return;
    }
    ptr=seekG(rx,ry);
    if(ptr==NULL || (ptr->type>=7 && ptr->type<=9))
        return;
    ptr->rotate(90);
}

void myscene::erase()
{
    if(rx<0 || rx>=UNIT*mapsideX || ry<0 || ry>=UNIT*mapsideY) return;
    if(seekG(rx,ry)==NULL && seekC(rx,ry)==NULL) return;

    matrix[rx/UNIT][ry/UNIT]=NULL;
    for(int a=0; 16; a++){
        if(cars.value(a)->exists && cars.value(a)->X==rx && cars.value(a)->Y==ry){
            euros-=CARCOST;
            changeMoney();
            deleteCar(a);
            return;
        }
    }
    for(int a=0; a<tracks.count(); a++){
        if(tracks.value(a)->X==rx && tracks.value(a)->Y==ry){
            euros-=ERASECOST/10;
            removeItem(tracks.takeAt(a));
            changeMoney();
            return;
        }
    }
    for(int a=0; a<houses.count(); a++){
        if(houses.value(a)->X==rx && houses.value(a)->Y==ry){
            euros-=ERASECOST;
            removeItem(houses.takeAt(a));
            changeMoney();
            return;
        }
    }
}

int myscene::distance(myelement *p1, myelement *p2)
{
    return sqrt(pow(p1->X-p2->X,2)+pow(p1->Y-p2->Y,2));
}

void myscene::attributeStations()
{
    if(stations.count()==0)
        return;

    int b, c, xt, yt;
    for(c=0; c<tracks.count(); c++)
        tracks[c]->dest=NULL;

    for(b=0; b<stations.count(); b++){
        xt=stations[b]->X;
        yt=stations[b]->Y;
        //assign tracks isNearStation=true
        track=seekT(xt,yt-UNIT);
        if(track!=NULL)
            track->dest=stations[b];
        track=seekT(xt+UNIT,yt);
        if(track!=NULL)
            track->dest=stations[b];
        track=seekT(xt,yt+UNIT);
        if(track!=NULL)
            track->dest=stations[b];
        track=seekT(xt-UNIT,yt);
        if(track!=NULL)
            track->dest=stations[b];
    }
}

QString myscene::name()
{
    if(names.count()==0)
        return "none";
    return names.takeAt(qrand()%names.count());
}

void myscene::increaseEuros(int m)
{
    euros+=m;
    changeMoney();
}

void myscene::updateTypes()
{
    mpv->load(skin);
    setBackgroundBrush(mpv->backBrush(skin));

    for(int a=0; a<tracks.count();a++)
        tracks[a]->setType(-1,0);
    for(int a=0; a<cars.count();a++)
        cars[a]->setType(-1,cars[a]->color);
    for(int a=0; a<stations.count();a++)
        stations[a]->setType(-1,0);
    for(int a=0; a<houses.count();a++)
        houses[a]->setType(-1,0);
}

void myscene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
        int x0=rx, y0=ry;
        rx=floorTo(base(event->scenePos().x()),UNIT);
        ry=floorTo(base(event->scenePos().y()),UNIT);
        rect->moveBy(rx-x0,ry-y0);
}

void myscene::resetSwitches(int i)
{
    if(i==0){
        for(int a=0; a<tracks.count();a++){
            if(tracks.value(a)->type==5) tracks.value(a)->setType(3,0);
            if(tracks.value(a)->type==6) tracks.value(a)->setType(4,0);
        }
    }
    else{
        for(int a=0; a<tracks.count();a++){
            if(tracks.value(a)->type==3) tracks.value(a)->setType(5,0);
            if(tracks.value(a)->type==4) tracks.value(a)->setType(6,0);
        }
    }
}

void myscene::routine()
{
    iterator++;
    if(iterator%MOVEMENT==0){
        changeMoney();
        if(deliveries==stations.count() && iterator!=DAY){
            if(iterator<DAY)
                DAY=iterator;
        }

        for(int a=0; a<16; a++)
            cars.value(a)->next();

        if(iterator==DAY+repositionTime){//set Payload
            iterator=0;
            for(int i=0; i<stations.count(); i++){
                stations.value(i)->payload=PAYLOAD+qrand()%100;
                stations.value(i)->setType(8,0);
                stations.value(i)->describe();
            }
            failures= stations.count()-deliveries;
            increaseEuros(-(CARCOST*ncars+TRACKCOST*tracks.count()+failures*PENALTY));
            deliveries=0;
            for(int i=0; i<16; i++){
                cars.value(i)->dest=NULL;
                cars.value(i)->payload=0;
            }
        }
        update();
    }
    for(int a=0; a<16; a++)
        cars.value(a)->madvance();
}

