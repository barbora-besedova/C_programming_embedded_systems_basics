/**
 @file    button.h
 @author  Barbora Besedova, Mira Kilani
 @version 02
 @date    01.04.2026
 
 @brief   buttons management for the msp432p401r Launchpad board
 */


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

/**
@brief  value seting the debounce threshold time on 100 ms
 */
#define BUTTON_DEBOUNCE_MS 100

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


/**
 @brief Callback function called from GPIO 's interrupt handlers
 */
extern void buttonCallback(int which_button);


#endif // BUTTON_H

