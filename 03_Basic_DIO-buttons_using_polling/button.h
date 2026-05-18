/**
 @file    button.h
 @author  Barbora Besedova, Mira Kilani
 @version 01
 @date    26.3.2026
 
 @brief   buttons management for the msp432p401r Launchpad board

*/

// Do not write above this line (except comments)!
#ifndef BUTTON_H
#define BUTTON_H

/* SECTION 1: Included header files required to compile this file  */


/* SECTION 2: Public macros                                        */
/**
@brief Button designators
*/
#define BUTTON0 0
#define BUTTON1 1
#define BUTTON2 2
#define BUTTON3 3


/* SECTION 3: Public types                                         */


/* SECTION 4: Public variables :: declarations, extern mandatory   */


/* SECTION 5: Public functions :: declarations, extern optional
   Rule exception (callbacks)  :: declarations, extern recommended */
/**
@brief Initialization function
*/
void buttonsInit(void);


/**
@brief Get the current button state
*/
int buttonState(int which_button);


/**
 @brief Determine if the button has been pressed
since the last time this function was called
 */
int buttonPressed(int which_button);


#endif // BUTTON_H

