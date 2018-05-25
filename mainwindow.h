#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "controlpanel.h"
#include <QEvent>
#include "manualdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    controlPanel *panel;
    myscene *scene;
    QString S, Ss;
    int control;
    bool isTimerActive, grabbed;
    myPixmapVector mpv;
    manualDialog *instructions;
    int seed, cars, stations, X, Y, reptime;
    float time;
public slots:
    void keyPressEvent(QKeyEvent *event);

    void keyReleaseEvent(QKeyEvent *event);

    void write();

    void start();

private slots:
    void on_grabButton_clicked();

    void on_checkBox_stateChanged();

    void on_manualButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
