#include<avr/io.h>
#define F_CPU 16000000UL
#include<util/delay.h>
#include<avr/interrupt.h>
int x=0;
//Interrupt

main()
{
DDRA=0;
DDRB=255;
DDRD=0;
PORTD=0xff;
TCCR0=(1<<CS01);
TCNT0=0;
TIMSK=(1<<TOIE0);
sei();
GICR=(1<<INT0);
MCUCR=(1<<ISC01);
while(1)
{
PORTB=0xf0;
}
}

ISR(TIMER0_OVF_vect)
{
x++;
if(x==397)
{
PORTB=~PORTB;
_delay_ms(50);
}

}
