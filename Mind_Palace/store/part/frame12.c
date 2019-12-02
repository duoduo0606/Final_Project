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

#define switch0 PINA & 0x01
#define button (~PINA & 0x08) >> 3

//---------------------------state machine----------------------------

/* 

   state machine
   Task1 GAMEen
   Task2 GMAElgc
   Task3 LED
   Task4 LCD
   Task5 INPUT
   Task6 MUSIC
   
*/

//---------------------------global variable--------------------------

unsigned char game_en = switch0;
unsigned char game_on = 0;

unsigned char right = 0;
unsigned char left = 0;
unsigned char up = 0;
unsigned char down = 0;



//---------------------------Task1 GAMEen--------------------------
enum GAMEen_states { GAMEen_start, GAMEen_on, GAMEen_off } GAMEen_state;
int GAMEen_Tick(int state) {
  // Local variables
	
  static unsigned short count = 0;

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


//---------------------------Task2 GAMElgc--------------------------
enum GAMElgc_states { GAMElgc_start, GAMElgc_on, GAMElgc_off } GAMElgc_state;
int GAMElgc_Tick(int state) {
  // Local variables
	
  static unsigned short count = 0;

  // === Transitions ===
  switch(state) {
		case GAMEen_Start:
		  state = game_en? GAMEen_on:GAMEen_off;
			break;

		case GAMEen_on:
		  state = game_en? GAMEen_on:GAMEen_off;
			break;

                case GAMEen_off:
		  state = game_en? GAMEen_on:GAMEen_off;	
			break;
	
		default:
			state = GAMEen_Start;
			break;
	}

  // === Actions ===
  switch(state) {
		case GAMEen_Start:
		  game_on = 0;
			break;

		case GAMEen_on:
		  game_on = 1;
			break;

                case GAMEen_off:
		  game_on = 0;	
			break;
	
		default:
			state = GAMEen_Start;
			break;
	}
	return state;
};

//---------------------------Task3 LED--------------------------
enum LED_states { LED_start, LED_wait, LED_frame0, LED_frame1, LED_dot, LED_off } LED_state;
int LED_Tick(int state) {
  // Local variables
	
  static unsigned short count = 0;

  // === Transitions ===
  switch(state) {
		case LED_start:
		  state = LED_wait;
			break;

		case LED_wait:
		  state = frame? LED_frame1:LED_frame0;	
			break;

                case LED_frame0:
		  state = frame? LED_frame1:LED_frame0;	
			break;

	        case LED_frame1:
		  state = frame? LED_frame1:LED_frame0;	
			break;

		default:
			state = LED_start;
			break;
	}

  // === Actions ===
    switch(state) {
		case LED_start:
		  send(0xfff7);
		  send(0x38eb);
		  send(0x3cab);
		  send(0x34eb);
		  send(0x1ceb);
		  send(0x3ccb);
		  send(0x3ce9);
		  send(0xfffe); 
		  clearreg();
		  send(0x6b7b);
		  send(0x677b);
		  send(0xad3f);
		  send(0x8d7f);
		  send(0x6f5b);
		  send(0x6f79);
		  clearreg();
			break;

		case LED_wait:
		   clearreg();	
			break;

                case LED_frame0:
		  state = frame? LED_frame1:LED_frame0;	
			break;

	        case LED_frame1:
		  state = frame? LED_frame1:LED_frame0;	
			break;

		default:
			state = LED_start;
			break;
	}
	return state;
};
//---------------------------Task4 LCD-----------------------------------
enum LCD_Displaystates {LCD_Start, LCD_Wait, LCD_Play, LCD_Pause, LCD_UpdateScore, LCD_UpdateLife, 
						LCD_WinLevel, LCD_LoseLevel, LCD_WinGame, LCD_LoseGame} LCD_Displaystate;
int LCDDisplay_Tick(int state) {
	// Local variables
	static unsigned short winCount = 0;
	static unsigned short loseCount = 0;

	// === Transitions ===
	switch(state) {
		case LCD_Start:
			highscore = eeprom_read_word((uint16_t*) 46);
			LCD_DisplayString(1, "BrickBreaker");
			LCD_AppendString(17, "High Score: ");
			LCD_WriteData('0' + ((highscore % 1000) / 100));
			LCD_WriteData('0' + ((highscore % 100) / 10));
			LCD_WriteData('0' + (highscore % 10));
			if (P)
				state = LCD_Start;
			else
				state = LCD_Play;
			break;
		case LCD_Wait:
			if (GameOver)
				state = LCD_LoseGame;
			else if (GameWon)
				state = LCD_WinGame;
			else if (LevelWon)
				state = LCD_WinLevel;
			else if (LevelLost)
				state = LCD_UpdateLife;
			else if (updateScore)
				state = LCD_UpdateScore;
			else if (P)
				state = LCD_Pause;
			else
				state = LCD_Wait;
			break;
		case LCD_Play:
			state = LCD_Wait;
			break;
		case LCD_Pause:
			if (P) 
				state = LCD_Pause;
			else
				state = LCD_Play;
			break;
		case LCD_UpdateScore:
			updateScore = 0;
			state = LCD_Wait;
			break;
		case LCD_UpdateLife:
			state = LCD_LoseLevel;
			break;
		case LCD_WinLevel:
			if (currentLevel == 4)
				state = LCD_WinGame;
			else if (LevelWon)
				state = LCD_WinLevel;
			else
				state = LCD_Play;
			break;
		case LCD_LoseLevel:
			if (LevelLost)
				state = LCD_LoseLevel;
			else
				state = LCD_Play;
			break;
		case LCD_WinGame:
			if (winCount <= 19) { // 500 * 20 = 10000ms
				winCount++;
				state = LCD_WinGame;
			} else {
				winCount = 0;
				if (score > highscore) {
					eeprom_update_word((uint16_t*) 46, score);					
				}
				score = 0;
				state = LCD_Start;
			}
			break;
		case LCD_LoseGame:
			if (loseCount <= 19) { // 500 * 20 = 10000ms
				loseCount++;
				state = LCD_LoseGame;
			} else {
				loseCount = 0;
				if (score > highscore) {
					eeprom_update_word((uint16_t*) 46, score);
				}
				for (int i = 0; i < 4; i++) {
					ClearRow(i);
				}
				score = 0;
				state = LCD_Start;
			}
			break;
		default:
			state = LCD_Start;
			break;
	}

	// === Actions ===
	switch(state) {
		case LCD_Start:
			break;
		case LCD_Wait:
			break;
		case LCD_Play:
			LCD_DisplayString(1, "Lives: ");
			LCD_WriteData('0' + numLives);
			LCD_AppendString(17, "Score: ");
			LCD_WriteData('0' + ((score % 1000) / 100));
			LCD_WriteData('0' + ((score % 100) / 10));
			LCD_WriteData('0' + (score % 10));
			break;
		case LCD_Pause:
			LCD_DisplayString(1, "PAUSED");
			break;
		case LCD_UpdateScore:
			LCD_Cursor(24);
			LCD_WriteData('0' + ((score % 1000) / 100));
			LCD_WriteData('0' + ((score % 100) / 10));
			LCD_WriteData('0' + (score % 10));
			break;
		case LCD_UpdateLife:
			LCD_Cursor(8);
			LCD_WriteData('0' + numLives);
			break;
		case LCD_WinLevel:
			LCD_DisplayString(1, "Level Complete!");
			break;
		case LCD_LoseLevel:
			LCD_DisplayString(1, "Lost a life!");
			break;
		case LCD_WinGame:
			LCD_DisplayString(1, "Congratulations! You Won!");
			break;
		case LCD_LoseGame:
			LCD_DisplayString(1, "GAME OVER");
			break;
		default:
			break;
	}
	return state;
}

//---------------------------Task5 INPUT--------------------------
enum INPUT_states {INPUT_start, INPUT_wait} input_state;

int INPUT_Tick(int state) {
	// Local variables
	
	unsigned short joyx = ADC_Read(0);
	unsigned short joyy = ADC_Read(1);

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
			
		  if(joyx>=750){
		    right = 1;
		    left = 0;
		  }
		  if(joyx<=250){
		    left = 1;
		    right = 0;
		  }
		  if(joyy>=750){
		    up = 1;
		    down = 0;
		  } 
		  if(joyy<=250){
		    down = 1;
		    up = 0;
		  }
		  break;
		
		 
		default:
		  break;
	}

	return state;
};



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


