/**
 @file    stime.h
 @author  Barbora Besedova, Mira Kilani
 @version 01
 @date    17.04.2026
 
 @brief    Module providing the number of milliseconds since it has been initialized
 */

#ifndef STIME_H
#define STIME_H

/* SECTION 1: Included header files required to compile this file  */
#include <stdint.h>


/* SECTION 2: Public macros                                        */


/* SECTION 3: Public types                                         */


/* SECTION 4: Public variables :: declarations, extern mandatory   */


/* SECTION 5: Public functions :: declarations, extern optional
   Rule exception (callbacks)  :: declarations, extern recommended */
/**
 @brief Initialize the module
 */
void stimeInit(uint32_t clkHz);


/**
 @brief Return the number of elapsed milliseconds since the module was initialized
 */
uint64_t stimeElapsedMillis(void);


/**
 @brief Wait a number of milliseconds
 */
void stimeWaitMillis(uint32_t millis);


/**
 @brief Callback to stime module
 */
extern void stimeCallback(void);


/**
 @brief Configure the execution period of the stimeCallback()
 */
void stimeTimedExecMillis(uint32_t millis);


#endif // STIME_H
