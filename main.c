/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.171.4
        Device            :  dsPIC33CK256MP508
    The generated drivers are tested against the following:
        Compiler          :  XC16 v2.10
        MPLAB 	          :  MPLAB X v6.05
*/

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/
#include "mcc_generated_files/mcc.h"
#ifndef FCY
#define FCY (_XTAL_FREQ/2)
#endif
#include <libpic30.h>
#include "mcc_generated_files/adc1.h"
#include "mcc_generated_files/uart1.h"
#include "stick/SystemTick.h"
#include "oled/OLED.h"
static const ADC1_CHANNEL channel=channel_AN23;
uint16_t readADC(void)
{
    uint16_t conversion;
    int i=0;
    ADC1_SoftwareTriggerEnable();
    for (i=0;i<1000;i++)
    {
        //delay
    }
    ADC1_SoftwareTriggerDisable();
    while(!ADC1_IsConversionComplete(channel));
    conversion=ADC1_ConversionResultGet(channel);
    return conversion;
    
}
/*
                         Main application
 */
int main(void)
{
    // initialize the device
//    tick_timer_t Tick1, Tick2;
    SYSTEM_Initialize();
    SystemTick_Init();
//    Tick_Timer_Reset(Tick1);
//    Tick_Timer_Reset(Tick2);
    ADC1_Enable();
    ADC1_ChannelSelect(channel);
    Oled_Init();
    Oled_Clear();              
    while (1)
    {
        // Add your application code
//         if (Tick_Timer_Is_Over_Ms(Tick1, 100))
         LED1_Toggle();
         __delay_ms(1000);
         char str1[10]; 
         uint16_t adcValue=readADC();
         sprintf(str1, "%u",adcValue); 
         Oled_SelectPage(1); //page 1 Select page/line 0-7 
         Oled_WriteString(" ADCvalue:");
         __delay_ms(20);
//         Oled_ClearLine(1);
         Oled_SelectPage(3); //page 2 //Select page/line 0-7 
         Oled_WriteString(" ");
         Oled_WriteString(str1);
         __delay_ms(5000);
         Oled_ClearLine(3);
          printf(" %u\n",adcValue);
          __delay_ms(100);
         Oled_ClearLine(0);
         Oled_ClearLine(2);
         Oled_ClearLine(4);
         Oled_ClearLine(5);
         Oled_ClearLine(6);
         Oled_ClearLine(7);
    }
    return 1; 
}
/**
 End of File
*/

