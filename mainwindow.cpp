#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    instructions=NULL;
    grabbed=false;
    control=1;
    panel=NULL;
    scene=NULL;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    //controlling the 16 types of cars
    if(Qt::Key_Q==event->key()) scene->setSpeed(0, control);
    if(Qt::Key_W==event->key()) scene->setSpeed(1, control);
    if(Qt::Key_E==event->key()) scene->setSpeed(2, control);
    if(Qt::Key_R==event->key()) scene->setSpeed(3, control);
    if(Qt::Key_T==event->key()) scene->setSpeed(4, control);
    if(Qt::Key_Y==event->key()) scene->setSpeed(5, control);
    if(Qt::Key_U==event->key()) scene->setSpeed(6, control);
    if(Qt::Key_I==event->key()) scene->setSpeed(7, control);
    if(Qt::Key_A==event->key()) scene->setSpeed(8, control);
    if(Qt::Key_S==event->key()) scene->setSpeed(9, control);
    if(Qt::Key_D==event->key()) scene->setSpeed(10, control);
    if(Qt::Key_F==event->key()) scene->setSpeed(11, control);
    if(Qt::Key_G==event->key()) scene->setSpeed(12, control);
    if(Qt::Key_H==event->key()) scene->setSpeed(13, control);
    if(Qt::Key_J==event->key()) scene->setSpeed(14, control);
    if(Qt::Key_K==event->key()) scene->setSpeed(15, control);

    //placing tracks
    if(Qt::Key_Z==event->key()) scene->place(0);
    if(Qt::Key_X==event->key()) scene->place(1);
    if(Qt::Key_C==event->key()) scene->place(2);
    if(Qt::Key_V==event->key()) scene->place(3);
    if(Qt::Key_B==event->key()) scene->place(4);

    //resetting switches
    if(Qt::Key_Comma==event->key())
        scene->resetSwitches(0);
    if(Qt::Key_Comma==event->key() && control==-1)
        scene->resetSwitches(1);

    //moving the rectangle
    if(Qt::Key_Up==event->key())    scene->moveRect(0,-UNIT);
    if(Qt::Key_Down==event->key())  scene->moveRect(0,UNIT);
    if(Qt::Key_Right==event->key()) scene->moveRect(UNIT,0);
    if(Qt::Key_Left==event->key())  scene->moveRect(-UNIT,0);

    //delete
    if(Qt::Key_Delete==event->key())
        scene->erase();

    //timer start/stop
    if(Qt::Key_Alt==event->key() && scene!=NULL && scene->timer!=NULL){
        if(isTimerActive){
            scene->timer->stop();
            isTimerActive=false;
        }
        else{
            scene->timer->start();
            isTimerActive=true;
        }
    }
    //release keyboard
    if(Qt::Key_Space==event->key()){
        releaseKeyboard();
        grabbed=false;
        ui->grabButton->setText("Grab Keys");
    }
    //controls on speed and rotation
    if(Qt::Key_Control==event->key()) control=-1;
    if(Qt::Key_Shift==event->key()) scene->rotatePiece();
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(Qt::Key_Control==event->key()) control=1;
}

void MainWindow::write()
{
    if(scene->message.count()!=0)
        ui->lineEdit->setText(scene->message);

    if(scene->euros<-1000){
        ui->moneyLabel->setText("GAME OVER");
        scene->euros=-100000;
    }
    else{
        S.setNum(scene->euros);
        ui->moneyLabel->setText(S + " €");
    }
    panel->update();
    float it=scene->iterator, d=scene->DAY+reptime,ri=(it/d)*100;
    ui->progressBar->setValue(ri);
    ui->progressBar->update();
    time=scene->DAY/10;
    S.setNum(time);

    ui->label->setText("Time: "+S+"+"+Ss+" sec");
}

void MainWindow::start()
{
    mpv.load(0);
    myelement::selfStop=true;
    Ss.setNum(reptime/10);
    if(scene!=NULL && panel!=NULL){
        for(int i=0; i<16; i++)
            delete scene->cars.value(i);
        if(scene->timer!=NULL)
            scene->timer->stop();
        scene->clear();
        for(int i=0 ; i<scene->mapsideY ; i++ )
            delete [] scene->matrix[i];
        delete [] scene->matrix;
        delete scene->timer;
        delete scene;
        panel->clear();
        delete panel;
    }
    controlPanel::mpv =&mpv;
    myscene::mpv      =&mpv;
    controlCar::mpv   =&mpv;
    myelement::mpv    =&mpv;

    scene = new myscene(this, seed, cars, stations, X, Y, reptime);
    ui->graphicsView->setScene(scene);
    isTimerActive=true;
    ui->graphicsView->ensureVisible(scene->rect);
    controlCar::scene=scene;
    controlPanel::scene=scene;
    panel= new controlPanel(this);
    ui->graphicsView_2->setScene(panel);

    write();
    connect(scene, SIGNAL(changeMoney()), this, SLOT(write()));
    if(scene==NULL) return;
    S.setNum(scene->seed);
    ui->lineEdit->setText(S);
}

void MainWindow::on_grabButton_clicked()
{
    if(grabbed){
        releaseKeyboard();
        grabbed=false;
        ui->grabButton->setText("Grab Keys");
    }
    else{
        grabKeyboard();
        grabbed=true;
        ui->grabButton->setText("Release Keys");
    }
}

void MainWindow::on_checkBox_stateChanged()
{
    myelement::selfStop = !myelement::selfStop;
}

void MainWindow::on_manualButton_clicked()
{
    if(instructions==NULL)
        instructions = new manualDialog(this, &seed, &stations, &cars, &X, &Y, &reptime);
    instructions->showMaximized();
    instructions->setPalette(this->palette());

    connect(instructions, SIGNAL(started()), this, SLOT(start()));
}

void MainWindow::on_pushButton_clicked()
{
    if(scene!=NULL)
        scene->iterator=scene->DAY+scene->repositionTime-scene->iterator%10-10;
}
