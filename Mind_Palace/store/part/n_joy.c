/*	Author: yxing024
 *      Partner(s) Name: 
 *	Lab Section:Final Project

 *      $$$$$$Mind Palace$$$$$$$

 *	Exercise Description: [maze game]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

#include "adc.c"
#include "io.c"
#include <stdio.h>

int main()
{
int  m,n ;
char str1[20],str2[20];
    DDRD = 0xff; PORTD = 0x00;
    DDRC = 0xFF; PORTC = 0x00;
    DDRA = 0xC0; PORTA = 0x3F;
 
    while (1)
    {
      ADC_init();
      m = ADC_Read(0);
      n = ADC_Read(1);
      LCD_init();
// LCD_WriteData('0'+m);
      sprintf(str1,"X = %d",m);
LCD_DisplayString(1,str1);
delay_ms(5);
sprintf(str2,"Y = %d",n);
LCD_DisplayString(17,str2);
      delay_ms(5);
    }
    return 0;
}



