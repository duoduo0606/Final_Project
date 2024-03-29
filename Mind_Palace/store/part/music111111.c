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

#include "timer.h"
#include "pwm.h"


enum States {OFF, PLAY} state;
unsigned short system_period = 20; // 1/16th of a second is 62.5 ms, just round to 63;
//unsigned char bpm = 120; // 2 beats per second
//unsigned char bpm = 60; // Let's start with 1 beat per second to make it easy and adjust later maybe.
unsigned char eigth = 2 ; // ticks per note
unsigned char quarter = 6; // ticks per note 
unsigned char half = 8; // ticks per note 
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

unsigned char notes_number = 12;
unsigned char position = 0, count = 0;

void Tick()
{
    double music_notes[] = {g5,f5,a4,b4,e5,d5,f4,g4,d5,c5,e4,g4,c5};
    unsigned char note_length[] = {quarter,quarter,half,half,quarter,quarter,half,half,quarter,quarter,half,half,whole};

    unsigned char tempA = (~PINA & 0x01);
    
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
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    DDRD = 0xFF; PORTD = 0x00;
    
    
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
