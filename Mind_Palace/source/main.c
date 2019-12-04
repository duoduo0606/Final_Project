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
#include "matrix.c"
#include "scheduler.h"

#include "timer.h"
#include "pwm.h"

//---------------------------sharp define-----------------------------

#define switch0 (PINA & 0x10) >> 4
#define button (~PINA & 0x08) >> 3
#define gbutton (~PINA & 0x20) >> 5

//---------------------------state machine----------------------------

/* 

   state machine
   Task1 INPUT
   Task2 GAMEen
   Task3 GMAElgc
   Task4 LED
   Task5 LCD
   Task6 MUSIC
   
*/

//---------------------------global variable--------------------------

 unsigned char game_en = 0;
 unsigned char game_on = 0;
unsigned char game_play = 0;
//unsigned char game_st = 0;
static unsigned char game_win = 0;

//unsigned char frame = 0;

unsigned char dotcol = 2;
unsigned char dotrow = 2;

unsigned char stepcnt = 0;
 
unsigned char right = 0;
unsigned char left = 0;
unsigned char up = 0;
unsigned char down = 0;




//---------------------------Task1 INPUT--------------------------
enum INPUT_states {INPUT_start, INPUT_wait} input_state;

int INPUT_Tick(int state) {
	//=== Local variables ===
	
	unsigned short joyx = ADC_Read(0);
	unsigned short joyy = ADC_Read(1);
	
        right = 0;
        left = 0;
        up = 0;
        down = 0;
	// ===Transitions=== 
	switch(state) {
	case INPUT_start:   
	  state = INPUT_wait;	 
	  break;
	
	case INPUT_wait:
	  break;
        
	default:
	  state = INPUT_start;
	  break;
	}

	// === Actions ===
	switch(state) {
		case INPUT_start:
		  right = 0;
		  left = 0;
		  up = 0;
		  down = 0;

		  break;
		case INPUT_wait:
			
		  if(joyx>=1023){
		    right = 1;
		    left = 0;
		  }
		  else if(joyx<=15){
		    left = 1;
		    right = 0;
		  }
		  else if(joyy>=1023){
		    up = 0;
		    down = 1;
		  } 
		  else if(joyy<=15){
		    down = 0;
		    up = 1;
		  }
		  break;
		
		 
		default:
		  break;
	}

	return state;
};




//---------------------------Task2 GAMEen--------------------------
enum GAMEen_states { GAMEen_start, GAMEen_on, GAMEen_off } GAMEen_state;
int GAMEen_Tick(int state) {
  // === Local variables===
	
  // === Var init ===

  game_en = switch0;

  // === Transitions ===
  switch(state) {
		case GAMEen_start:
		  state = game_en? GAMEen_on:GAMEen_off;
			break;

		case GAMEen_on:
		  state = game_en? GAMEen_on:GAMEen_off;
			break;

                case GAMEen_off:
		  state = game_en? GAMEen_on:GAMEen_off;	
			break;
	
		default:
			state = GAMEen_start;
			break;
	}

  // === Actions ===
  switch(state) {
		case GAMEen_start:
		  game_on = 0;
			break;

		case GAMEen_on:
		  game_on = 1;
			break;

                case GAMEen_off:
		  game_on = 0;	
			break;
	
		default:
		  state = GAMEen_start;
			break;
	}
	return state;
};







//---------------------------Task3 GAMElgc--------------------------
enum GAMElgc_states { GAMElgc_start, GAMElgc_play, GAMElgc_check, GAMElgc_movel, GAMElgc_mover, GAMElgc_moveu, GAMElgc_moved, GAMElgc_win} GAMElgc_state;
int GAMElgc_Tick(int state) {
  // === Local variables ===

  game_win = 0;
  
  unsigned char map[8][8] = {{1,1,1,1,1,1,1,1},
			     {1,0,1,1,0,0,0,1},
			     {1,0,0,0,0,1,0,1},
                             {1,1,0,1,1,0,0,1},
			     {1,1,0,1,1,0,1,1},
			     {1,0,0,0,0,0,0,1},
			     {1,0,1,0,0,1,0,1},
                             {1,1,1,1,1,1,0,1}};
  
  
  // === Transitions ===
  switch(state) {
		case GAMElgc_start:
		  state = game_on? GAMElgc_play:GAMElgc_start;
			break;

		case GAMElgc_play:
		  if ((game_on)&&(gbutton))
		    {
		      state = GAMElgc_check;
		    }
		  else{
		    state = GAMElgc_play;
		  }
		 
			break;

                case GAMElgc_check:
		  
		  
		    if (left){
		      state =  GAMElgc_movel;
		    }
		    else if (right){
		      state =  GAMElgc_mover;
		    }
		    else if (up){
		      state =  GAMElgc_moveu;
		    }
		    else if (down){
		      state =  GAMElgc_moved;
		    }
		    else if ((left || right || up || down) == 0){
		     state = GAMElgc_check;
		   }

		    if ((dotcol == 7)&&(dotrow == 7)){
		      state = GAMElgc_win;
		    }
		  	break;

                case GAMElgc_movel:
		  state = game_on? GAMElgc_check:GAMElgc_play;
			break;

                case GAMElgc_mover:
		  state = game_on? GAMElgc_check:GAMElgc_play;
			break;
                case GAMElgc_moveu:
		  state = game_on? GAMElgc_check:GAMElgc_play;
			break;
                case GAMElgc_moved:
		  state = game_on? GAMElgc_check:GAMElgc_play;
			break;

                case GAMElgc_win:
		  state = gbutton?GAMElgc_play:GAMElgc_win;
			break;

		default:
			state = GAMElgc_start;
			break;
	}

  // === Actions ===
  switch(state) {
               case GAMElgc_start:
		  
			break;

		case GAMElgc_play:
		  dotcol = 2;
		  dotrow = 2;
		  game_win = 0;
		  game_play = 0;
		  stepcnt = 0;
			break;

                case GAMElgc_check:
		  game_play = 1;
			break;

                case GAMElgc_movel:
		  if ((map[dotcol-2][dotrow-1] == 0)&&(dotcol > 2)){
		    dotcol--;
		    stepcnt++;
		  }
			break;

                case GAMElgc_mover:
		  if((map[dotcol][dotrow-1] == 0)&&(dotcol <= 6 )){
		    dotcol++;
		    stepcnt++;
		  }
			break;
                case GAMElgc_moveu:
		  if ((map[dotcol-1][dotrow] == 0)&&(dotrow <=6 )){
		    dotrow++;
		    stepcnt++;
		  }
			break;
                 case GAMElgc_moved:
		   if((map[dotcol-1][dotrow-2] == 0)&&(dotrow > 2)){
		     dotrow--;
		     stepcnt++;
		   } 
			break;

                case GAMElgc_win:
		  game_win = 1;
		 	break;
	
	}
	return state;
};








//---------------------------Task4 LED--------------------------
enum LED_states { LED_start, LED_init, LED_frame} LED_state;
int LED_Tick(int state) {
  // Local variables
	
 

  // === Transitions ===
  switch(state) {
		case LED_start:
		  	  state = LED_init;

		  
			break;

                case LED_init:
		 	  state = game_on? LED_frame:LED_init;

			break;
               
                 case LED_frame:
		   state = game_on? LED_frame:LED_init;	
		  
		 
			break;

		default:
			state = LED_start;
			break;
	}

  // === Actions ===
    switch(state) {
		case LED_start:
		  
		  /*
		 send(0x6b7b);
		  send(0x677b);
		  send(0xad3f);
		  send(0x8d7f);
		  send(0x6f5b);
		  send(0x6f79);
		  clearreg();
		  */
		  
			  	 
			break;

        	case LED_init:
		  
		  
		 send(0x6b7b);
		  send(0x677b);
		  send(0xad3f);
		  send(0x8d7f);
		  send(0x6f5b);
		  send(0x6f79);
		  clearreg();
		  break;

                case LED_frame:
		 
		  
		  send(0xfff7);
		  send(0x79eb);
		  
		  
		  send(0xb4eb);
		  send(0x3fbb);
		  send(0x1fff);
		  send(0x3ccb);
		  send(0xfce9);
		  send(0xfffe); 
		   send(litled(dotcol,dotrow));
		 
		  clearreg();
		  
			break;

	       
	
	}
	return state;
};








//---------------------------Task5 LCD-----------------------------------

enum LCD_states { LCD_start, LCD_wait, LCD_on, LCD_win} LCD_state;
int LCD_Tick(int state) {
  // Local variables
	
 char buffer[20];

  // === Transitions ===
  switch(state) {
		case LCD_start:
		  state = game_on? LCD_wait:LCD_start; 
			break;

		case LCD_wait:
		  
		  // state = (game_on && game_play)? LCD_on:LCD_wait;
		  
		  if (game_on){
		    if (game_play){
		      state = LCD_on;
		    }
		    else {state = LCD_wait;}
		  }
		  else{state = LCD_start;}

			break;

                case LCD_on:
		  	  
		  // state = (game_on && game_win)? LCD_win:LCD_on;
			
		  if (game_on){
		    if (game_win){
		      state = LCD_win;
		    }
		    else {state = LCD_on;}
		  }
		  else{state = LCD_start;}

			 break;	
                
                case LCD_win:
		  
		  // state = (game_on && game_win)?LCD_win:LCD_start;
		    
		  if (game_on){
		    if (game_win){
		      state = LCD_win;
		    }
		    else {state = LCD_start;}
		  }
		  else{state = LCD_start;}

		  break;

		  	default:
		  	state = LCD_start;
		  	break;
	}

  // === Actions ===
    switch(state) {
		case LCD_start:
		  LCD_ClearScreen();
        
			break;

                case LCD_wait:
	        
		  LCD_DisplayString(1,"Find your lover");
			break;

		case LCD_on:
		 		 
		  sprintf(buffer, "Cur_Step:%d", stepcnt);
		  LCD_DisplayString(1,buffer);
	        	  
			break;

               	case LCD_win:
		  if (stepcnt == 10){
		    LCD_DisplayString(1,"You find her");		 
		  }
		  else {
		    LCD_DisplayString(1,"She LEFT");
		  }
			break;



	       
	
	}
	return state;
};





//---------------------------Task6 MUSIC--------------------------
enum MUSIC_states { MUSIC_off, MUSIC_play} MUSIC_state;

unsigned char notes_number = 58;
unsigned char position = 0;
unsigned char count = 0;


unsigned char n8 = 2 ; // ticks per note
unsigned char n4 = 4; // ticks per note 
unsigned char n2 = 8; // ticks per note 
unsigned char th = 12;
unsigned char whole = 16;

double c4 = 261.63;
double d4 = 293.66;
double e4 = 329.63;
double f4 = 349.23;
double g4 = 392.00;
double a4 = 440.00;
double b4 = 493.88;
double c5 = 523.25;
double d5 = 587.33;
double e5 = 659.25;
double f5 = 698.46;
double g5 = 783.99;

int MUSIC_Tick(int state) {
  // Local variables
	
double music_notes[] = {e4,a4,b4,c5,b4,a4,f4,0,f4,a4,b4,c5,b4,a4,e4,0,e4,a4,b4,c5,b4,a4,f4,0,d5,c5,b4,c5,b4,a4,e4,0,  f5,e5,d5,e5,d5,c5, a4,b4, e5,d5,c5,d5,c5,b4, a4,0 ,f5,e5,d5,e5,d5,c5,a4,b4,e5  };
unsigned char note_length[] = {n8,n8,n8,n8,n8,n8,th,n8, n8,n8,n8,n8,n8,n8,th,n8, n8,n8,n8,n8,n8,n8,th,n8, n8,n8,n8,n8,n8,n8,th,n8, n8,n8,n8,n8,n8,n8,n2,n4, n8,n8,n8,n8,n8,n8,th,n8,n8,n8,n8,n8,n8,n8,n2,n4,whole};

  // === Transitions ===
 switch(state)
    {
        case MUSIC_off:
        if(button){
            state = MUSIC_play;
        }
        else{
            state = MUSIC_off;
        }
        break;

        case MUSIC_play:
	  if((button) || (position >=notes_number) && (count >= note_length[position])){
            state = MUSIC_off;
        }
        break;

        default:
        state = MUSIC_off;
        break;
    }
 // === Action ===
    switch(state)
    {
        case MUSIC_off:
            set_PWM(0);
            count = 0;
            position = 0;
        break;

        case MUSIC_play:
            if(count < note_length[position]){
                set_PWM(music_notes[position]);
            }else {
                position++;
                count = 0;
                set_PWM(music_notes[position]);              
            }     
            count++;                      
        break;

        default:
        set_PWM(0);
        break;
    }
    return state;
}



//---------------------------main function----------------------------
int main()
{
    // DDR setting
   
       DDRA = 0xC0; PORTA = 0x3F;
       DDRB = 0xFF; PORTB = 0x00;
       DDRC = 0xFF; PORTC = 0x00;
       DDRD = 0xFF; PORTD = 0x00;

    // variable setting
    
       const unsigned short numTasks = 6;
       const unsigned short GCDPeriod = 20;
       task tasks[numTasks];
       unsigned char i = 0;
    
    // Task 1: INPUT
        tasks[i].state = 0;
        tasks[i].period = 40;
        tasks[i].elapsedTime = 0;
        tasks[i].TickFct = &INPUT_Tick;
        i++;

    // Task 2: GAMEen
	tasks[i].state = 0;
	tasks[i].period = 20;
	tasks[i].elapsedTime = 0;
	tasks[i].TickFct = &GAMEen_Tick;
	i++;

    // Task 3: GAMElgc
	tasks[i].state = 0;
	tasks[i].period = 100;
	tasks[i].elapsedTime = 0;
	tasks[i].TickFct = &GAMElgc_Tick;
	i++;

    // Task 4: LED
	tasks[i].state = 0;
	tasks[i].period = 20;
	tasks[i].elapsedTime = 0;
	tasks[i].TickFct = &LED_Tick;
	i++;

    // Task 5: LCD
	tasks[i].state = 0;
	tasks[i].period = 200;
	tasks[i].elapsedTime = 0;
	tasks[i].TickFct = &LCD_Tick;
	i++;

    // Task 6: MUSIC
	tasks[i].state = 0;
	tasks[i].period = 160;
	tasks[i].elapsedTime = 0;
	tasks[i].TickFct = &MUSIC_Tick;
	i++;	
  

  


    TimerSet(GCDPeriod);
    TimerOn();
    LCD_init();
    ADC_init();

    PWM_on();
    set_PWM(0);
 

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


