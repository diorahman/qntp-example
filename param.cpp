/**
 * @file param.cpp
 * @author Francesco Fraccaroli <francesco.fraccaroli@lever.it>
 * ### LICENSE
 * Copyright Lever srl 2015
 *
 * @brief
 *
 */

#include "param.h"
#include <QDebug>
#include <QFile>

namespace param
{

bool verbose = false;
int timezone=0;
}

namespace util{
const QString debug_path = "/local/root/log/logNtp.txt";

void (*debug)(const QString &str) = noDebug;
void noDebug(const QString &str){

}

void debugVideo(const QString &str){
    qDebug() << str;
}

void debugFile(const QString &str){
    QFile fileLog(debug_path);
    fileLog.open(QIODevice::Append | QIODevice::Text);
    QTextStream(&fileLog) << str << "\n";
    qDebug() << str;
}
}
