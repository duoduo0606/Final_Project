/*	Author: yxing024
 *	Lab Section:Final Project
 *      $$$$$$$$$$$$$$$$$$$$$$$$$$
 *      $$$$$$$$$$$$$$$$$$$$$$$$$$
 *      $$$$$$$ Mind Palace $$$$$$
 *      $$$$$$$$$$$$$$$$$$$$$$$$$$
 *      $$$$$$$$$$$$$$$$$$$$$$$$$$
 *	Exercise Description: [maze game]
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

//---------------------------include file----------------------------

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

#include <stdio.h>

#include "reg.c"
#include "io.c"
#include "adc.c"

//---------------------------sharp define-----------------------------

#define switch PINA & 0x01
#define button (~PINA & 0x08) >> 3

//---------------------------state machine----------------------------

/* 
   state machine
   Task1 
*/

//---------------------------global variable--------------------------

//---------------------------Task1 xxx--------------------------





//---------------------------main function----------------------------
int main()
{
    // DDR setting
   
       DDRA = 0xC0; PORTA = 0x3F;
       DDRB = 0xFF; PORTB = 0x00;
       DDRC = 0xFF; PORTC = 0x00;
       DDRD = 0xFF; PORTD = 0x00;

    // variable setting
    
       const unsigned short numTasks = 7;
       const unsigned short GCDPeriod = 25;
       task tasks[numTasks];
       unsigned char i = 0;
    
    // Task 1: Input
        tasks[i].state = 0;
        tasks[i].period = 25;
        tasks[i].elapsedTime = 0;
        tasks[i].TickFct = &Input_Tick;
        i++;

    // Task 2: Paddle
	tasks[i].state = 0;
	tasks[i].period = 50;
	tasks[i].elapsedTime = 0;
	tasks[i].TickFct = &Paddle_Tick;
	i++;

    // Task 3: Level
	tasks[i].state = 0;
	tasks[i].period = 50;
	tasks[i].elapsedTime = 0;
	tasks[i].TickFct = &Level_Tick;
	i++;

    // Task 4: Boss
	tasks[i].state = 0;
	tasks[i].period = 250;
	tasks[i].elapsedTime = 0;
	tasks[i].TickFct = &Boss_Tick;
	i++;

    // Task 5: Ball
	tasks[i].state = 0;
	tasks[i].period = 250;
	tasks[i].elapsedTime = 0;
	tasks[i].TickFct = &Ball_Tick;
	i++;

    // Task 6: LEDDisplay
	tasks[i].state = 0;
	tasks[i].period = 25;
	tasks[i].elapsedTime = 0;
	tasks[i].TickFct = &LEDDisplay_Tick;
	i++;

    // Task 7: LCDDisplay
	tasks[i].state = 0;
	tasks[i].period = 500;
	tasks[i].elapsedTime = 0;
	tasks[i].TickFct = &LCDDisplay_Tick;

    TimerSet(GCDPeriod);
    TimerOn();
    LCD_init();
    ADC_init();

    while (1) 
      {
     
	// Scheduler code
	    for ( i = 0; i < numTasks; i++ ) 
	      {
	// Task is ready to tick
		    if ( tasks[i].elapsedTime == tasks[i].period ) 
		      {
	// Setting next state for task
			tasks[i].state = tasks[i].TickFct(tasks[i].state);
	// Reset the elapsed time for next tick.
			tasks[i].elapsedTime = 0;
		      }
		    tasks[i].elapsedTime += GCDPeriod;
	      }
	    while(!TimerFlag);
	    TimerFlag = 0;
      }
    return 0;
}


