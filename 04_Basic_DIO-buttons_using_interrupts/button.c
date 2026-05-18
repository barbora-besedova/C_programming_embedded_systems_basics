/**
 @file    button.c
 @author  Barbora Besedová, Mira Kilani
 @version 02
 @date    01.04.2026
 
 @brief   buttons management for the msp432p401r Launchpad board
 */


/* SECTION 1: Included header files to compile this file           */
#include "button.h"
#include "ti/devices/msp432p4xx/driverlib/driverlib.h"
#include "common.h"


/* SECTION 2: Private macros                                       */


/**
 @brief Number of entries in the @sa _pinrefs array
 @note This value is automatically calculated , do not edit
 */
#define NUM_BUTTONS ARRAY_SIZE(_pinrefs)


/* SECTION 3: Private types                                        */


/* SECTION 4: Public variables  :: definitions, no extern 
 (must match declarations in header file)                        */


/* SECTION 5: Private variables :: definitions, static mandatory 
 (no need to declare, definitions include declarations)           */
/**
 @brief Private array of pin references for buttons on the board
 */
static input_pin_t _pinrefs[] =
        { { . mask = BIT1, . port_is_odd = 1, . odd = P1, //BUTTON0 P1 .1
            . use_pullup = 1, //Internal pull -up
            . int_num = INT_PORT1, . use_interrupt = 0 //Polling
        }, { . mask = BIT4, . port_is_odd = 1, . odd = P1, //BUTTON1 P1 .4
             . use_pullup = 1, //Internal pull -up
             . int_num = INT_PORT1, . use_interrupt = 1 //Interrupts
        }, { . mask = BIT1, . port_is_odd = 1, . odd = P5, //BUTTON2 P5 .1
             . use_pullup = 0, //No internal pull -up
             . int_num = INT_PORT5, . use_interrupt = 1 //Interrupts
        }, { . mask = BIT5, . port_is_odd = 1, . odd = P3, //BUTTON3 P3 .5
             . use_pullup = 0, //No internal pull -up
             . int_num = INT_PORT3, . use_interrupt = 0 // Polling
        } };


/* SECTION 6: Private functions :: declarations, static mandatory
 Rule exception (ISRs)        :: declarations, no static         */
/*
 @brief Initialization function for a single
 button
 */
static void _buttonInit(input_pin_t *ref);


/**
 @brief DIO interrupt handlers 1-6
 */
void PORT1_IRQHandler(void);
void PORT2_IRQHandler(void);
void PORT3_IRQHandler(void);
void PORT4_IRQHandler(void);
void PORT5_IRQHandler(void);
void PORT6_IRQHandler(void);


/**
 @brief Function called from a DIO ISR to process a set of flags */
static void _buttonProcessFlags(uint16_t int_num, uint8_t flags);


/**
 @brief Function to perform an inverse lookup and get
 the button designator from the pair ( int_num , mask ) */
static int _buttonInverseLookup(uint16_t int_num, uint8_t mask);


/* SECTION 7: Private functions :: definitions, static mandatory
 Rule exception (ISRs)        :: definitions, no static
 Public functions             :: definitions, no extern
 Function definitions (private & public) written in any order    */


//private functions

/**
 @brief Initialization function  for a single button
 */
static void _buttonInit(input_pin_t *ref)
{
    if ((ref->port_is_odd) == 1)
    {
        DIO_PORT_Odd_Interruptable_Type *port = ref->odd;
        port->DIR = port->DIR & ~(ref->mask);
        port->SEL1 = port->SEL1 & ~(ref->mask);
        port->SEL0 = port->SEL0 & ~(ref->mask);
        if ((ref->use_pullup) == 1)
        {
            port->REN = port->REN | ref->mask;
            port->OUT = port->OUT | ref->mask;
        }
        else
        {
            port->REN = port->REN & ~(ref->mask);
        }
        port->IES = port->IES | ref->mask;

        if ((ref->use_interrupt) == 1)
        {
            port->IE = port->IE | (ref->mask);
            port->IFG = port->IFG & ~(ref->mask);
            Interrupt_enableInterrupt(ref->int_num);
        }
        else
        {
            port->IE = port->IE & ~(ref->mask);
        }
    }
    else
    {
        DIO_PORT_Even_Interruptable_Type *port = ref->even;
        port->DIR = port->DIR & ~(ref->mask);
        port->SEL1 = port->SEL1 & ~(ref->mask);
        port->SEL0 = port->SEL0 & ~(ref->mask);
        if ((ref->use_pullup) == 1)
        {
            port->REN = port->REN | ref->mask;
            port->OUT = port->OUT | ref->mask;
        }
        else
        {
            port->REN = port->REN & ~(ref->mask);
        }
        port->IES = port->IES | ref->mask;
        if ((ref->use_interrupt) == 1)
        {
            port->IE = port->IE | (ref->mask);
            port->IFG = port->IFG & ~(ref->mask);
            Interrupt_enableInterrupt(ref->int_num);
        }
        else
        {
            port->IE = port->IE & ~(ref->mask);
        }
    }
}


/**
 @brief Function called from a DIO ISR to process a set of flags */
static void _buttonProcessFlags(uint16_t int_num, uint8_t flags)
{
    int i, mask, button;
    mask = BIT0;
    for (i = 0; i < 8; i++)
    {
        if ((flags & mask) != 0)
        {
            button = _buttonInverseLookup(int_num, mask);
            if (button >= 0)
            {
                buttonCallback(button);
            }
        }
        mask = mask << 1;
    }
}


/**
 @brief Function to perform an inverse lookup and get
 the button designator from the pair ( int_num , mask ) */
static int _buttonInverseLookup(uint16_t int_num, uint8_t mask)
{
    int i, result;
    result = -1;
    for (i = 0; i < NUM_BUTTONS; i++)
    {
        if ((_pinrefs[i].mask == mask) && (_pinrefs[i].int_num == int_num))
        {
            result = i;
            break;
        }
    }
    return result;
}


/**
 @brief DIO interrupt handlers 1-6
 */
void PORT1_IRQHandler(void)
{
    uint8_t filtered_buttons;
    filtered_buttons = P1->IFG & P1->IE;
    P1->IFG &= ~filtered_buttons;
    _buttonProcessFlags(INT_PORT1, filtered_buttons);
}


void PORT2_IRQHandler(void)
{
    uint8_t filtered_buttons;
    filtered_buttons = P2->IFG & P2->IE;
    P2->IFG &= ~filtered_buttons;
    _buttonProcessFlags(INT_PORT2, filtered_buttons);
}


void PORT3_IRQHandler(void)
{
    uint8_t filtered_buttons;
    filtered_buttons = P3->IFG & P3->IE;
    P3->IFG &= ~filtered_buttons;
    _buttonProcessFlags(INT_PORT3, filtered_buttons);
}


void PORT4_IRQHandler(void)
{
    uint8_t filtered_buttons;
    filtered_buttons = P4->IFG & P4->IE;
    P4->IFG &= ~filtered_buttons;
    _buttonProcessFlags(INT_PORT4, filtered_buttons);
}


void PORT5_IRQHandler(void)
{
    uint8_t filtered_buttons;
    filtered_buttons = P5->IFG & P5->IE;
    P5->IFG &= ~filtered_buttons;
    _buttonProcessFlags(INT_PORT5, filtered_buttons);
}


void PORT6_IRQHandler(void)
{
    uint8_t filtered_buttons;
    filtered_buttons = P6->IFG & P6->IE;
    P6->IFG &= ~filtered_buttons;
    _buttonProcessFlags(INT_PORT6, filtered_buttons);
}


//public functions

/**
 @brief Initialization function
 */
void buttonsInit(void)
{
    int i;
    for (i = 0; i < NUM_BUTTONS; i++)
    {
        _buttonInit(&_pinrefs[i]);
    }
}


/**
 @brief Get the current button state
 */
int buttonState(int which_button)
{
    int res, val;
    if ((which_button < 0) || (which_button > (NUM_BUTTONS - 1)))
    {
        res = -1;
    }
    else
    {
        if ((_pinrefs[which_button].port_is_odd) == 1)
        {
            val = _pinrefs[which_button].odd->IN & _pinrefs[which_button].mask;
            if (val == 0)
            {
                res = 1;
            }
            else
            {
                res = 0;
            }
        }
        else
        {
            val = _pinrefs[which_button].even->IN & _pinrefs[which_button].mask;
            if (val == 0)
            {
                res = 1;
            }
            else
            {
                res = 0;
            }

        }

    }
    return res;
}


/**
 @brief Determine if the button has been pressed
 since the last time this function was called
 */
int buttonPressed(int which_button)
{
    int res, val;
    if ((which_button < 0) || (which_button > (NUM_BUTTONS - 1)))
    {
        res = -1;
    }
    else
    {
        if ((_pinrefs[which_button].port_is_odd) == 1)
        {
            val = _pinrefs[which_button].odd->IFG & _pinrefs[which_button].mask;
            if (val == 0)
            {
                res = 0;
            }
            else
            {
                res = 1;
                _pinrefs[which_button].odd->IFG =
                        _pinrefs[which_button].odd->IFG
                                & ~(_pinrefs[which_button].mask);

            }
        }
        else
        {
            val = _pinrefs[which_button].even->IFG
                    & _pinrefs[which_button].mask;
            if (val == 0)
            {
                res = 0;
            }
            else
            {
                res = 1;
                _pinrefs[which_button].even->IFG =
                        _pinrefs[which_button].even->IFG
                                & ~(_pinrefs[which_button].mask);
            }

        }

    }
    return res;
}


/**
 @brief Callback function called from GPIO 's interrupt handlers
 */
void buttonCallback(int which_button) __attribute__ (( weak )
);
void buttonCallback(int which_button)
{
    /* Empty function */
}

