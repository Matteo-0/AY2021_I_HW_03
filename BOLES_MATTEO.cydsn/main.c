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
#include "ISRTimer.h"
#include "stdio.h"

int t=0,h=0,c=0,s=0,p=0,q=0;
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
    ISR_Timer_StartEx(Timer_ISR);
    
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
                UART_PutString("Questo programma permette di controllare un canale RGB\r\nInserire packet header 0x0A per iniziare\r\n");
                t=1;
                }
            break;
            case 1:
            if(b==0)
            {
                if(received == 0x0A)
                {                
                    if(h==0)
                    {
                    UART_PutString("Inserire entro 5 secondi intensita' canale rosso\r\n");
                    h=1;
                    }
                    Timer_Start();
                    ClockTimer_Start();
                }
                else
                {
                    UART_PutString("\r\nPacket header non valido\r\n");
                    CyDelay(1000);
                    r=0;
                    t=0;
                }
            }
            break;
            case 2:
            if (b==0)
            {
                if (c==0)
                {
                UART_PutString("\nInserire entro 5 secondi intensita' canale verde\n");
                c=1;
                }
                R = received;
            }
            break;
            case 3:
            if (b==0)
            {
                if (s==0)
                {
                UART_PutString("\nInserire entro 5 secondi intensita' canale blu\n");
                s=1;
                }
                G = received;
            }
            break;
            case 4:
            if(b==0)
            {
                if(p==0)
                {
                UART_PutString("\n\nInserire Packet tail 0x0C per terminare\n");
                p=1;
                }
                B = received;
            }
            break;
            case 5:
            if(received == 0x0C)
            {
                if(q==0)
                {
                UART_PutString("\nPacket tail corretto\n");
                q=1;
                }
                sprintf(message, "\nI colori selezionati per i tre canali sono: Rosso=%c\r\nVerde=%c\r\nBlu=%c\r\n", R,G,B);
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
                UART_PutString("\nPacket tail non valido\n");
                r=4;
                p=0;
            }
            break;           
        }
    }
}

/* [] END OF FILE */
