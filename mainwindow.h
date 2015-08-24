#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QDebug>
#include <QTimer>
#include <QPainter>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QSerialPort *serial;
    QTimer *timer;
    int timerID;
    int STATE_SERIAL;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void initControls();
    void openSerialPort();
    void displayState(QString path);

public slots:
    void displayValue();
    void sendC();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
