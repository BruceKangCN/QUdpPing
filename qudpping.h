#ifndef QUDPPING_H
#define QUDPPING_H

#include <QWidget>
#include <QElapsedTimer>
#include <QUdpSocket>
#include <QByteArray>

QT_BEGIN_NAMESPACE
namespace Ui { class QUdpPing; }
QT_END_NAMESPACE

class QUdpPing : public QWidget
{
    Q_OBJECT

public:
    QUdpPing(QWidget *parent = nullptr);
    ~QUdpPing();

private slots:
    void on_btnListen_clicked();

    void on_btnPing_clicked();

private:
    Ui::QUdpPing *ui;

    quint16 listen;
    QHostAddress host;
    quint16 port;
    QHostAddress senderHost;
    quint16 senderPort;
    QUdpSocket* socket;
    QElapsedTimer* timer;
    qint64 t;
    QByteArray data;
};
#endif // QUDPPING_H
