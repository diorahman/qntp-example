#include "ntptest.h"
#include <QDebug>
#include <QCoreApplication>
#include <QStringList>
#include <sys/time.h>

#define DEBUG_LEVEL 2   //0=no, 1=to qDebug(), 2=to log file and qDebug()

#if DEBUG_LEVEL==0
    #define debugC(x) ;     //info
#endif

#if DEBUG_LEVEL==1
    #define debugC(x) qDebug() << x   //info
#endif

#if DEBUG_LEVEL==2
#include <QFile>
#define debug_path "/local/root/log/logNtp.txt"
#define debugC(x) {QFile fileLog(debug_path); fileLog.open(QIODevice::Append | QIODevice::Text); QTextStream(&fileLog) << x << "\n"; qDebug() << x;}
#endif

NtpTest::NtpTest(int timeZone, QObject *parent) :
    QObject(parent),
    m_timeZone(timeZone*3600),
    m_timer(0)
{
    debugC("start Npt");
    m_client = new NtpClient(this);
    connect(m_client, SIGNAL(replyReceived(QHostAddress,quint16,NtpReply)), this, SLOT(onReplyReceived(QHostAddress,quint16,NtpReply)));
    m_timer = new QTimer();
    m_timer->setInterval(15000);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(timeEnd()));
}

void NtpTest::timeEnd(){
    debugC("Terminated for timeout.");
    qApp->quit();
}

void NtpTest::run()
{
    // tok-ntp-ext.asi 17.82.254.14     2 u 1141  512    1  571.869  -735.58  45.102
    m_client->sendRequest(QHostAddress("17.82.254.14"), 123);
    m_timer->start();
}

void NtpTest::run(QString servName)
{
    bool isIP;
    //check if the servName is an IP address
    QStringList campi = servName.split(".", QString::SkipEmptyParts);
    if (campi.length()!=4)
        isIP = false;
    if (!((campi.at(0).toInt(&isIP)>=0) && (campi.at(0).toInt(&isIP)<=255)))
        isIP = false;
    if (!((campi.at(1).toInt(&isIP)>=0) && (campi.at(1).toInt(&isIP)<=255)))
        isIP = false;
    if (!((campi.at(2).toInt(&isIP)>=0) && (campi.at(2).toInt(&isIP)<=255)))
        isIP = false;
    if (!((campi.at(3).toInt(&isIP)>=0) && (campi.at(3).toInt(&isIP)<=255)))
        isIP = false;

    if (isIP){
        m_client->sendRequest(QHostAddress(servName), 123);
        debugC("Send request to IP " << servName);
    }
    else{
        QHostInfo::lookupHost(servName, this, SLOT(lookedUp(QHostInfo)));
        debugC("Lookup host for url " << servName);
    }
    m_timer->start();
}

void NtpTest::onReplyReceived(QHostAddress host, quint16 port, NtpReply reply)
{
    Q_UNUSED(host)
    Q_UNUSED(port)

    m_timer->stop();
    updateTime(reply.transmitTime().toTime_t());
    debugC("Updated" << reply.transmitTime().toString());

    qApp->quit();
}

void NtpTest::lookedUp(const QHostInfo &host)
{
    m_timer->stop();
    if (host.error() != QHostInfo::NoError) {
        debugC("Cannot resolve URL:" << host.errorString());
        qApp->quit();
    }

    foreach (const QHostAddress &address, host.addresses()){
        debugC("Found address:" << address.toString());
        m_client->sendRequest(address, 123);
        m_timer->start();
    }
}

void NtpTest::updateTime(time_t hour_s){
    if (isDST(hour_s))
        hour_s += 3600;  //if DST, add one hour.

    hour_s +=m_timeZone;

    struct timeval temp;
    temp.tv_sec = hour_s;
    temp.tv_usec = 0;
    settimeofday(&temp, 0);
    system("/sbin/hwclock -wu");        /* Update RTC from system */
}

//european DST: from the last sunday of March to the last sunday of October
bool NtpTest::isDST(time_t hour_s){
    struct tm *pt = gmtime(&hour_s);

    if (pt->tm_mon == MAR){
        pt->tm_mday = 31;   //set on April, 31th
        time_t tmp = mktime(pt);
        pt = gmtime(&tmp);
        pt->tm_mday = 31 - pt->tm_wday;   //find the last Sunday of March
        pt->tm_hour = 2;
        pt->tm_min = 0;
        pt->tm_sec = 0;
        if (hour_s >= mktime(pt))   //if greater (or equal), DST
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
        if (hour_s < mktime(pt))   //if lower, DST
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
