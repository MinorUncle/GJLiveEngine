/*
 *  Copyright (C) 2008-2009 Andrej Stepanchuk
 *  Copyright (C) 2009-2010 Howard Chu
 *
 *  This file is part of librtmp.
 *
 *  librtmp is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as
 *  published by the Free Software Foundation; either version 2.1,
 *  or (at your option) any later version.
 *
 *  librtmp is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with librtmp see the file COPYING.  If not, write to
 *  the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *  Boston, MA  02110-1301, USA.
 *  http://www.gnu.org/copyleft/lgpl.html
 */

#ifndef __KK_LOG_H__
#define __KK_LOG_H__

#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include "GJPlatformHeader.h"
#ifdef __cplusplus
extern "C" {
#endif
/* Enable this to get full debugging */
/* #define _DEBUG */

#define GJ_DEBUG

#define DEFAULT_LOG GNULL

#define GJ_DEBUG_FREQUENTLY

typedef enum {
    GJ_LOGNONE,   ///永远不产生log
    GJ_LOGFORBID, //调试包会产生中断，
    GJ_LOGERROR,
    GJ_LOGWARNING,
    GJ_LOGDEBUG,
    GJ_LOGINFO,
    GJ_LOGALL
} GJ_LogLevel;

typedef struct _ {
    GChar *     className;
    GJ_LogLevel dLevel;
} GJLogClass;

extern const GJLogClass logTrancking;
extern const GJLogClass Default_NONE;
extern const GJLogClass Default_FORBID;
extern const GJLogClass Default_ERROR;
extern const GJLogClass Default_WARNING;
extern const GJLogClass Default_DEBUG;
extern const GJLogClass Default_INFO;
extern const GJLogClass Default_ALL;

#define LOG_NONE (&Default_NONE)
#define LOG_FORBID (&Default_FORBID)
#define LOG_ERROR (&Default_ERROR)
#define LOG_WARNING (&Default_WARNING)
#define LOG_DEBUG (&Default_DEBUG)
#define LOG_INFO (&Default_INFO)
#define LOG_ALL (&Default_ALL)
#define LOG_TRACKING (&logTrancking)


extern GJLogClass *defaultDebug;

typedef GVoid(GJ_LogCallback)(GJLogClass *logClass, GJ_LogLevel level, const char *pre, const char *fmt, va_list);

//小于GJ_debuglevel则显示
GVoid GJ_LogSetLevel(GJ_LogLevel lvl);

GVoid GJ_LogSetCallback(GJ_LogCallback *cb);
GVoid GJ_LogSetOutput(const char *file);

GVoid GJ_Log(const GVoid *logClass, GJ_LogLevel level, const char *pre, const char *format, ...) __printflike(4, 5);
GVoid GJ_LogHex(GJ_LogLevel level, const GUInt8 *data, GUInt32 len);
GVoid GJ_LogHexString(GJ_LogLevel level, const GUInt8 *data, GUInt32 len);

//所有等级都会打印，但是大于GJ_LOGDEBUG模式会产生中断
GVoid GJ_LogAssert(GInt32 isTrue,const char *pre,const char *format, ...) __attribute__((format(printf, 3, 4)));
GBool GJ_LogCheckResult(GResult result, const char *pre, const char *format, ...);
GBool GJ_LogCheckBool(GBool result, const char *pre, const char *format, ...);

GJ_LogLevel GJ_LogGetLevel(GVoid);

#define GJCheckResult(isTrue, format, ...) GJ_LogCheckResult(isTrue, __func__, format, ##__VA_ARGS__)
#define GJCheckBool(isTrue, format, ...) GJ_LogCheckBool(isTrue, __func__, format, ##__VA_ARGS__)


#ifdef GJ_DEBUG
    
#define GJLOGTRACKING(format,...) GJ_Log(LOG_TRACKING,GJ_LOGDEBUG, __func__, format, ##__VA_ARGS__)

#define GJCLOG(dclass, level, format, ...) GJ_Log((dclass), (level), __func__, format, ##__VA_ARGS__)
    
#define GJLOG(level, format, ...) GJ_Log(GNULL, (level), __func__, format, ##__VA_ARGS__)

#define GJAssert(isTrue, format, ...) GJ_LogAssert(isTrue, __func__, format, ##__VA_ARGS__)

#ifdef GJ_DEBUG_FREQUENTLY

#define GJLOGFREQ(format, ...) GJ_Log(DEFAULT_LOG, GJ_LOGALL, __func__, format, ##__VA_ARGS__)
#else

#define GJLOGFREQ(level, format, ...)
#endif

#else
    
#define GJLOGTRACKING(...)
#define GJCLOG(dclass, level, format, ...)
#define GJLOG(level, format, ...)
#define GJOLOG(switch, level, format, ...)
#define GJLOGFREQ(level, format, ...)
#define GJAssert(isTrue, format, ...)
#endif
    
    
#ifdef __cplusplus
}
#endif

#endif
