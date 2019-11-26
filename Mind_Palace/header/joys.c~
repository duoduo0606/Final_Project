#include <avr/io.h>
#include "timer.h"

#define SHIFT_DDR DDRD
#define SHIFT_PORT PORTD
#define DATA 0
#define LATCH 1
#define CLOCK 2
#define uc unsigned char


void send(unsigned short value)
{
unsigned short i = 0;
	for ( i = 0; i < 16; i++)
	{
		if (i < 8) {
			if (value & 0x8000)
			{
				SHIFT_PORT = SHIFT_PORT | (0x0001<<DATA);
			}
			else
			{
				SHIFT_PORT = SHIFT_PORT & ~(0x0001<<DATA);
			}
		}
		else {
			if (value & 0x8000) {
				SHIFT_PORT = SHIFT_PORT | (0x0001<<DATA);
			}
			else 
			{
			
				SHIFT_PORT = SHIFT_PORT & ~(0x0001<<DATA);
			}
		}
		value = value << 1;
		// clock pin high
		SHIFT_PORT = SHIFT_PORT | (0x0001<<CLOCK);
		// clock pin low
		SHIFT_PORT = SHIFT_PORT & ~(0x0001<<CLOCK);
	}
	// load pin high
	SHIFT_PORT = SHIFT_PORT | (0x0001<<LATCH);
	// load pin low
	SHIFT_PORT = SHIFT_PORT & ~(0x0001<<LATCH);
}


void clearreg()
{
 unsigned short i = 0;
	for ( i = 0; i < 16; i++)
	{
	
	
	  SHIFT_PORT = SHIFT_PORT & ~(0x0001<<DATA);
		
	
	
		// clock pin high
		SHIFT_PORT = SHIFT_PORT | (0x0001<<CLOCK);
		// clock pin low
		SHIFT_PORT = SHIFT_PORT & ~(0x0001<<CLOCK);
	}
	// load pin high
	SHIFT_PORT = SHIFT_PORT | (0x0001<<LATCH);
	// load pin low
	SHIFT_PORT = SHIFT_PORT & ~(0x0001<<LATCH);
}
