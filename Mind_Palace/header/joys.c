#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "io.c"
#include "ADC.c"

int joys(void)
{
	char buffer1[20];
	char buffer2[20];
	int ADC_Value;
	
	ADC_Init();						
	LCD_init();						

	while(1)
	{
		ADC_Value = ADC_Read(0);	
		sprintf(buffer1, "X=%d   ", ADC_Value);
		LCD_DisplayString(1, buffer1);
		
		ADC_Value = ADC_Read(1);	
		sprintf(buffer2, "Y=%d   ", ADC_Value);
		LCD_DisplayString(2, buffer2);
	
	}
}
