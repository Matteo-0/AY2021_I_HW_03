/* 
 *
 * 
 *
 *
 *
 * 
 * 
 *
 * 
*/

#include "project.h"
#include "ISRTimer.h"

extern int r;
extern int i;

CY_ISR(Timer_ISR)
{
    UART_PutString("\nIl dato non e' stato inserito entro 5 secondi\n\n");
    r=1;
    i=1;
    Timer_Stop();
    ClockTimer_Stop();
}

/* [] END OF FILE */
