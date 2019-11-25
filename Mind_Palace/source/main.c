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
#include "io.c"
//#include "reg1.c"
//#include "reg2.c"
#include "reg.c"
int main()
{
    DDRD = 0xff; PORTD = 0x00;
    DDRC = 0xFF; PORTC = 0x00;
    DDRA = 0xC0; PORTA = 0x3F;
   
    while (1)
    {
   
    
      send(0xfff7);
send(0x1ceb);

      //sendcol(0x0f);
      // sendrow(0x0f);
    }
    return 0;
}
