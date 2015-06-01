#include <QCoreApplication>
#include "ntptest.h"
#include <QDebug>
#include <sys/time.h>
#include "param.h"
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
 *  to be wrote as [+12; -14] integer number.
 *
 * Parametri:
 * -t specifica timezone
 * -v verbose
 * -f verbose to file
 * -h help
 * -e version
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    for (int i=0; i<argc; i++){
        if(QString(argv[i]).compare("-e")==0){
            qDebug() << "versione" <<GIT_CURRENT_SHA1;
            //qApp->quit();
            return 1;
        }
    }

    NtpTest *test;
    if (argc==1){
        test = new NtpTest();
        test->run();
    }
    if (argc>1){    //options
        using namespace util;
        debug = debugVideo;
        for (int i=1; i<argc-1; i++){
//            if(QString(argv[i]).compare("-v")==0)
//                debug=debugVideo;
//            if(QString(argv[i]).compare("-f")==0)
//                debug=debugFile;
            if(QString(argv[i]).compare("-t")==0){
                if ((atoi(argv[i+1])<=14) || (atoi(argv[i+1])>=-12)){
                    param::timezone = atoi(argv[i+1]);
                }
            }
        }
        test = new NtpTest(param::timezone);
        test->run(QString(argv[argc-1]));
    }

    return a.exec();
}
