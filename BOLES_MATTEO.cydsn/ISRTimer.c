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
extern int t;

CY_ISR(Timer_ISR)
{
    UART_PutString("Il dato non e' stato inserito entro 5 secondi\n");
    r=0;
    t=0;
    Timer_Stop();
}

/* [] END OF FILE */
