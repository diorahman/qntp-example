#ifndef NTPTEST_H
#define NTPTEST_H

#include <QObject>
#include <QHostAddress>
#include <QHostInfo>
#include "qntp/QNtp.h"
#include "qntp/NtpClient.h"
#include "qntp/NtpReply.h"

class NtpTest : public QObject
{
    Q_OBJECT
public:

    /**
     * @brief Default costructor.
     * @param parent Parent of the object.
     */
    explicit NtpTest(QObject *parent = 0);

    /**
     * @brief Ask for a server reply. Resolve the url and then send a request.
     * @param servName Name of the NTP server (both IP or url)
     */
    void run(QString servName);

    /**
     * @brief Ask for a default server reply.
     */
    void run();

    void aggiornaOra(qint64 ora_s);
    void isDST(qint64 ora_s);

    const int DST_change[] = {
        1427590800, 1445738400, //2015
        1459040400, 1477792800, //2016
        1490490000, 1509242400, //2017
        1521939600, 1540692000, //2018
        1553994000, 1572141600, //2019
        1585443600, 1603591200, //2020
        1616893200, 1635645600, //2021
        1648342800, 1667095200, //2022
        1679792400, 1698544800, //2023
        1711846800, 1729994400, //2024
        1743296400, 1761444000, //2025
        1774746000, 1792893600, //2026
        1806195600, 1824948000, //2027
        1837645200, 1856397600, //2028
        1869094800, 1887847200, //2029
        1901149200, 1919296800, //2030
        1932598800, 1950746400, //2031
        1964048400, 1982800800, //2032
        1995498000, 2014250400, //2033
        2026947600, 2045700000, //2034
        2058397200, 2077149600, //2035
    };    //hour of DST switch starting from 2015 to 2050

signals:

private slots:
    void onReplyReceived(QHostAddress host, quint16 port, NtpReply reply);
    void lookedUp(const QHostInfo &host);

private:
    NtpClient * m_client;

};

#endif // NTPTEST_H
