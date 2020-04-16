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

    connect(socket, &QUdpSocket::readyRead,
            [=]()
    {
        if(socket->readDatagram(data.data(), 32, &senderHost, &senderPort) > 0)
        {
            //ui->textBrowser->append(QString("[receive from %1:%2] %3 ms").arg(sender.toString()).arg(port).arg(elapsed));

            senderPort = QString(data).toUShort();
            //qDebug() << "sender's port: " << senderPort;

            if(senderPort)
            {
                //qDebug() << "client to server...";
                socket->writeDatagram("return", senderHost, senderPort);
            }
            else
            {
                //qDebug() << "server to client...";
                t = timer->nsecsElapsed();
                double elapsed = t * 1.0 / 1000000;
                ui->textBrowser->append(QString("[receive from %1:%2] %3 ms").arg(senderHost.toString()).arg(port).arg(elapsed));
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
}

void QUdpPing::on_btnPing_clicked()
{
    host = QHostAddress(ui->inpIp->text());
    port = ui->inpPort->text().toUShort();
    data = QString::number(socket->localPort()).toUtf8();

    timer->restart();
    socket->writeDatagram(data.data(), 32, host, port);
}
