#include <avr/io.h>
#include "timer.h"

#define SHIFT_DDR DDRD
#define SHIFT_PORT PORTD
#define DATA 3
#define LATCH 4
#define CLOCK 5
#define uc unsigned char


void sendrow(unsigned char value)
{
unsigned short i = 0;
	for ( i = 0; i < 8; i++)
	{
	
			if (value & 0x80)
			{
				SHIFT_PORT = SHIFT_PORT | (0x01<<DATA);
			}
			else
			{
				SHIFT_PORT = SHIFT_PORT & ~(0x01<<DATA);
			}
		
		value = value << 1;
		// clock pin high
		SHIFT_PORT = SHIFT_PORT | (0x01<<CLOCK);
		// clock pin low
		SHIFT_PORT = SHIFT_PORT & ~(0x01<<CLOCK);
	}
	// load pin high
	SHIFT_PORT = SHIFT_PORT | (0x01<<LATCH);
	// load pin low
	SHIFT_PORT = SHIFT_PORT & ~(0x01<<LATCH);
}
