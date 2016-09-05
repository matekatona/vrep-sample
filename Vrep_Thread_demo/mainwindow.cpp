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
    ui->textEdit->setText(this->socket1.readLine());
}

void MainWindow::readyRead2()
{
    ui->textEdit_2->setText(this->socket2.readLine());
}
