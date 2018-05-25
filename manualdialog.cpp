#include "manualdialog.h"
#include "ui_manualdialog.h"

manualDialog::manualDialog(QWidget *parent, int *seed, int *stations, int *cars, int *x, int *y, int *rt) :
    QDialog(parent),
    ui(new Ui::manualDialog)
{
    ui->setupUi(this);
    Lseed=seed;
    Lstations=stations;
    Lcars=cars;
    X=x;
    Y=y;
    reptime=rt;
}

manualDialog::~manualDialog()
{
    delete ui;
}

void manualDialog::on_startButton_clicked()
{
    *Lseed=ui->spinSeed->value();
    *Lstations=ui->spinStations->value();
    *Lcars=ui->spinCars->value();
    *X=ui->mapSideX->value();
    *Y=ui->mapSideY->value();
    *reptime=ui->timeBox->value()*10;
    started();
    this->close();
}

void manualDialog::on_GoBackButton_clicked()
{
    this->close();
}
