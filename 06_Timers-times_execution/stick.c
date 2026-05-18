/**
 @file    stick.c
 @author  Barbora Besedova, Mira Kilani
 @version 01
 @date    06.04.2026
 
 @brief   Basic module to manage the SysTick timer
 */

// Do not write above this line (except comments)!
/* SECTION 1: Included header files to compile this file           */
#include "common.h"
#include "stick.h"


/* SECTION 2: Private macros                                       */


/* SECTION 3: Private types                                        */


/* SECTION 4: Public variables  :: definitions, no extern 
   (must match declarations in header file)                        */


/* SECTION 5: Private variables :: definitions, static mandatory 
  (no need to declare, definitions include declarations)           */


/* SECTION 6: Private functions :: declarations, static mandatory
   Rule exception (ISRs)        :: declarations, no static         */

/**
@brief SysTick interrupt handler
*/
void SysTick_Handler(void);


/* SECTION 7: Private functions :: definitions, static mandatory
   Rule exception (ISRs)        :: definitions, no static 
   Public functions             :: definitions, no extern
   Function definitions (private & public) written in any order    */

//private functions

/**
@brief SysTick interrupt handler
*/
void SysTick_Handler(void){
    stickClearIntFlag();
    stickCallback();
}


//public functions

void stickCallback ( void ) __attribute__ (( weak ));
void stickCallback ( void )
{
/* Empty function */
}


/**
 @brief Start the timer setting the ENABLE bit
 */
void stickStart(void){
    SysTick -> CTRL |= ( SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk );
}


/**
 @brief Stop the timer clearing the ENABLE bit
 */
void stickStop(void){
    SysTick -> CTRL &= ~ SysTick_CTRL_ENABLE_Msk ;
}


/**
@brief Determine if the timer is counting analyzing the ENABLE bit
 */
uint32_t stickIsStarted(void){
    return ( SysTick -> CTRL & SysTick_CTRL_ENABLE_Msk ) >> SysTick_CTRL_ENABLE_Pos ;
}


/**
 @brief Enable timer interrupts setting the TICKINT bit
 */
void stickEnableInt(void){
    SysTick -> CTRL |= SysTick_CTRL_TICKINT_Msk ;
}


/**
@brief Disable timer interrupts clearing the TICKINT bit
*/
void stickDisableInt(void){
    SysTick -> CTRL &= ~ SysTick_CTRL_TICKINT_Msk ;
}


/**
 @brief Determine whether timer interrupts are enabled analyzing the TICKINT bit.
 */
uint32_t stickIsIntEnabled(void){
    return ( SysTick -> CTRL & SysTick_CTRL_TICKINT_Msk ) >> SysTick_CTRL_TICKINT_Pos;
}


/**
 @brief Set the timer period writing p-1 into the STRVR register
 */
void stickSetPeriod(uint32_t p){
    SysTick -> LOAD = ((p -1) & SysTick_LOAD_RELOAD_Msk );
}


/**
 @brief Timer period
 Return p + 1, being p the STRVR register
 */
uint32_t stickGetPeriod(void){
    return (( SysTick -> LOAD & SysTick_LOAD_RELOAD_Msk ) + 1) ;
}


/**
 @brief Current timer count.
Return c, being c the STCVR register
 */
uint32_t stickGetCount(void){
    return ( SysTick -> VAL & SysTick_VAL_CURRENT_Msk );
}


/**
 @brief Clear the timer interrupt flag, clearing the COUNTFLAG bit
 */
void stickClearIntFlag(void){
    SysTick -> CTRL &= ~ SysTick_CTRL_COUNTFLAG_Msk ;
}


/**
 @brief Determine whether the timer interrupt flag is set analyzing the COUNTFLAG bit.
Return 1 if the flag is set, 0 otherwise.
 */
uint32_t stickIsIntFlagActive(void){
    return ( SysTick -> CTRL & SysTick_CTRL_COUNTFLAG_Msk ) >> SysTick_CTRL_COUNTFLAG_Pos ;
}
