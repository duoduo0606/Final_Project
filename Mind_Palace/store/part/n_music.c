/*	Author: yxing024
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

#include "timer.h"
#include "pwm.h"


enum States {OFF, PLAY} state;
unsigned short system_period = 160; 
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

unsigned char notes_number = 58;
unsigned char position = 0, count = 0;

void Tick()
{
 
  double music_notes[] = {e4,a4,b4,c5,b4,a4,f4,0,f4,a4,b4,c5,b4,a4,e4,0,e4,a4,b4,c5,b4,a4,f4,0,d5,c5,b4,c5,b4,a4,e4,0,  f5,e5,d5,e5,d5,c5, a4,b4, e5,d5,c5,d5,c5,b4, a4,0 ,f5,e5,d5,e5,d5,c5,a4,b4,e5  };
  unsigned char note_length[] = {n8,n8,n8,n8,n8,n8,th,n8, n8,n8,n8,n8,n8,n8,th,n8, n8,n8,n8,n8,n8,n8,th,n8, n8,n8,n8,n8,n8,n8,th,n8, n8,n8,n8,n8,n8,n8,n2,n4, n8,n8,n8,n8,n8,n8,th,n8,n8,n8,n8,n8,n8,n8,n2,n4,whole};

  unsigned char tempA = (~PINA & 0x08) >> 3;
    
    switch(state)
    {
        case OFF:
        if(tempA == 0x01){
            state = PLAY;
        }
        else{
            state = OFF;
        }
        break;
        case PLAY:
        if( (position >=notes_number) && (count >= note_length[position])){
            state = OFF;
        }
        break;
        default:
        state = OFF;
        break;
    }
    
    switch(state)
    {
        case OFF:
            set_PWM(0);
            count = 0;
            position = 0;
        break;
        case PLAY:
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
}

int main()
{
    DDRA = 0xc0; PORTA = 0x3F;
    DDRB = 0xFF; PORTB = 0x00;
 
    
    
    PWM_on();
    set_PWM(0);
   
    TimerSet(system_period);
    TimerOn();
    
    state = OFF;
    TimerFlag = 0;
    count = 0;
    position = 0;
    while (1)
    {
        Tick();
        // Input is reversed to be activated on low, so we need to bitwise inverse PINA to get the same kind of logic as usual.
        while(!TimerFlag);
        TimerFlag = 0;       
    }
    return 0;
}
