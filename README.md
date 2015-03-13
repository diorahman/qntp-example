# A simple example consuming QNtp

QNtp is hosted on https://code.google.com/p/qntp 

I have the copy here inside this repo.

## using this example

```
$ git clone git@github.com:diorahman/qntp-example.git
$ mkdir build
$ cd build
// if you're on a mac (use your own platform -spec for qmake)
$ qmake -spec macx-g++ ../qntp-example/ntp.pro
$ make
$ ntp
QDateTime("Sat Mar 14 06:03:16 2015") 
QDateTime("Sat Mar 14 06:03:27 2015")
```

# the meat

```cpp
void NtpTest::run()
{
    // tok-ntp-ext.asi 17.82.254.14     2 u 1141  512    1  571.869  -735.58  45.102
    m_client->sendRequest(QHostAddress("17.82.254.14"), 123);
}

void NtpTest::onReplyReceived(QHostAddress host, quint16 port, NtpReply reply)
{
    qDebug() << "reference time:" << reply.referenceTime();
    qDebug() << "origin time:" << reply.originTime();
}
```


# license 
The example is MIT, however the QNtp has its own license
