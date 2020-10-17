/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include "project.h"
#include "ISRTimer.h"

extern int r;

CY_ISR(Timer_ISR)
{
    UART_PutString("Il dato non e' stato inserito entro 5 secondi\n");
    r=0;
    Timer_Stop();
}

/* [] END OF FILE */
