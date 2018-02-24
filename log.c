/* 
 *  Copyright (c) 2008 Texas Instruments. All rights reserved.
 *  This program and the accompanying materials are made available under the
 *  terms of the Eclipse Public License v1.0 and Eclipse Distribution License
 *  v. 1.0 which accompanies this distribution. The Eclipse Public License is
 *  available at http://www.eclipse.org/legal/epl-v10.html and the Eclipse
 *  Distribution License is available at
 *  http://www.eclipse.org/org/documents/edl-v10.php.
 *
 *  Contributors:
 *      Texas Instruments - initial implementation
 * */
/*
 *  ======== Log.c ========
 */
#include "log/diags.h"
#include "log/log.h"

/*
 * Conditionally set the format string depending on the width of data
 * primitives. This should be removed once System_printf supports
 * 32-bit format strings
 */
//#if (xdc_target__bitsPerChar * xdc_target__sizeof_Int) == 32
//#define SERIAL "#%010u "
//#define HI "%0.8x:"
//#define LO "%0.8x] "
//#elif (xdc_target__bitsPerChar * xdc_target__sizeof_Long) == 32
//#define SERIAL "#%010lu "
//#define HI "%0.8lx:"
//#define LO "%0.8lx] "
//#else
//#error xdc.runtime.Log does not support this target.
//#endif


static const Log_Callback *Log_CallbackPointer=NULL;
static uint32_t Log_Event_All = 0;

/*
 *  ======== doPrint ========
 */
void Log_doPrint(Log_EventRec *er)
{

}

void Log_InitCallback(const Log_Callback *p)
{
	Log_CallbackPointer = p;
}

const Log_Callback *Log_GetCallback(void)
{
	return Log_CallbackPointer;
}

DiagsMask Log_getMask(void){
	return (DiagsMask)Log_Event_All & 0x0000ffff;
}

void Log_setMask(DiagsMask mask){
	Log_Event_All = (Log_Event_All & 0xffff0000) | mask;
}

/*
 *  @(#) xdc.runtime; 2, 1, 0,0; 5-10-2017 08:13:20; /db/ztree/library/trees/xdc/xdc-D13/src/packages/
 */

