#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "modelElBuggy.h"


modelElBuggy elBg = modelElBuggy();

void printStates(){

    qDebug("ON Btn : %d\n",elBg.onBtn);
    qDebug("OFF Btn : %d\n",elBg.offBtn);
    qDebug("Smjer Naprijed Btn : %d\n",elBg.smjerNaprijedBtn);
    qDebug("Smjer Nazad Btn : %d\n",elBg.smjerNazadBtn);
    qDebug("Dial Ubrzanje : %f\n",elBg.dialUbrzanje);
    qDebug("Dial Kocenje : %f\n",elBg.dialKocenje);

}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->progressBarUbrzanje->setValue(0);
    ui->progressBarKocenje->setValue(0);




    ui->statusCode->setText("<font color='red'>Elektricni buggy je na stanju OFF!</font>");
    ui->statusbar->showMessage("UKLJUCITE MOTORE..");
    if (elBg.onBtn == false){
        ui->dialKocenje->setDisabled(true);
        ui->ubrzanjeDial->setDisabled(true);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ubrzanjeDial_valueChanged(int value)
{
    if (elBg.onBtn == true ){
        if((elBg.smjerNaprijedBtn || elBg.smjerNazadBtn) == true){
    ui->progressBarUbrzanje->setValue(value);
    ui->progressBarKocenje->setValue(0);
    ui->kocenjeLcd->display(0);
    ui->dialKocenje->setValue(0);
    ui->progressBarUbrzanje->setHidden(false);
    ui->progressBarKocenje->setHidden(true);
    elBg.dialKocenje = 0;
    ui->ubrzanjeLcd->display(value);
        }
    }
}

void MainWindow::on_startBtn_clicked()
{
    if(elBg.onBtn == false && elBg.offBtn == false){
    ui->statusCode->setText("<font color='green'>Elektricni buggy je na stanju ON...</font>");
    ui->statusbar->showMessage("ODABERITE SMIJER..");
         elBg.onBtn = true;
         ui->progressBarUbrzanje->setValue(0);
         ui->progressBarKocenje->setValue(0);
         ui->ubrzanjeDial->setValue(0);
         ui->dialKocenje->setValue(0);
         printStates();
    }

}


void MainWindow::on_stopBtn_clicked()
{
    if (elBg.onBtn == true){
    ui->statusCode->setText("<font color='red'>Elektricni buggy je na stanju OFF!</font>");
     ui->statusbar->showMessage("UKLJUCITE MOTORE..");
         elBg.onBtn = false;
         elBg.offBtn = true;
         elBg.setModelElBuggyParameters(0,0,0,0,0,0,0,0,0,0);
         ui->progressBarUbrzanje->setValue(0);
         ui->progressBarKocenje->setValue(0);
         ui->kocenjeLcd->display(0);
         ui->ubrzanjeLcd->display(0);
         ui->ubrzanjeDial->setValue(0);
         ui->dialKocenje->setValue(0);
         ui->dialKocenje->setDisabled(true);
         ui->ubrzanjeDial->setDisabled(true);
         ui->progressBarUbrzanje->setHidden(true);
         ui->progressBarKocenje->setHidden(true);
         printStates();
         }
}


void MainWindow::on_nazadBtn_clicked()
{
    if (elBg.onBtn == true){
    if (elBg.smjerNaprijedBtn == false && elBg.smjerNazadBtn == false){
    ui->statusCode->setText("<font color='green'>Elektricni buggy je na stanju NAZAD...</font>");
        qDebug("Smjer Nazad button");
        ui->statusbar->showMessage(" ");
        elBg.smjerNaprijedBtn = false;
        elBg.smjerNazadBtn = true;
        ui->dialKocenje->setDisabled(false);
        ui->ubrzanjeDial->setDisabled(false);
        printStates();
    } else {
       ui->statusbar->showMessage("ZAUSTAVITI MOTORE, PA PRITISNITE SMIJER NAZAD");
     }
    }
}


void MainWindow::on_progressBarUbrzanje_valueChanged(int value)
{
    if (elBg.onBtn == true){
    ui->statusCode->setText("<font color='green'>Elektricni buggy je u stanju UBRZAVANJA...</font>");
        elBg.dialUbrzanje = value;
        elBg.dialKocenje = 0;
        qDebug("%.0lf",elBg.dialUbrzanje);
        }
}


void MainWindow::on_progressBarKocenje_valueChanged(int value)
{
    if (elBg.onBtn == true){
    ui->statusCode->setText("<font color='green'>Elektricni buggy je u stanju KOCENJA...</font>");
        elBg.dialKocenje = value;
        elBg.dialUbrzanje = 0;
        qDebug("%.0lf",elBg.dialKocenje);
        }
}


void MainWindow::on_naprijedBtn_clicked()
{
    if (elBg.onBtn == true){
    if (elBg.smjerNaprijedBtn == false && elBg.smjerNazadBtn == false){
    ui->statusCode->setText("<font color='green'>Elektricni buggy je na stanju NAPRIJED...</font>");
       qDebug("Smjer Naprijed button");
    ui->statusbar->showMessage(" ");
       elBg.smjerNaprijedBtn = true;
       elBg.smjerNazadBtn = false;
       ui->dialKocenje->setDisabled(false);
       ui->ubrzanjeDial->setDisabled(false);
       printStates();
    } else {
        ui->statusbar->showMessage("ZAUSTAVITI MOTORE, PA PRITISNITE SMIJER NAPRIJED");
     }
    }
}


void MainWindow::on_zaustaviBtn_clicked()
{
    if (elBg.onBtn == true){
    qDebug("Zaustavi button");
    ui->statusbar->showMessage(" ");
    elBg.smjerNaprijedBtn = false;
    elBg.smjerNazadBtn = false;
    ui->progressBarUbrzanje->setValue(0);
    ui->progressBarKocenje->setValue(0);
    ui->ubrzanjeDial->setValue(0);
    ui->dialKocenje->setValue(0);
    ui->kocenjeLcd->display(0);
    ui->ubrzanjeLcd->display(0);
    ui->dialKocenje->setDisabled(true);
    ui->ubrzanjeDial->setDisabled(true);
    ui->progressBarUbrzanje->setHidden(true);
    ui->progressBarKocenje->setHidden(true);
    ui->statusCode->setText("<font color='green'>Elektricni buggy je na stanju ZAUSTAVI...</font>");
    printStates();
    }
}


void MainWindow::on_dialKocenje_valueChanged(int value)
{
    if (elBg.onBtn == true){
    if((elBg.smjerNaprijedBtn || elBg.smjerNazadBtn) == true){
    ui->progressBarKocenje->setValue(value);
    ui->progressBarUbrzanje->setValue(0);
    ui->ubrzanjeLcd->display(0);
    ui->ubrzanjeDial->setValue(0);
    ui->progressBarUbrzanje->setHidden(true);
    ui->progressBarKocenje->setHidden(false);
    elBg.dialUbrzanje = 0;
    ui->kocenjeLcd->display(value);
        }
    } else {
          ui->statusbar->showMessage("ZAUSTAVITI MOTORE, PA PRITISNITE SMIJER NAZAD");
    }
}

