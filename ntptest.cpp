#include "ntptest.h"
#include <QDebug>
#include <sys/time.h>

#define CET (+1)
#define DST ()

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

void NtpTest::run(QString servName)
{
    QHostInfo::lookupHost(servName, this, SLOT(lookedUp(QHostInfo)));
}

void NtpTest::onReplyReceived(QHostAddress host, quint16 port, NtpReply reply)
{
    qDebug() << "reference time:" << reply.referenceTime();
    qDebug() << "origin time:" << reply.originTime();
    qDebug() << "destination time:" << reply.destinationTime();
    qDebug() << "transmit time:" << reply.transmitTime();
    qDebug() << "receive time:" << reply.receiveTime();
    aggiornaOra(reply.transmitTime().toTime_t());
}

void NtpTest::lookedUp(const QHostInfo &host)
{
    if (host.error() != QHostInfo::NoError) {
        qDebug() << "Cannot resolve URL:" << host.errorString();
        return;
    }

    foreach (const QHostAddress &address, host.addresses()){
        qDebug() << "Found address:" << address.toString();
        m_client->sendRequest(address, 123);
    }
}

void NtpTest::aggiornaOra(qint64 ora_s){
    struct timeval temp;
    temp.tv_sec = ora_s;
    temp.tv_usec=0;

    struct tm *pt = 0;
    pt = new tm;

    settimeofday(&temp, 0);
    system("/sbin/hwclock -wu");        /* Update RTC from system */
}

void NtpTest::isDST(qint64 ora_s){
    struct tm *pt = qmtime(&ora_s);
    if (pt->tm_wday ==
}
