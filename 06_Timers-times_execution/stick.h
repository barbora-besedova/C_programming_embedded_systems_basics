/**
 @file    stick.h
 @author  Barbora Besedová,  Mira Kilani
 @version 01
 @date    06.04.2026
 
 @brief   Basic module to manage the SysTick timer
*/


#ifndef STICK_H
#define STICK_H


/* SECTION 1: Included header files required to compile this file  */
#include <stdint.h>


/* SECTION 2: Public macros                                        */


/* SECTION 3: Public types                                         */


/* SECTION 4: Public variables :: declarations, extern mandatory   */


/* SECTION 5: Public functions :: declarations, extern optional
   Rule exception (callbacks)  :: declarations, extern recommended */

/**
 @brief callback function called from the timer interrupt handler
 */
extern void stickCallback (void);


/**
 @brief Start the timer setting the ENABLE bit
 */
void stickStart(void);


/**
 @brief Stop the timer clearing the ENABLE bit
 */
void stickStop(void);


/**
@brief Determine if the timer is counting analyzing the ENABLE bit
 */
uint32_t stickIsStarted(void);


/**
 @brief Enable timer interrupts setting the TICKINT bit
 */
void stickEnableInt(void);


/**
@brief Disable timer interrupts clearing the TICKINT bit
*/
void stickDisableInt(void);


/**
 @brief Determine whether timer interrupts are enabled analyzing the TICKINT bit.
 */
uint32_t stickIsIntEnabled(void);


/**
 @brief Set the timer period writing p-1 into the STRVR register
 */
void stickSetPeriod(uint32_t p);


/**
 @brief Timer period
 Return p + 1, being p the STRVR register
 */
uint32_t stickGetPeriod(void);


/**
 @brief Current timer count.
Return c, being c the STCVR register
 */
uint32_t stickGetCount(void);


/**
 @brief Clear the timer interrupt flag, clearing the COUNTFLAG bit
 */
void stickClearIntFlag(void);


/**
 @brief Determine whether the timer interrupt flag is set analyzing the COUNTFLAG bit.
Return 1 if the flag is set, 0 otherwise.
 */
uint32_t stickIsIntFlagActive(void);


#endif // STICK_H
