#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    this->socket1.disconnectFromHost();
    this->socket2.disconnectFromHost();
    this->max1 = 0;
    this->max2 = 0;
    this->counter = 0;
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if(this->socket1.state()!=QTcpSocket::ConnectedState)
    {
        socket1.connectToHost("127.0.0.1", 25455);
        socket2.connectToHost("127.0.0.1", 25456);
        int timeout_ms = 100;
        socket1.waitForConnected(timeout_ms);
        socket2.waitForConnected(timeout_ms);
        if(this->socket1.state()==QTcpSocket::ConnectedState && this->socket2.state()==QTcpSocket::ConnectedState)
        {
            connect(&this->socket1, SIGNAL(readyRead()), this, SLOT(readyRead1()));
            connect(&this->socket2, SIGNAL(readyRead()), this, SLOT(readyRead2()));
            ui->pushButton->setText("Disconnect");
        }
    }
    else
    {
        this->socket1.disconnectFromHost();
        disconnect(&this->socket1, SIGNAL(readyRead()), this, SLOT(readyRead1()));
        this->socket2.disconnectFromHost();
        disconnect(&this->socket2, SIGNAL(readyRead()), this, SLOT(readyRead2()));
        ui->pushButton->setText("Connect");
    }
}

void MainWindow::readyRead1()
{
    QByteArray line = this->socket1.readLine();
    QString actualTimeString = line.split(':').at(1);
    float actualTime = actualTimeString.toFloat();
    qDebug() << actualTime << " <==> " << this->max1;
    if(actualTime > this->max1)
    {
        ui->textEdit->setText(line);
        this->max1 = actualTime;
    }
    if(this->counter>9)
    {
        this->counter = 0;
        this->max1 = 0;
    }
    else
    {
        this->counter++;
    }
}

void MainWindow::readyRead2()
{
    QByteArray line = this->socket2.readLine();
    QString actualTimeString = line.split(':').at(1);
    float actualTime = actualTimeString.toFloat();
    ui->textEdit_2->setText(line);
    qDebug() << actualTime << " <==> " << this->max2;
    if(actualTime > this->max2)
    {
        this->max2 = actualTime;
    }
}
