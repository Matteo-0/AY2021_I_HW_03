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
extern int t,h,c,s,p,q,b;

CY_ISR(Timer_ISR)
{
    UART_PutString("Il dato non e' stato inserito entro 5 secondi\n\n");
    r=0, t=0,h=0,c=0,s=0,p=0,q=0;
    b=1;
    Timer_Stop();
    ClockTimer_Stop();
}

/* [] END OF FILE */
