/**
*     \file ISRUART.c
*     \brief source file for the third assignment
*
*     This ISR is activated each time a byte is sent.
*     Each time we send a byte we enter a different case in the switch case.
*     Which case we enter is regulated by a variable t that is incremented by a variable i each time we enter the ISR.
*
*     \author: Matteo Boles
*     \date: October 20, 2020
*/

#include "project.h"
#include "ISRUART.h"
#include "stdio.h"

extern int r;
extern int i;
extern int t;
extern char received;
extern int RGB[3];
static char message[90] = {'\0'};

CY_ISR(Received_Datum)
{
    if(UART_ReadRxStatus() == UART_RX_STS_FIFO_NOTEMPTY)       // Controls if a byte has been sent      
    {
        t=t+i;                               // t is incremented by i, so that each time we enter the right case in the switch case
        received = UART_ReadRxData();        // We save the sent byte in the variable received
        if (received == 'v')                 // This part is used to connect to the GUI
        {
            UART_PutString("\nRGB LED Program $$$\r\n");
            r=1;
        }
        switch (t)
        { 
            case 1:                         // When we send the first byte we enter the first case. 
            if(received == 0xA0)            // Check if the packet header is correct 
            {
                t=0;                        // t is reset to zero
                i++;                        // i here is equal to 2
                Timer_Start();              // We activate the timer so that we have 5 seconds to send the next byte otherwise we return to idle
            }
            else
            {    
                UART_PutString("\nPacket header scorretto ritorno allo stato di idle\n\n");
                r=1;                        // If the packet header is not correct we return to the idle state
            }
            break;
            case 2:                         // When we send the second byte we enter the second case
            Timer_Init();                   // We restore the timer so that it restarts to count from 5 seconds
            RGB[0] = received;              // We save the byte of the red channel in RGB[0]
            t=0;                            // t is reset to zero
            i++;                            // i here is equal to 3
            break;            
            case 3:                         // When we send the third byte we enter the third case
            Timer_Init();                   // We restore the timer so that it restarts to count from 5 seconds
            RGB[1] = received;              // We save the byte of the green channel in RGB[1]
            t=0;
            i++;                            // i here is equal to 4
            break;
            case 4:                         // When we send the forth byte we enter the forth case
            Timer_Init();                   // We restore the timer so that it restarts to count from 5 seconds
            RGB[2] = received;              // We save the byte of the blue channel in RGB[2]
            t=0;                            
            i++;                            // i here is equal to 5
            break;
            case 5:                                  // When we send the last byte we enter the last case
            if(received == 0xC0)                     // We verify if the right packet tail has been sent
            {
                Timer_Stop();                        // We stop the timer because we will return to the idle state
                sprintf(message,"\nI valori inseriti per i tre canali sono:\nRosso = %d\nVerde = %d\nBlu = %d\n\n", RGB[0],RGB[1],RGB[2]);
                UART_PutString(message);
                PWMRedGreen_WriteCompare1(RGB[0]);   // We set the duty cycle of the blue channel according to the byte sent
                PWMRedGreen_WriteCompare2(RGB[1]);   // We set the duty cycle of the blue channel according to the byte sent
                PWMBlue_WriteCompare(RGB[2]);        // We set the duty cycle of the blue channel according to the byte sent
                r=1;                                 // We return to the idle state
            }
            else
            {
                UART_PutString("\nPacket tail scorretto ritorno allo stato di idle\n\n");
                Timer_Stop();                        // We stop the timer because we will return to the idle state
                r=1;                                 // We return to the idle state
            }
            break;          
        } 
    }
    
}
   
/* [] END OF FILE */
