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
#include "stdio.h"

int t=0;
int b=0;
int r=0;
char received;
int R=0, G=0, B=0;
static char message[90] = {'\0'};

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    UART_Start();
    PWMRedGreen_Start();
    PWMBlue_Start();
    ClockPWM_Start();
    ISR_Received_StartEx(Received_Datum);
    
    PWMRedGreen_WriteCompare1(R);
    PWMRedGreen_WriteCompare2(G);
    PWMBlue_WriteCompare(B);
    
    for(;;)
    {
        
        switch (r)
        {
            received = UART_ReadRxData();
            case 0:
            if(t==0)
                {
                UART_PutString("Questo programma permette di controllare un canale RGB\nInserire packet header 0x0A per iniziare\n");
                t=1;
                }
            break;
            case 1:
            if(b==0)
            {
                if(received == 'c')
                {
                    UART_PutString("Inserire entro 5 secondi intensita' canale rosso\n");
                    Timer_Start();
                    ClockTimer_Start();
                }
                else
                {
                    UART_PutString("Packet header non valido\n");
                    r=0;
                }
            }
            break;
            case 2:
            if (b==0)
            {
                UART_PutString("Inserire entro 5 secondi intensita' canale verde\n");
                R = received;
            }
            break;
            case 3:
            if (b==0)
            {
                UART_PutString("Inserire entro 5 secondi intensita' canale blu\n");
                G = received;
            }
            break;
            case 4:
            if(b==0)
            {
                UART_PutString("Inserire Packet tail 0x0C per terminare\n");
                B = received;
            }
            break;
            case 5:
            if(received == 192)
            {
                UART_PutString("Packet tail corretto\n");
                sprintf(message, "I colori selezionati per i tre canali sono: Rosso=%c\r\nVerde=%c\r\nBlu=%c\r\n", R,G,B);
                UART_PutString(message);
                //Timer_Stop();
                //ClockTimer_Start();
                //PWMRedGreen_Stop();
                //PWMBlue_Stop();
                //ClockPWM_Start();
                PWMRedGreen_WriteCompare1(R);
                PWMRedGreen_WriteCompare2(G);
                PWMBlue_WriteCompare(B);
                PWMRedGreen_WriteCounter(0);
                PWMBlue_WriteCounter(0);
                PWMRedGreen_Start();
                PWMBlue_Start();
                ClockPWM_Start();                         
            }
            else
            {
                UART_PutString("Packet tail non valido\n");
                r=4;
            }
            break;
        }
    }
}

/* [] END OF FILE */
