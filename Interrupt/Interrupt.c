#include<avr/io.h>
#define F_CPU 16000000UL
#include<util/delay.h>
#include<avr/interrupt.h>

//Interrupt

main()
{
DDRA=0;
DDRB=255;
DDRD=0;
PORTD=0xff;
sei();
GICR=(1<<INT0);
MCUCR=(1<<ISC01);
while(1)
{
PORTB=0xf0;
_delay_ms(100);
}
}

ISR(INT0_vect)
{
PORTB=~PORTB;
_delay_ms(500);
}
