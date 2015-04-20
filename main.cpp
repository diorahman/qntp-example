#include <QCoreApplication>
#include "ntptest.h"
#include <QDebug>
#include <sys/time.h>
/**
 * @brief Start an istance of the NtpTest application.
 * Call:
 * ntp
 *  send a NTP request to the server tok-ntp-ext.asi (17.82.254.14)
 * ntp <url>
 *  send a NTP request to the url passed as argument. The URL can
 *  be wrote both as IP address or as host name.
 * ntp <url> <timezone>
 *  send a NTP request to the url passed as argument. The URL can
 *  be wrote both as IP address or as host name. The timezone has
 *  to be wrote as +12 <> -14 integer number.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    NtpTest *test;
    switch (argc){
    case 2:
        //use custom url
        test = new NtpTest();
        test->run(QString(argv[1]));
        break;
    case 3:
        //use custom url, custom timezone
        if ((atoi(argv[2])>14) || (atoi(argv[2])<-12)){
            test = new NtpTest();
        }
        else{
            test = new NtpTest(atoi(argv[2]));
        }
        test->run(QString(argv[1]));
        break;
    default:
        //use default server
        test = new NtpTest();
        test->run();
    }

    return a.exec();
}
