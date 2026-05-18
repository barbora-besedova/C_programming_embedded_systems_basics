/**
 @file    main.c
 @author  Barbora Besedova, Mira Kilani copied by Paco Rodríguez
 @version 0.1
 @date    06/03/2026

 @brief   Main function calling the defined functions
*/

#include "common.h"
#include "led.h"

int main(void)
{
    volatile uint32_t i;
    WDT_A->CTL = WDT_A_CTL_PW | // Stop WDT
            WDT_A_CTL_HOLD;
    ledsInit();
    while (1) // continuous loop
    {
        if (ledToggle(LED0) < 0)
        { // Blink LED
            while (1);
        }
        for ( i = 20000; i > 0; i--); // Delay
        if (ledToggle(LED0) < 0)
        { // Blink LED
            while (1);
        }
        for ( i = 2000000; i > 0; i--); // Delay
        if (ledOn(LED0) < 0)
        { // Switch LED on
            while (1);
        }
        for ( i = 20000; i > 0; i--); // Delay
        if (ledOff(LED0) < 0)
        { // Switch LED off
            while (1);
        }
    for ( i = 20000; i > 0; i--); // Delay
}
}
