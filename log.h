/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-D13
 */

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     PROLOGUE
 *     INCLUDES
 *     
 *     INTERNAL DEFINITIONS
 *     MODULE-WIDE CONFIGS
 *     FUNCTION DECLARATIONS
 *     SYSTEM FUNCTIONS
 *     
 *     EPILOGUE
 *     STATE STRUCTURES
 *     PREFIX ALIASES
 */


/*
 * ======== PROLOGUE ========
 */

#ifndef LOG_H_
#define LOG_H_

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif


/*
 * ======== INCLUDES ========
 */

#include <stdint.h>
#include <time.h>

/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/*
 *  ======== xdc_runtime_Log_Event ========
 *  Log_Event is an encoded type.  Log Events are encoded on the target as
 *  a 32-bit value:
 *
 *      | format rope | module ID or mask |
 *      | 31 ----- 16 | 15 ------------ 0 |
 *
 *  The lower 16-bits contain either a mask or a module ID; when the event
 *  is statically declared this field has a mask, when the event is passed
 *  to an ILogger this field is the module ID of the module that generated
 *  the event.
 *
 *  The upper 16-bits are an ID (rope) that that identifies the format
 *  string to use to render the event (and its arguments).
 */
typedef uint32_t Log_Event;

/* Event */
typedef uint32_t Log_Event;

typedef uint32_t Log_Timestamp;

/* EventId */
typedef Log_Event Log_EventId;

/* RopeId */
typedef uint16_t Log_RopeId;

typedef struct Log_EventRec {
	Log_Timestamp tstamp;
    uint32_t serial;
    Log_Event evt;
    void *arg;
}Log_EventRec;

typedef int (*Log_CallbackPrintf)(const char *fmt, ...);
typedef uint32_t (*Log_GetSerial)(void);
typedef uint32_t (*Log_GetSysUptime)(void);
typedef time_t (*Log_GetTimeStamp)(struct tm *tm);

typedef struct Log_Callback{
	Log_CallbackPrintf printf;
	Log_GetSerial serial;
	Log_GetSysUptime sysuptime;
	Log_GetTimeStamp timestamp;
}Log_Callback;

/*
 * ======== INTERNAL DEFINITIONS ========
 */


/*
 * ======== MODULE-WIDE CONFIGS ========
 */


/*
 * ======== FUNCTION DECLARATIONS ========
 */

/*
 *  ======== Log_getMask ========
 */
//#define Log_getMask(evt) ((DiagsMask)((evt) & 0x0000ffff))

/*
 *  ======== Log_getRope ========
 */
#define Log_getRope(evt) ((Log_RopeId)((evt) >> 16))

/*
 *  ======== Log_getEventId ========
 */
#define Log_getEventId(evt) \
    ((Log_EventId)((evt) >> 16))


#ifndef Log_DISABLE_ALL
#ifndef Log_ENABLE_INFO
//#define Log_ENABLE_INFO
#endif
#ifndef Log_ENABLE_ERROR
//#define Log_ENABLE_ERROR
#endif
#ifndef Log_ENABLE_DIAG_COLOR
//#define Log_ENABLE_DIAG_COLOR
#endif
#ifndef Log_ENABLE_SEQUENCEID
//#define Log_ENABLE_SEQUENCEID	// sequenceId
#endif
#ifndef Log_ENABLE_SYSUPTIME
#define Log_ENABLE_SYSUPTIME	// sysUpTime
#ifndef Log_ENABLE_TIMESTAMP
//#define Log_ENABLE_TIMESTAMP	// timestamp
#endif
#endif

#ifndef Log_FILE
#define Log_FILE	__FILE__
#endif

#ifndef Log_LINE
#define Log_LINE	__LINE__
#endif

#ifndef Log_EOL
#define Log_EOL "\r\n"
#endif

#define _STRINGIFY(x) #x
#define STRINGIFY(x) _STRINGIFY(x)

#ifdef Log_ENABLE_DIAG_COLOR
#define Log_DIAG_COLOR_RED		"\033[31m"      /* Red */
#define Log_DIAG_COLOR_GREEN	"\033[32m"      /* Green */
#define Log_DIAG_COLOR_RESET	"\033[0m"
#else
#define Log_DIAG_COLOR_RED
#define Log_DIAG_COLOR_GREEN
#define Log_DIAG_COLOR_RESET
#endif	// #ifdef Log_ENABLE_DIAG_COLOR

#define Log_doPrintf(mask,fmt,args...)	\
do{	\
	const Log_Callback *callback=Log_GetCallback();	\
	if(callback && Diags_query(mask) & Log_getMask())	\
		callback->printf(fmt, ## args);	\
}while(0)


#ifdef Log_ENABLE_SEQUENCEID
#define Log_ENABLE_SEQUENCEID_fmt	"#%06u"
#define Log_ENABLE_SEQUENCEID_arg	callback->serial()
#define Log_Printf0(mask,fmt,args...)	\
do{	\
	const Log_Callback *callback=Log_GetCallback();	\
	if(callback)	\
	{	\
		if(callback->serial)	\
			Log_doPrintf(mask,Log_ENABLE_SEQUENCEID_fmt " " fmt Log_EOL, Log_ENABLE_SEQUENCEID_arg, ## args);	\
		else	\
			Log_doPrintf(mask,fmt Log_EOL, ## args);	\
	}	\
}while(0)
#else
#define Log_Printf0(mask,fmt,args...)	\
		Log_doPrintf(mask,fmt Log_EOL, ## args)
#endif	// #ifdef Log_ENABLE_SEQUENCEID

#ifdef Log_ENABLE_SYSUPTIME
#define Log_ENABLE_SYSUPTIME_fmt	"[ %06u.%03u ]"
#define Log_ENABLE_SYSUPTIME_arg	callback->sysuptime()/1000,callback->sysuptime()%1000
#define Log_Printf1(mask,fmt,args...)	\
do{	\
	const Log_Callback *callback=Log_GetCallback();	\
	if(callback)	\
	{	\
		if(callback->sysuptime)	\
			Log_Printf0(mask,Log_ENABLE_SYSUPTIME_fmt " " fmt, Log_ENABLE_SYSUPTIME_arg, ## args);	\
		else	\
			Log_Printf0(mask,fmt, ## args);	\
	}	\
}while(0)
#else
#ifdef Log_ENABLE_TIMESTAMP
#define Log_Printf1(mask,fmt,args...)	\
do{	\
	struct Log_Callback *callback=Log_GetCallback();	\
	if(callback)	\
	{	\
		if(callback->timestamp)	\
		{	\
			char time_str[25];	\
			struct tm tm;		\
			callback->timestamp(&tm);	\
			strftime(time_str, sizeof(time_str), "%c", &tm);	\
			Log_Printf0(mask,"%s " fmt, time_str, ## args);	\
		}	\
		else	\
		{	\
			Log_Printf0(mask,fmt, ## args);	\
		}	\
	}	\
}while(0)
#else
#define Log_Printf1(mask,fmt,args...)	\
		Log_Printf0(mask,fmt, ## args)
#endif	// #ifdef Log_ENABLE_TIMESTAMP
#endif	// #ifdef Log_ENABLE_SYSUPTIME

#define Log_dPrintf(mask,diags,color,fmt,args...)	\
		Log_Printf1(mask,color diags Log_DIAG_COLOR_RESET " (" Log_FILE ":" STRINGIFY(Log_LINE) ") " fmt, ## args)

// Log_printf
#define Log_printf(fmt,args...)	Log_doPrintf(Diags_CRITICAL | Diags_STATUS,fmt, ##args)

// Log_info
#ifdef Log_ENABLE_INFO
#define Log_info(fmt,args...)   Log_dPrintf(Diags_STATUS | Diags_INFO,"INFO: ",Log_DIAG_COLOR_GREEN,fmt, ##args)
#else
#define Log_info(fmt,args...)
#endif	// #ifdef Log_ENABLE_INFO

// Log_error
#ifdef Log_ENABLE_ERROR
#define Log_error(fmt,args...)   Log_dPrintf(Diags_STATUS | Diags_ERROR,"ERROR:",Log_DIAG_COLOR_RED,fmt, ##args)
#else
#define Log_error(fmt,args...)
#endif	// #ifdef Log_ENABLE_ERROR
#else
#define Log_info(fmt,args...)
#define Log_error(fmt,args...)
#endif // Log_DISABLE_ALL

/*
 * ======== SYSTEM FUNCTIONS ========
 */

const Log_Callback *Log_GetCallback(void);

void Log_InitCallback(const Log_Callback *p);

DiagsMask Log_getMask(void);
void Log_setMask(DiagsMask mask);

/*
 * ======== EPILOGUE ========
 */

#endif /* LOG_H_ */
