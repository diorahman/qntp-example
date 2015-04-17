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

signals:

private slots:
    void onReplyReceived(QHostAddress host, quint16 port, NtpReply reply);
    void lookedUp(const QHostInfo &host);

private:
    NtpClient * m_client;

};

#endif // NTPTEST_H
