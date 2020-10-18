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

int RGB[3] = {0,0,0};
char received;
int r=1;
int t=0;
int i=1;

int main(void)
{
    CyGlobalIntEnable; 
    
    UART_Start();
    PWMRed_Start();
    PWMGreen_Start();
    PWMBlue_Start();
    ClockPWM_Start();
    ISR_Received_StartEx(Received_Datum);
    ISR_Timer_StartEx(Timer_ISR);
    
    PWMRed_WriteCompare(RGB[0]);
    PWMGreen_WriteCompare(RGB[1]);
    PWMBlue_WriteCompare(RGB[2]);
    
    for(;;)
    {    
        if (r==1)
        {  
            UART_PutString("Questo programma permette di controllare un canale RGB\r\nInserire i valori uno alla volta o tutti insieme\r\n");
            r=0;
        }
    }
}

/* [] END OF FILE */
