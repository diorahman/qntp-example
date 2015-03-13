#include "ntptest.h"
#include <QDebug>

NtpTest::NtpTest(QObject *parent) :
    QObject(parent)
{
    m_client = new NtpClient(this);
    connect(m_client, SIGNAL(replyReceived(QHostAddress,quint16,NtpReply)), this, SLOT(onReplyReceived(QHostAddress,quint16,NtpReply)));
}

void NtpTest::run()
{
    // tok-ntp-ext.asi 17.82.254.14     2 u 1141  512    1  571.869  -735.58  45.102
    m_client->sendRequest(QHostAddress("17.82.254.14"), 123);
}

void NtpTest::onReplyReceived(QHostAddress host, quint16 port, NtpReply reply)
{
    qDebug() << "reference time:" << reply.referenceTime();
    qDebug() << "origin time:" << reply.originTime();
}
