/*	Author: yxing024
 *      Partner(s) Name: 
 *	Lab Section:Final Project

 *      $$$$$$Mind Palace$$$$$$$

 *	Exercise Description: [maze game]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */



#include "timer.h"
#include "pwm.h"
#include "reg.c"
#include "io.c"
#include "ADC.c"

int main()
{
    DDRD = 0xff; PORTD = 0x00;
    DDRC = 0xFF; PORTC = 0x00;
    DDRA = 0xC0; PORTA = 0x3F;
 
    while (1)
    {
      
	
      
      PORTD = 0x00;
      if(!(PINA & 0x10)){
      send(0xfff7);
      send(0x38eb);
      send(0x3cab);
      send(0x34eb);
      send(0x1ceb);
      send(0x3ccb);
      send(0x3ce9);
      send(0xfffe);
      
      }
      clearreg();
    }
    return 0;
}



