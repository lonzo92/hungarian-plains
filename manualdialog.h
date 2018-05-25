#ifndef MANUALDIALOG_H
#define MANUALDIALOG_H

#include <QDialog>

namespace Ui {
class manualDialog;
}

class manualDialog : public QDialog
{
    Q_OBJECT

public:
    explicit manualDialog(QWidget *parent = 0, int *seed=NULL, int *stations=NULL, int *cars=NULL, int *x=NULL, int *y=NULL, int *rt=NULL);
    ~manualDialog();
    int *Lseed, *Lstations, *Lcars, *X, *Y, *reptime;

signals:
    void started();

private slots:
    void on_startButton_clicked();

    void on_GoBackButton_clicked();

private:
    Ui::manualDialog *ui;
};

#endif // MANUALDIALOG_H
