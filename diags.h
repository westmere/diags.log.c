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

#ifndef DIAGS_H_
#define DIAGS_H_

#ifdef __cplusplus
#define __extern extern "C"
#else
#define __extern extern
#endif


/*
 * ======== INCLUDES ========
 */

#include <stdint.h>

/*
 * ======== AUXILIARY DEFINITIONS ========
 */

/* DiagsMask */
typedef uint16_t DiagsMask;

/* ENTRY */
#define Diags_ENTRY (0x0001)

/* EXIT */
#define Diags_EXIT (0x0002)

/* LIFECYCLE */
#define Diags_LIFECYCLE (0x0004)

/* INTERNAL */
#define Diags_INTERNAL (0x0008)

/* ASSERT */
#define Diags_ASSERT (0x0010)

/* STATUS */
#define Diags_STATUS (0x0080)

/* LEVEL */
#define Diags_LEVEL (0x0060)

/* USER1 */
#define Diags_USER1 (0x0100)

/* USER2 */
#define Diags_USER2 (0x0200)

/* USER3 */
#define Diags_USER3 (0x0400)

/* USER4 */
#define Diags_USER4 (0x0800)

/* USER5 */
#define Diags_USER5 (0x1000)

/* USER6 */
#define Diags_USER6 (0x2000)

/* USER7 */
#define Diags_USER7 (0x4000)

/* INFO */
#define Diags_INFO (0x4000)

/* USER8 */
#define Diags_USER8 (0x8000)

/* ANALYSIS */
#define Diags_ANALYSIS (0x8000)

/* ALL */
#define Diags_ALL (0xFF9F)

/* ALL_LOGGING */
#define Diags_ALL_LOGGING (0xFF9F & (~0x0010) & (~0x0008))

/* EventLevel */
enum Diags_EventLevel {
    Diags_LEVEL1 = 0x0,
    Diags_LEVEL2 = 0x20,
    Diags_LEVEL3 = 0x40,
    Diags_LEVEL4 = 0x60
};
typedef enum Diags_EventLevel Diags_EventLevel;

/* EMERGENCY */
#define Diags_EMERGENCY (Diags_LEVEL1)

/* CRITICAL */
#define Diags_CRITICAL (Diags_LEVEL2)

/* ERROR */
#define Diags_ERROR (Diags_LEVEL3)

/* WARNING */
#define Diags_WARNING (Diags_LEVEL4)


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
 *  ======== xdc_runtime_Diags_query ========
 *  Returns true iff:
 *      1. the current module's included diags intersect evt's mask, and
 *      2. either the permanently enabled diags intersect evt's mask or
 *         the runtime controllable diags intersect evt's mask.
 *
 *  This macro relies on three "internal" macros which are defined in each
 *  module's internal header (e.g., package/internal/System.xdc.h):
 *      Module__DGSINCL - a const bit mask of bits that are _not_ ALWAYS_OFF
 *      Module__DGSENAB - a const bit mask of bits that are ALWAYS_ON
 *      Module__DGSMASK - a const pointer to a bit mask of currently enabled
 *                        diagnostics
 *  These macros reference module-specific variables generated at config
 *  time, when we know the value of these constants.
 *
 */
#ifndef Diags_Mask
#define Diags_query(evt)	(evt)
#else
#define Module__DGSMASK Diags_Mask
#define Diags_query(evt) \
   ((Module__DGSMASK) & (evt))
#endif

/*
 *  ======== Diags_getLevel ========
 *  Returns the event level set in the given diags mask. The level is a value
 *  stored using two bits of the diags mask.
 */
#define Diags_getLevel(mask) \
    (Diags_LEVEL & (mask))

/*
 *  ======== Diags_compareLevels ========
 *  The definition of the diags levels assigns the value '0' to the highest
 *  priority events and '3' to the lowest, so the comparison is done backwards.
 *  For example, for (LEVEL4 (0), LEVEL1 (3)) this must return false.
 */
#define Diags_compareLevels(levelA, levelB) \
    ((levelA) > (levelB))

/*
 * ======== SYSTEM FUNCTIONS ========
 */


/*
 * ======== EPILOGUE ========
 */

#endif /* DIAGS_H_ */
