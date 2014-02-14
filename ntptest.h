#ifndef NTPTEST_H
#define NTPTEST_H

#include <QObject>
#include <QHostAddress>
#include "qntp/QNtp.h"
#include "qntp/NtpClient.h"
#include "qntp/NtpReply.h"

class NtpTest : public QObject
{
    Q_OBJECT
public:
    explicit NtpTest(QObject *parent = 0);
    void run();

signals:

private slots:
    void onReplyReceived(QHostAddress host, quint16 port, NtpReply reply);

private:
    NtpClient * m_client;

};

#endif // NTPTEST_H
