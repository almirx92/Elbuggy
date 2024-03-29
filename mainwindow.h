#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ubrzanjeDial_valueChanged(int value);

    void on_startBtn_clicked();

    void on_stopBtn_clicked();

    void on_nazadBtn_clicked();

    void on_progressBarUbrzanje_valueChanged(int value);

    void on_progressBarKocenje_valueChanged(int value);

    void on_naprijedBtn_clicked();

    void on_zaustaviBtn_clicked();

    void on_dialKocenje_valueChanged(int value);

    void updateArduino(QString command);


private:
    Ui::MainWindow *ui;
    QSerialPort *arduino;

    static const quint16 arduino_uno_vendor_id = 9025;
        static const quint16 arduino_uno_product_id = 67;
        QString arduino_port_name;
        bool arduino_is_available;
};
#endif // MAINWINDOW_H
