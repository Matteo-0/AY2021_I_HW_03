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
int b=0,z=0;
int r=0;
char received;
int R=0, G=0, B=0;
//static char message[150] = {'\0'};

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    UART_Start();
    PWMRed_Start();
    PWMGreen_Start();
    PWMBlue_Start();
    ClockPWM_Start();
    ISR_Received_StartEx(Received_Datum);
    //ISR_Timer_StartEx(Timer_ISR);
    
    PWMRed_WriteCompare(R);
    PWMGreen_WriteCompare(G);
    PWMBlue_WriteCompare(B);
    
    for(;;)
    {
        
        switch (r)
        {
            received = UART_ReadRxData();
            case 0:
            
            if(t==0)
                {
                UART_PutString("Questo programma permette di controllare un canale RGB\r\nInserire packet header 0xA0 per iniziare\r\n");
                t=1;
                UART_ClearRxBuffer();
                }
            break;
            case 1:
            if(b==0)
            {
                if(received == 0xA0)
                {                
                    if(h==0)
                    {
                    UART_PutString("\nInserire entro 5 secondi intensita' canale rosso\r\n");
                    h=1;
                    b=1;
                    Timer_Start();
                    ClockTimer_Start();
                    }                     
                }
                else
                {
                    UART_PutString("\r\nPacket header non valido\n\n");
                    r=0;
                    t=0;
                    h=0;
                    b=0;
                }    
            }
            break;
            case 2:
            R = received;
            if (z==0)
            {      
                Timer_Stop();
                Timer_WritePeriod(250);
                Timer_Enable();
                if (c==0)
                {
                UART_PutString("\nInserire entro 5 secondi intensita' canale verde\n");
                c=1;
                z=1;
                //Timer_Start();
                }

            }
            break;           
            case 3:
            G = received;
            b=0;
            Timer_Stop();
            Timer_WriteCounter(250);
            Timer_Enable();          
            if (b==0)
            {
                
                if (s==0)
                {
                UART_PutString("\nInserire entro 5 secondi intensita' canale blu\n");
                s=1;
                b=1;
                } 
               
            }
            break;
            case 4:
            B = received;
            b=0;
            Timer_Stop();
            Timer_WriteCounter(250);
            Timer_Enable();            
            if(b==0)
            {
                if(p==0)
                {
                UART_PutString("\n\nInserire Packet tail 0xC0 per terminare\n");
                p=1;
                }
                
            }
            break;
            case 5:
            b=0;
            if(received == 0xC0)
            {
                if(q==0)
                {
                UART_PutString("\nPacket tail corretto\n\n");
                q=1;
                }
                //PWMRed_WriteCounter(0);
                //PWMGreen_WriteCounter(0);
                //PWMBlue_WriteCounter(0);
                Timer_Stop();
                PWMRed_Stop();
                PWMGreen_Stop();
                PWMBlue_Stop();
                PWMRed_Enable();
                PWMGreen_Enable();
                PWMBlue_Enable();
                PWMRed_WriteCompare(R);
                PWMGreen_WriteCompare(G);
                PWMBlue_WriteCompare(B);
                PWMRed_Start();
                PWMGreen_Start();
                PWMBlue_Start();
                r=0;
                t=0,h=0,c=0,s=0,p=0,q=0;
                b=0,z=0;
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
