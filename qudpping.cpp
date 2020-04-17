#include "qudpping.h"
#include "ui_qudpping.h"

#include <QDebug>

QUdpPing::QUdpPing(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::QUdpPing)
{
    ui->setupUi(this);

    timer = new QElapsedTimer();
    socket = new QUdpSocket(this);
    sent = 0;
    received = 0;

    connect(socket, &QUdpSocket::readyRead,
            [=]()
    {
        if(socket->readDatagram(data.data(), 32, &senderHost, &senderPort) > 0)
        {
            //ui->textBrowser->append(QString("[receive from %1:%2] %3 ms").arg(sender.toString()).arg(port).arg(elapsed));

            //senderPort = QString(data).toUShort();
            //qDebug() << "sender's port: " << senderPort;

            if(QString(data) == "00000000000000000000000000000000")
            {
                //qDebug() << "client to server...";
                socket->writeDatagram("return", senderHost, senderPort);
            }
            else
            {
                //qDebug() << "server to client...";
                t = timer->nsecsElapsed();
                double elapsed = t * 1.0 / 1000000;
                received++;

                ui->textBrowser->append(QString("[receive from %1:%2] %3 ms").arg(senderHost.toString()).arg(port).arg(elapsed));
                ui->textBrowser->append(QString("sent: %1").arg(sent));
                ui->textBrowser->append(QString("received: %1").arg(received));
                ui->textBrowser->append("");

                timer->elapsed();
            }
        }
    });
}

QUdpPing::~QUdpPing()
{
    delete ui;
}


void QUdpPing::on_btnListen_clicked()
{
    listen = ui->inpListen->text().toUShort();
    socket->bind(listen);

    ui->textBrowser->append(QString("start to listen on: %1").arg(socket->localPort()));
    ui->textBrowser->append("");
}

void QUdpPing::on_btnPing_clicked()
{
    host = QHostAddress(ui->inpIp->text());
    port = ui->inpPort->text().toUShort();
    data = QString("00000000000000000000000000000000").toUtf8();

    timer->restart();
    if(socket->writeDatagram(data.data(), 32, host, port) != -1)
        sent++;
}
