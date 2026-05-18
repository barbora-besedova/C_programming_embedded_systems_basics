/**
 @file    lab4.c
 @author  Paco Rodriguez
 @version 1.0
 @date    Spring 2021
 
 changed by
 @author  Barbora Besedová, Mira Kilani
 @version 1.0
 @date 1.4.2026

 @brief   Simple code to test buttons managed using polling
*/

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "led.h"
#include "button.h"

/* callback function called from GPIO 's interrupt handlers
*/
extern void buttonCallback(int which_button){
    if(which_button==BUTTON1){
        ledToggle(LED2_RED);
    }
    else{
        if(which_button==BUTTON2){
            ledToggle(LED2_BLUE);
            ledToggle(LED2_GREEN);
        }
    }
}

int main(void) {
    volatile uint32_t i;
    int res;

    /* Stop Watchdog  */
    MAP_WDT_A_holdTimer();

   	/* Initialize the led and button modules */
    ledsInit();
    buttonsInit();
	
	/* Enable interrupts in the application  */
	Interrupt_enableMaster();
   	
	/* Superloop: react to polling-based buttons */
    while (1)
    {
		res = buttonState(BUTTON0);
		if (res < 0) {
			while(1);
		}
		if (res == 1) {
			ledOn(LED0);
		} else {
			ledOff(LED0);
		}

		res = buttonPressed(BUTTON3);
		if (res < 0) {
			while(1);
		}
		if (res == 1) {
			do {
				ledToggle(LED1_RED);
				ledToggle(LED1_GREEN);
				ledToggle(LED1_BLUE);
				for (i = 20000; i > 0; i--);
				res = buttonPressed(BUTTON3);
				if (res < 0) {
					while(1);
				}
			} while (res == 0);
		}
    }
}
