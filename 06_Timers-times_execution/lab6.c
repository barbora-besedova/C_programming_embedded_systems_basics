/**
 @file    lab6.c
 @author  Barbora Besedova, Mira Kilani
 @version 01
 @date    06.04.2026

 @brief   Timed wait application using the led and stime modules
 */


#include "stime.h"
#include "led.h"
#include "common.h"
#include "driverlib.h"


void stimeCallback(void){
    ledToggle(LED1_RED);
    ledToggle(LED1_GREEN);
    ledToggle(LED1_BLUE);
}


void main(void){
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

    uint32_t clkHz;
    clkHz = 3000000; //from my observation: for real time 1 second better works 1.5MHz,but instructions says 3MHz
    ledsInit();
    stimeInit(clkHz);
    stimeTimedExecMillis(1000);
    Interrupt_enableMaster();

    while (1){
        ledOn(LED0);
        stimeWaitMillis(1000);
        ledOff(LED0);
        stimeWaitMillis(2000);
    }
}
