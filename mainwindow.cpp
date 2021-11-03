/*
 Digital outputs on arduino

 PWM modulacija
 --------------------------------

 digitalPin 9 PWM -> dialUbrzanje  zakodirano a1 value
 digitalPin 10 PWM -> dialKocenje  zakodirano g1 value



 digitalPin 2 -> ON  zakodirano b1
 digitalPin 3 -> OFF zakodirano c1

 Smijer kretanja
 ---------------------------
 digitalPin 4 ->  Naprijed  zakodirano e1
 digitalPin 5 ->  Nazad     zakodirano d1
 ditalPin 6 -> Zaustavi     zakodiranof1

*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "modelElBuggy.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include<QWidget>


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
   //-----------------arduino-------------------------

    arduino_is_available = false;
     arduino_port_name = "";
     arduino = new QSerialPort;


     qDebug() << "Number of available ports: " << QSerialPortInfo::availablePorts().length();
     foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
         qDebug() << "Has vendor ID: " << serialPortInfo.hasVendorIdentifier();
         if(serialPortInfo.hasVendorIdentifier()){
             qDebug() << "Vendor ID: " << serialPortInfo.vendorIdentifier();
         }
         qDebug() << "Has Product ID: " << serialPortInfo.hasProductIdentifier();
         if(serialPortInfo.hasProductIdentifier()){
             qDebug() << "Product ID: " << serialPortInfo.productIdentifier();
         }
     }



     foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
         if(serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier()){
             if(serialPortInfo.vendorIdentifier() == arduino_uno_vendor_id){
                 if(serialPortInfo.productIdentifier() == arduino_uno_product_id){
                     arduino_port_name = serialPortInfo.portName();
                     arduino_is_available = true;
                 }
             }
         }
     }

   // arduino_is_available =true;
  //  arduino_port_name = "/dev/tty.usbserial-14520";
     if(arduino_is_available){
         // open and configure the serialport
         arduino->setPortName(arduino_port_name);
         arduino->open(QSerialPort::WriteOnly);
         arduino->setBaudRate(QSerialPort::Baud9600);
         arduino->setDataBits(QSerialPort::Data8);
         arduino->setParity(QSerialPort::NoParity);
         arduino->setStopBits(QSerialPort::OneStop);
         arduino->setFlowControl(QSerialPort::NoFlowControl);
     }else{
         // give error message if not available
         qDebug("Port error Couldn't find the Arduino!");
     }


    //------------------------------------------------
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
    if(arduino->isOpen()){
           arduino->close();
       }
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
    MainWindow::updateArduino(QString("a%1").arg(value));
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
         MainWindow::updateArduino(QString("b%1").arg(1));
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
         MainWindow::updateArduino(QString("c%1").arg(1));
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
        MainWindow::updateArduino(QString("d%1").arg(1));
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
       MainWindow::updateArduino(QString("e%1").arg(1));
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
    MainWindow::updateArduino(QString("f%1").arg(1));
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
    MainWindow::updateArduino(QString("g%1").arg(value));
        }
    } else {
          ui->statusbar->showMessage("ZAUSTAVITI MOTORE, PA PRITISNITE SMIJER NAZAD");
    }
}

void MainWindow::updateArduino(QString command)
{
    if(arduino->isWritable()){
        arduino->write(command.toStdString().c_str());
        qDebug() << "Is sent to arduino";
        qDebug() << command.toStdString().c_str();
        qDebug() << "-----------------------------";
    }else{
        qDebug() << "Couldn't write to serial!";
    }
}

