#ifndef MYPIXMAPVECTOR_H
#define MYPIXMAPVECTOR_H
#include <QtCore>
#include <QPixmap>
#include <QPainter>

#define UNIT 30

class myPixmapVector
{
public:
    QList<QPixmap> icons, caricons, latCarIcon;
    QPixmap *t, *c;
    QChar letters[16];

    void load(int min);
    QPixmap house();
    QStringList names();
    QBrush backBrush(int skin=0);
    QBrush panelBrush();
    int resizeSpeed(int c);
};

#endif // MYPIXMAPVECTOR_H
