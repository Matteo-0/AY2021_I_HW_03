/**
*     \file main.c
*     \brief main source file for the third assignment
*
*     This source file allows to control the intensity of the three channels of an RGB Led.
*
*     \author: Matteo Boles
*     \date: October 20, 2020
*/

#include "project.h"
#include "ISRUART.h"
#include "ISRTimer.h"

int RGB[3] = {0,0,0};                             // Array where we save the intensity value of each channel of the RGB
char received;                                    // Variable where we save the byte sent
int r=1;                                          // Variable used to enter the idle state
int t=0;                                          // Variable used to enter different cases in the switch case in the ISRUART.c 
int i=1;                                          // Variable used to increment t in the ISRUART.c

int main(void)
{
    CyGlobalIntEnable;                            // Enables global interrupts
    
    UART_Start();                                 // Initializes and enables the UART operation
    PWMRedGreen_Start();                          // Initializes PWM that controls Red and Green channels
    PWMBlue_Start();                              // Initializes PWM that controls Blue channel
    ClockPWM_Start();                             // Starts the common clock of the two PWM
    ClockTimer_Start();                           // We activate the clock of the timer
    ISR_Received_StartEx(Received_Datum);         // Sets up the interrupt on the received byte
    ISR_Timer_StartEx(Timer_ISR);                 // Sets up the interrupt on the timer
     
    // When the system is activated at the beginning the three channels must be set to zero so that they are all off
    PWMRedGreen_WriteCompare1(RGB[0]);            
    PWMRedGreen_WriteCompare2(RGB[1]);
    PWMBlue_WriteCompare(RGB[2]);
    
    for(;;)
    {    
        // if r is equal to 1 we are in the idle state. Each time we pass from this state the variables t and i are set to their initial values 
        // In this way when we enter the ISR activated on the received byte we will restart from the first case of the switch case
        if (r==1)
        {  
            UART_PutString("Questo programma permette di controllare un canale RGB\r\nInserire i valori uno alla volta (ognuno entro 5 secondi) o tutti insieme\r\n");
            t=0;
            i=1;
            r=0;          // r is set to zero so that the string is not written countless times
        }
    }
}

/* [] END OF FILE */
