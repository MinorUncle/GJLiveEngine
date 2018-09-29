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
#include <dispatch/once.h>
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

typedef struct _GJLog GJLog;

extern GJLog* defalutLoger;
typedef GVoid(*GJ_LogCallback)(GJLog* loger, const GJLogClass *logClass, GJ_LogLevel level, const char *pre, const char *fmt, va_list);

GVoid gj_async_time_func_log(GJLog* loger, const GJLogClass *dClass, GJ_LogLevel level, const char *pre, const char *format, va_list vl);
GVoid gj_sync_time_func_log(GJLog* loger, const GJLogClass *dClass, GJ_LogLevel level, const char *pre, const char *format, va_list vl);
GVoid gj_async_log(GJLog* loger, const GJLogClass *dClass, GJ_LogLevel level, const char *pre, const char *format, va_list vl);

GVoid GJLog_Create(GJLog** pLoger,GJ_LogCallback logCallback);
GVoid GJLog_SetLogFile(GJLog* loger,const GChar* file);
GVoid GJLog_Log(GJLog* loger,const GJLogClass *logClass, GJ_LogLevel level, const char *pre, const char *format, ...) __printflike(5, 6);
GVoid GJLog_SetLogLevel(GJLog* loger,GJ_LogLevel level);
GVoid GJLog_LogClean(GJLog* loger,GBool complete);
GVoid GJLog_LogHex(GJLog* loger, GJ_LogLevel level, const GUInt8 *data, GUInt32 len);
GVoid GJLog_LogHexString(GJLog* loger, GJ_LogLevel level, const GUInt8 *data, GUInt32 len);
GVoid GJLog_Flush(GJLog* loger);

GVoid GJLog_Dealloc(GJLog** pLoger);
    
static inline GJLog* getDefaultLog(){
    if (defalutLoger == GNULL) {
        static dispatch_once_t onceToken;
        dispatch_once(&onceToken, ^{
            GJLog_Create(&defalutLoger,gj_async_time_func_log);
        });
    }
    return defalutLoger;
}
    
static inline GVoid GJ_LogClean(void){
        GJLog_LogClean(getDefaultLog(),GTrue);
}

static inline GVoid GJ_LogSetLevel(GJ_LogLevel lvl){
    GJLog_SetLogLevel(getDefaultLog(), lvl);
}

static inline GVoid GJ_LogSetOutput(const char *file){
    GJLog_SetLogFile(getDefaultLog(), file);
}



//所有等级都会打印，但是大于GJ_LOGDEBUG模式会产生中断
//GVoid GJ_LogAssert(GInt32 isTrue,const char *pre,const char *format, ...) __attribute__((format(printf, 3, 4)));
//GBool GJ_LogCheckResult(GResult result, const char *pre, const char *format, ...);
//GBool GJ_LogCheckBool(GBool result, const char *pre, const char *format, ...);

//GJ_LogLevel GJ_LogGetLevel(GVoid);

//#define GJCheckResult(isTrue, format, ...) GJ_LogCheckResult(isTrue, __func__, format, ##__VA_ARGS__)
//#define GJCheckBool(isTrue, format, ...) GJ_LogCheckBool(isTrue, __func__, format, ##__VA_ARGS__)


#ifdef GJ_DEBUG
    
#define GJCustomLOG(loger,level, format, ...) GJLog_Log(loger,GNULL, (level), __func__, format, ##__VA_ARGS__)
    
#define GJLOGTRACKING(format,...) GJLog_Log(getDefaultLog(),LOG_TRACKING,GJ_LOGDEBUG, __func__, format, ##__VA_ARGS__)

#define GJCLOG(dclass, level, format, ...) GJLog_Log(getDefaultLog(),(dclass), (level), __func__, format, ##__VA_ARGS__)
    
#define GJLOG(level, format, ...) GJLog_Log(getDefaultLog(),GNULL, (level), __func__, format, ##__VA_ARGS__)

#define GJAssert(isTrue, format, ...) !(isTrue)?GJLog_Log(getDefaultLog(),GNULL,(GJ_LOGFORBID),__func__, format, ##__VA_ARGS__):GNULL

#define GJ_LogHexString(level,data,len) GJLog_LogHexString(getDefaultLog(),level,data,len)

#define GJ_LogHex(level,data,len) GJLog_LogHex(getDefaultLog(),level,data,len)

#define GJ_LogFlush() GJLog_LogFlush(getDefaultLog())

#else
    
#define GJLOGTRACKING(...)
#define GJCLOG(dclass, level, format, ...)
#define GJLOG(level, format, ...)
#define GJOLOG(switch, level, format, ...)
#define GJLOGFREQ(level, format, ...)
#define GJAssert(isTrue, format, ...)
#define GJ_LogHexString(level,data,len)
#define GJLog_LogHex(level,data,len)
#endif
    
    
#ifdef __cplusplus
}
#endif

#endif
