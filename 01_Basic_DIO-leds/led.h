/**
 @file    led.h
 @author  Barbora Besedova, Mira Kilani
 @version 02
 @date    05.03.2026
 


 @brief   LEDs management for the msp432p401r Launchpad board

 */
// Do not write above this line (except comments)!
#ifndef LED_H	//
#define LED_H	//



/* SECTION 1: Included header files required to compile this file  */



/* SECTION 2: Public macros                                        */
#define LED0		0



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
// Do not write below this line!

