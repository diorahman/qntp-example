#ifndef NTPTEST_H
#define NTPTEST_H

#include <QObject>
#include <QHostAddress>
#include <QHostInfo>
#include <QTimer>
#include "qntp/QNtp.h"
#include "qntp/NtpClient.h"
#include "qntp/NtpReply.h"

class NtpTest : public QObject
{
    Q_OBJECT
public:

    //monts of the year (in struct tm data)
    enum MONTHS{
        JAN=0,
        FEB=1,
        MAR=2,
        APR=3,
        MAJ=4,
        JUN=5,
        JUL=6,
        AUG=7,
        SEP=8,
        OCT=9,
        NOV=10,
        DEC=11
    };

    /**
     * @brief Default costructor.
     * @param timeZone Time zone (default is UTC)
     * @param parent Parent of the object.
     */
    explicit NtpTest(int timeZone = 0, QObject *parent = 0);

    /**
     * @brief Ask for a server reply. Resolve the url and then send a request.
     * If the url is an IP address, send a request directly. Resolve
     * an IP could be possibile, but may get problems in intranet without
     * DNS servers.
     * @param servName Name of the NTP server (both IP or url)
     */
    void run(const QString servName);

    /**
     * @brief Ask for a default server reply.
     */
    void run();

public slots:
    void timeEnd();

signals:

private slots:
    /**
     * @brief Receive the timeserver responce and set the local time.
     * @param host Address of the server
     * @param port Port of the server
     * @param reply Reply of the server
     */
    void onReplyReceived(QHostAddress host, quint16 port, NtpReply reply);

    /**
     * @brief Receive the list of IP from DNS sever and send requests.
     * If empty list, just quit.
     * @param host Reply of the DSN server.
     */
    void lookedUp(const QHostInfo &host);

    /**
     * @brief Update the system time. Works on Linux Embedded.
     * @param hour_s Time to be set (UTC)
     */
    void updateTime(time_t hour_s);

    /**
     * @brief Calculate if the DST is active
     * @param hour_s Time to calculate if the DST is applied or not.
     * @return true if DST has to be applied, false otherwise.
     */
    bool isDST(time_t hour_s);
private:
    NtpClient * m_client;   //!< Client fot NTP comms
    int m_timeZone;     //!< Timezone
    QTimer *m_timer;    //!< Timeout timer
};

#endif // NTPTEST_H
