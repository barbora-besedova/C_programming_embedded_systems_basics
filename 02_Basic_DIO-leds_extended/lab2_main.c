/**
 @file    lab2_main.c
 @author  Barbora Besedova, Mira Kilani
 @version 01
 @date    21.03.2026
 **/

#include "common.h"
#include "led.h"

int main(void) {
    volatile uint32_t i;
    int n, l;

    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;        // Stop WDT
    
    // Initialize the led module and get the number of available LEDs
    ledsInit();
    n = ledsGetNum();
    
    while (1)                               // superloop
    {
        /* Toggle all LEDs using a loop */
        for (l=0; l < n; l++) {
            if (!ledToggle(l)) {                // Toggle LED l
                while(1);
            }
            for (i = 20000; i > 0; i--);        // Delay after each LED
        }
        /* Check LED status is correct  for all LEDs */
        for (l=0; l < n; l++) {
            if (ledGet(l) != 1) {
                while(1);
            }
        }

        /* Toggle all LEDs using a loop */
        for (l=0; l < n; l++) {
            if (!ledToggle(l)) {                // Toggle LED l
                while(1);
            }
            for (i = 20000; i > 0; i--);        // Delay after each LED
        }
        /* Check LED status is correct  for all LEDs */
        for (l=0; l < n; l++) {
            if (ledGet(l) != 0) {
                while(1);
            }
        }
        

        /* Switch on all LEDs using a loop */
        for (l=0; l < n; l++) {
            if (!ledOn(l)) {                    // Switch LED l on
                while(1);
            }
            for (i = 20000; i > 0; i--);        // Delay after each LED
        }
        /* Check LED status is correct  for all LEDs */
        for (l=0; l < n; l++) {
            if (ledGet(l) != 1) {
                while(1);
            }
        }
        
        /* Switch off all LEDs using a loop */
        for (l=0; l < n; l++) {
            if (!ledOff(l)) {                   // Switch LED l off
                while(1);
            }
            for (i = 20000; i > 0; i--);        // Delay after each LED
        }
        /* Check LED status is correct  for all LEDs */
        for (l=0; l < n; l++) {
            if (ledGet(l) != 0) {
                while(1);
            }
        }
    }
}

