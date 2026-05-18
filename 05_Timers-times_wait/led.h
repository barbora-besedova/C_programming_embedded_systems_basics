/**
 @file    led.h
 @author  Barbora Besedova, Mira Kilani
 @version 01
 @date    17.04.2026

 @brief   LEDs management for the msp432p401r Launchpad board

 */
#ifndef LED_H	//
#define LED_H	//


/* SECTION 1: Included header files required to compile this file  */


/* SECTION 2: Public macros                                        */
#define LED0 0
#define LED1_RED 1
#define LED1_GREEN 2
#define LED1_BLUE 3
#define LED2_RED 4
#define LED2_GREEN 5
#define LED2_BLUE 6


/* SECTION 3: Public types                                         */


/* SECTION 4: Public variables :: declarations, extern mandatory   */


/* SECTION 5: Public functions :: declarations, extern optional
 Rule exception (callbacks)  :: declarations, extern recommended */
void ledsInit(void);


int ledsGetNum(void);


int ledOn(int which_led);


int ledOff(int which_led);


int ledToggle(int which_led);


int ledGet(int which_led);


#endif // LED_H	//
