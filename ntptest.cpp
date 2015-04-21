#include "ntptest.h"
#include <QDebug>
#include <sys/time.h>

#define CET (+1)
#define DST ()

NtpTest::NtpTest(int timeZone, QObject *parent) :
    QObject(parent),
    m_timeZone(timeZone*3600)
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
    updateTime(reply.transmitTime().toTime_t());
}

void NtpTest::lookedUp(const QHostInfo &host)
{
    if (host.error() != QHostInfo::NoError) {
        //qDebug() << "Cannot resolve URL:" << host.errorString();
        return;
    }

    foreach (const QHostAddress &address, host.addresses()){
        //qDebug() << "Found address:" << address.toString();
        m_client->sendRequest(address, 123);
    }
}

void NtpTest::updateTime(time_t ora_s){
    if (isDST(ora_s))
        ora_s += 3600;  //if DST, add one hour.

    ora_s +=m_timeZone;

    struct timeval temp;
    temp.tv_sec = ora_s;
    temp.tv_usec = 0;
    settimeofday(&temp, 0);
    system("/sbin/hwclock -wu");        /* Update RTC from system */
}

//european DST: from the last sunday of March to the last sunday of October
bool NtpTest::isDST(time_t ora_s){
    struct tm *pt = gmtime(&ora_s);

    if (pt->tm_mon == MAR){
        pt->tm_mday = 31;   //set on April, 31th
        time_t tmp = mktime(pt);
        pt = gmtime(&tmp);
        pt->tm_mday = 31 - pt->tm_wday;   //find the last Sunday of March
        pt->tm_hour = 2;
        pt->tm_min = 0;
        pt->tm_sec = 0;
        if (ora_s >= mktime(pt))   //if greater (or equal), DST
            return true;
        else
            return false;
    }

    if (pt->tm_mon == OCT){
        pt->tm_mday = 31;   //set on October, 31th
        time_t tmp = mktime(pt);
        pt = gmtime(&tmp);
        pt->tm_mday = 31 - pt->tm_wday;   //find the last Sunday of October
        pt->tm_hour = 3;
        pt->tm_min = 0;
        pt->tm_sec = 0;
        if (ora_s < mktime(pt))   //if lower, DST
            return true;
        else
            return false;
    }

    if ((pt->tm_mon < MAR) || (pt->tm_mon > OCT))   //winter, from November to February, isn't DST
        return false;

    if ((pt->tm_mon > MAR) || (pt->tm_mon < OCT))   //summer, from April to Septemper, is DST
        return true;

    return false;
}
