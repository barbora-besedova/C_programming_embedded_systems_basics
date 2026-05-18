/**
 @file    stime.c
 @author  Barbora Besedova, Mira Kilani
 @version 01
 @date    17.04.2026
 
 @brief     Module providing the number of milliseconds since it has been initialized
*/


// Do not write above this line (except comments)!
/* SECTION 1: Included header files to compile this file           */
#include "stime.h"
#include "stick.h"


/* SECTION 2: Private macros                                       */


/* SECTION 3: Private types                                        */


/* SECTION 4: Public variables  :: definitions, no extern 
   (must match declarations in header file)                        */


/* SECTION 5: Private variables :: definitions, static mandatory 
  (no need to declare, definitions include declarations)           */
/**
 @brief Number of milliseconds since initilization
 */
static uint64_t ms;


/**
 @brief Timed execution period (in milliseconds)
 */
static uint32_t timed_exec_period;


/**
 @brief Count to determine if the timed execution period has been reached
 */
static uint32_t timed_exec_count;


/* SECTION 6: Private functions :: declarations, static mandatory
   Rule exception (ISRs)        :: declarations, no static         */


/* SECTION 7: Private functions :: definitions, static mandatory
   Rule exception (ISRs)        :: definitions, no static 
   Public functions             :: definitions, no extern
   Function definitions (private & public) written in any order    */

void stickCallback(void){
    ms++;
    if (timed_exec_period == 0){
        timed_exec_count = 0;
    }
    else{
        timed_exec_count++;
        if (timed_exec_count == timed_exec_period){
            timed_exec_count = 0;
            stimeCallback();
        }
    }
}


//public functions

/**
 @brief Initialize the module
 */
void stimeInit(uint32_t clkHz){
    ms = 0;
    timed_exec_period = 0;
    timed_exec_count = 0;
    stickStop();
    stickClearIntFlag();
    stickSetPeriod(clkHz / 1000);
    stickEnableInt();
    stickStart();
}


/**
 @brief Return the number of elapsed milliseconds since the module was initialized
 */
uint64_t stimeElapsedMillis(void){
    uint64_t new_ms;
    stickDisableInt();
    new_ms = ms;
    stickEnableInt();
    return new_ms;
}


/**
 @brief Wait a number of milliseconds
 */
void stimeWaitMillis(uint32_t millis){
    uint64_t k, t0;

    t0 = stimeElapsedMillis();
    k = t0 + millis;
    do
    {
        /*empty loop*/
    }
    while (stimeElapsedMillis() < k);
}


void stimeCallback(void) __attribute__ (( weak ));
void stimeCallback(void)
{
    /* Empty function */
}


/**
 @brief Configure the execution period of the stimeCallback()
 */
void stimeTimedExecMillis(uint32_t millis)
{
    stickDisableInt();
    timed_exec_period = millis;
    timed_exec_count = 0;
    stickEnableInt();
}


