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
#include "stdio.h"

extern int b;
extern int r;
extern char received;
extern int i;
extern int t;
extern int RGB[3];
static char message[90] = {'\0'};

CY_ISR(Received_Datum)
{
    if(UART_ReadRxStatus() == UART_RX_STS_FIFO_NOTEMPTY)
    {
        t=t+i;
        received = UART_ReadRxData();
        switch (t)
        { 
            case 1:
            if(received == 0xA0)
            {
                r=0;
                i++;
                t=0;
                Timer_Start();
                ClockTimer_Start();
            }
            else
            {        
                UART_ClearRxBuffer();
                UART_PutString("\nheader non corretto\n");
                r=1;
                i=1;
                t=0;               
            }
            break;
            case 2:
            Timer_Init();
            RGB[0] = received;
            t=0;
            i++;
            break;
            case 3:
            Timer_Init();
            RGB[1] = received;
            t=0;
            i++; 
            break;
            case 4:
            Timer_Init();
            RGB[2] = received;
            t=0;
            i++;
            break;
            case 5:
            if(received == 0xC0)
            {
                Timer_Stop();
                sprintf(message,"\nPacket header e packet tail corretti.\n\nI valori selezionati sono:\nRosso=%d\nVerde=%d\nBlu=%d\n\n",RGB[0],RGB[1],RGB[2]);
                UART_PutString(message);
                PWMRed_WriteCompare(RGB[0]);
                PWMGreen_WriteCompare(RGB[1]);
                PWMBlue_WriteCompare(RGB[2]);
                r=1;
                i=1;
                t=0;
            }
            else
            {
                Timer_Stop();
                UART_PutString("\nPacket tail non corretto\n\n");
                r=1;
                i=1;
                t=0;
            }
            break;          
        } 
    }
    
}
   
/* [] END OF FILE */
