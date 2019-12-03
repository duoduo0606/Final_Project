/*
 * ADC_H.h
 *
 * Created: 7/28/2016 4:50:16 PM
 *  Author: User
 */ 


#ifndef ADC_H
#define ADC_H

//#define F_CPU 8000000UL					/* Define CPU Frequency e.g. here its 8 Mhz */
#include <avr/io.h>						/* Include AVR std. library file */
#include <util/delay.h>
#define ipin PINA
#define iport PORTA

void ADC_init();
int ADC_Read(char);

#endif /* ADC_H */
