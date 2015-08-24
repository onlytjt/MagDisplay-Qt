#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    STATE_SERIAL = -1;
    initControls();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initControls()
{
    // 显示标题
    QFont ft;
    ft.setPointSize(22);
    ui->label->setFont(ft);
    displayState("./pic/red.jpeg");
    ui->comboBox->addItem("COMLEFT");
    ui->comboBox->addItem("COMRIGHT");
    ui->comboBox->setCurrentIndex(1);
    ui->comboBox_2->addItem("4800");
    ui->comboBox_2->addItem("9600");
    ui->comboBox_2->addItem("115200");
    ui->comboBox_2->setCurrentIndex(1);
}

void MainWindow::openSerialPort()
{
    serial = new QSerialPort(this);
    QObject::connect(serial, SIGNAL(readyRead()), this, SLOT(displayValue()));
    QString port;
    if (ui->comboBox->currentText() == "COMLEFT") { // 使用左边usb口
        port = "tty.wchusbserial1420";
    } else { // 使用右边usb口
        port = "tty.wchusbserial1410";
    }
    serial->setPortName(port);
    serial->setBaudRate(ui->comboBox_2->currentText().toInt());
    serial->setParity(QSerialPort::NoParity);
    serial->setDataBits(QSerialPort::Data8);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    if (serial->open(QIODevice::ReadWrite)) {
        qDebug() << "open port succeed!";
        displayState("./pic/green.jpeg");
        STATE_SERIAL = 1;
    } else {
        qDebug() << "open port failed!";
        STATE_SERIAL = 0;
    }
}

void MainWindow::displayState(QString path)
{
    QImage *img = new QImage;
    img->load(path);
    QImage *imgScaled = new QImage;
    *imgScaled = img->scaled(35, 35, Qt::KeepAspectRatio);
    ui->lab_state->setPixmap(QPixmap::fromImage(*imgScaled));
    //QPainter painter(ui->lab_state);
}

void MainWindow::displayValue()
{
    // 接收串口数据
    QByteArray ba;
    ba = serial->readAll();
    ba = ba.left(5);
    float distance = ba.toFloat();
    distance = 0.026716*distance - 186.6173;
    QString show_dis;
    show_dis = QString::number(distance) + "mm";

    //设置lab_dis的字体和颜色
    QPalette pa;
    pa.setColor(QPalette::WindowText, Qt::red);
    ui->lab_dis->setPalette(pa);
    QFont ft;
    ft.setPointSize(30);
    ui->lab_dis->setFont(ft);

    // 数据更新
    ui->lab_dis->setText(show_dis);
    ui->lineEdit->setText(ba);
}

void MainWindow::sendC()
{
    if (STATE_SERIAL == 1) {
        serial->write("c");
    } else {
        return;
    }

}

void MainWindow::on_pushButton_clicked() // 打开button
{
    openSerialPort();
    timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(sendC()));
    timer->start(10);
}

void MainWindow::on_pushButton_2_clicked() // 关闭button
{
    serial->close();
    timer->stop();
    displayState("./pic/red.jpeg");
    STATE_SERIAL = 0;
    qDebug() << "port has been closed!";
}
