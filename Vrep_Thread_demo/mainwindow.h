#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>  // requires QT += network in .pro file!!!

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void readyRead1();
    void readyRead2();

private:
    Ui::MainWindow *ui;

    QTcpSocket socket1;
    QTcpSocket socket2;
};

#endif // MAINWINDOW_H
