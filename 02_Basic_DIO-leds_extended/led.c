/**
 @file    led.c
 @author  Barbora Besedova, Mira Kilani
 @version 01
 @date    21.03.2026
 
 @brief   LEDs management for the msp432p401r Launchpad board
 */



/* SECTION 1: Included header files to compile this file           */
#include "common.h"
#include "led.h"


/* SECTION 2: Private macros                                       */

/**
 @brief Macro to automatically calculate the number of entries in the @sa _ledsPinRefs array
 */
#define NUM_LEDS 	ARRAY_SIZE(_ledPinRefs)


/* SECTION 3: Private types                                        */


/* SECTION 4: Public variables  :: definitions, no extern 
 (must match declarations in header file)                        */


/* SECTION 5: Private variables :: definitions, static mandatory 
 (no need to declare, definitions include declarations)           */

/**
 @brief Private array of pin references for leds on the board
 
 @remark This is the only element that should be adapted to
 accommodate a different number of LEDs in the board, 
 or LEDs located at different pins/ports.
 */
static output_pin_t _ledPinRefs [] = {
    {.mask = BIT0, .port_is_odd = 1 , .odd = P1}, // LED0 P1 .0
    {.mask = BIT0, .port_is_odd = 0 , .even = P2}, // LED1_RED P2 .0
    {.mask = BIT1, .port_is_odd = 0 , .even = P2}, // LED1_GREEN P2.1
    {.mask = BIT2, .port_is_odd = 0 , .even = P2}, // LED1_BLUE P2 .2
    {.mask = BIT6, .port_is_odd = 0 , .even = P2}, // LED2_RED P2 .6
    {.mask = BIT4, .port_is_odd = 0 , .even = P2}, // LED2_GREEN P2 .4
    {.mask = BIT6, .port_is_odd = 1 , .odd = P5} // LED2_BLUE P5 .6
};


/* SECTION 6: Private functions :: declarations, static mandatory
 Rule exception (ISRs)        :: declarations, no static         */
static void _ledInitOdd(DIO_PORT_Odd_Interruptable_Type *port, uint8_t mask);

static void _ledInitEven(DIO_PORT_Even_Interruptable_Type *port, uint8_t mask);

static void _ledInit(output_pin_t *pin);


/* SECTION 7: Private functions :: definitions, static mandatory
 Rule exception (ISRs)        :: definitions, no static
 Public functions             :: definitions, no extern
 Function definitions (private & public) written in any order    */

//private functions
static void _ledInitOdd(DIO_PORT_Odd_Interruptable_Type *port, uint8_t mask)
{
    port->DIR = port->DIR | mask; //set as output
    port->SEL0 = port->SEL0 & ~(mask);
    port->SEL1 = port->SEL1 & ~(mask);
    port->DS = port->DS & ~(mask);
}


static void _ledInitEven(DIO_PORT_Even_Interruptable_Type *port, uint8_t mask)
{
    port->DIR = port->DIR | mask;
    port->SEL0 = port->SEL0 & ~(mask);
    port->SEL1 = port->SEL1 & ~(mask);
    port->DS = port->DS & ~(mask);
}


static void _ledInit(output_pin_t *pin)
{
    if (pin->port_is_odd == 1)
    {
        _ledInitOdd(pin->odd, pin->mask);
    }
    else
    {
        _ledInitEven(pin->even, pin->mask);
    }
}


//public functions

void ledsInit(void)
{
    int i;
    for (i = 0; i <= (NUM_LEDS - 1); i++)
    {
        _ledInit(&_ledPinRefs[i]);
        ledOff(i);
    }
}


int ledsGetNum(void)
{
    return NUM_LEDS;
}


int ledOn(int which_led)
{
    if ((which_led < 0) || (which_led > (NUM_LEDS - 1)))
    {
        return -1;
    }
    else
    {
        if ((_ledPinRefs[which_led].port_is_odd) == 1)
        {
            _ledPinRefs[which_led].odd->OUT = _ledPinRefs[which_led].odd->OUT
                    | _ledPinRefs[which_led].mask;
        }
        else
        {
            _ledPinRefs[which_led].even->OUT = _ledPinRefs[which_led].even->OUT
                    | _ledPinRefs[which_led].mask;

        }
        return 1;
    }
}


int ledOff(int which_led)
{
    if ((which_led < 0) || (which_led > (NUM_LEDS - 1)))
    {
        return -1;
    }
    else
    {
        if ((_ledPinRefs[which_led].port_is_odd) == 1)
        {
            _ledPinRefs[which_led].odd->OUT = _ledPinRefs[which_led].odd->OUT
                    & ~_ledPinRefs[which_led].mask;
        }
        else
        {
            _ledPinRefs[which_led].even->OUT = _ledPinRefs[which_led].even->OUT
                    & ~_ledPinRefs[which_led].mask;

        }
        return 1;
    }
}


int ledToggle(int which_led)
{
    if ((which_led < 0) || (which_led > (NUM_LEDS - 1)))
    {
        return -1;
    }
    else
    {
        if (ledGet(which_led) == 0)
        {
            ledOn(which_led);
        }
        else
        {
            ledOff(which_led);
        }
        return 1;
    }
}


int ledGet(int which_led)
{
    if ((which_led < 0) || (which_led > (NUM_LEDS - 1)))
    {
        return -1;
    }
    else
    {
        if ((_ledPinRefs[which_led].port_is_odd) == 1)
        {

            if ((_ledPinRefs[which_led].odd->OUT & _ledPinRefs[which_led].mask) != 0x00)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            if ((_ledPinRefs[which_led].even->OUT & _ledPinRefs[which_led].mask) != 0x00)
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }
}



