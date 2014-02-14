#include <QCoreApplication>
#include "ntptest.h";
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    NtpTest test;
    test.run();

    return a.exec();
}
