/**
*     \file ISRTimer.c
*     \brief source file for the third assignment
*
*     This source file allows to return the system to the idle state if the byte is not sent within 5 seconds.
*     This ISR is called every time the timer finish to count 5 seconds, when the timer is activated.
*
*     \author: Matteo Boles
*     \date: October 20, 2020
*/

#include "project.h"
#include "ISRTimer.h"

extern int r;

CY_ISR(Timer_ISR)
{
    UART_PutString("\nIl dato non e' stato inserito entro 5 secondi\n\n");
    r=1;                                    // r is set to 1 to return to the idle state
    Timer_Stop();                           // Timer is stopped so that the interrupt doesn't start again
}

/* [] END OF FILE */
