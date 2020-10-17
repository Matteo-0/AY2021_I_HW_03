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
#include "ISRUART.h"

extern int r;
extern char received;
extern int b;

CY_ISR(Received_Datum)
{
    if(UART_ReadRxStatus() == UART_RX_STS_FIFO_NOTEMPTY)
    {
        if(received >= 0 && received <= 255)
        {
            r++;
            b=0;
        }
        else
        {
            UART_PutString("Inserire un altro valore compreso tra 0 e 255 oppure il packet header o il tail header");
            b=1;
        }
    }
}
   
/* [] END OF FILE */
