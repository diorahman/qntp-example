#include <QCoreApplication>
#include "ntptest.h"
#include <QDebug>
/**
 * @brief Start an istance of the NtpTest application.
 * Call:
 * ntp
 *  send a NTP request to the server tok-ntp-ext.asi (17.82.254.14)
 * ntp <url>
 *  send a NTP request to the url passed as argument. The URL can
 *  be wrote both as IP address or as host name.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    NtpTest test;
    switch (argc){
    case 2:
        //use custom url
        test.run(QString(argv[1]));
        break;
    default:
        //use default server
        test.run();
    }
    return a.exec();
}
