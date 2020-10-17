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
#include "ISRUART.h"

extern int r;
extern char received;
extern int b,t,h;

CY_ISR(Received_Datum)
{
    if(UART_ReadRxStatus() == UART_RX_STS_FIFO_NOTEMPTY)
    {
        received = UART_ReadRxData();
        if(received >= 0x0A && received <= 0xFF )
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
