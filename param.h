/**
 * @file param.h
 * @author Francesco Fraccaroli <francesco.fraccaroli@lever.it>
 * ### LICENSE
 * Copyright Lever srl 2015
 *
 * @brief
 *
 */

#ifndef PARAM_H
#define PARAM_H

#include <QString>

namespace param
{
    extern bool verbose;
    extern int timezone;
}

namespace util{
extern void (*debug)(const QString &);
void noDebug(const QString &);
void debugVideo(const QString &);
void debugFile(const QString &);
}

#endif // PARAM_H
