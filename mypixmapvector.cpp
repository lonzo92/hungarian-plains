#include "mypixmapvector.h"

void myPixmapVector::load(int min)
{
    icons.clear();
    caricons.clear();
    latCarIcon.clear();

    letters[0]='Q';
    letters[1]='W';
    letters[2]='E';
    letters[3]='R';
    letters[4]='T';
    letters[5]='Y';
    letters[6]='U';
    letters[7]='I';
    letters[8]='A';
    letters[9]='S';
    letters[10]='D';
    letters[11]='F';
    letters[12]='G';
    letters[13]='H';
    letters[14]='J';
    letters[15]='K';

    QPixmap A, B;
    A.load(":/trainIcons/infrastructures.png");
    for(int i=0; i<26; i++){
        B=A.copy(i*30, 30*min, 30,30);
        icons.append(B);
    }

    A.load(":/trainIcons/cars.png");
    for(int i=0; i<16; i++){
        B=A.copy(12*i, 28*0, 12, 28);
        caricons.append(B);
        B=A.copy(12*i, 28*1, 12, 28);
        caricons.append(B);
        B=A.copy(12*i, 28*2, 12, 28);
        caricons.append(B);
    }

    A.load(":/trainIcons/carL.png");
    for(int i=0; i<3; i++){
        B=A.copy(0, 30*i, 90,30);
        latCarIcon.append(B);
    }
}

QPixmap myPixmapVector::house()
{
    return icons.value(qrand()%16+10);
}

QStringList myPixmapVector::names()
{
    QStringList N;
    QFile file(":/trainIcons/names");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return N;

    QString readout;
    while(!file.atEnd()){
        readout= file.readLine();
        readout.chop(1);
        N.append(readout);
    }
    return N;
}

QBrush myPixmapVector::backBrush(int skin)
{
    load(skin);
    QImage p;
    p.load(":/trainIcons/infrastructures.png");
    QColor col=p.pixel(0,skin*UNIT);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(col);
    return brush;
}

QBrush myPixmapVector::panelBrush()
{
    QImage p;
    p.load(":/trainIcons/carL.png");
    QColor col=p.pixel(0,0);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(col);
    return brush;
}

int myPixmapVector::resizeSpeed(int c)
{
    if(c<-1) return -1;
    if(c>+1) return +1;
    return c;
}
