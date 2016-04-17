#include<avr/io.h>
#define F_CPU 16000000UL
#include<util/delay.h>

void main()
{
DDRB=255;
DDRA=0;
PORTB=0;
_delay_ms(10);
while(1)
{
if((PINA&0x0f)==0x02)
{
PORTB=0b00000101;
}

if((PINA&0x0f)==0x04)
{
PORTB=0b00000110;
}

if((PINA&0x0f)==0x06)
{
PORTB=0b00001001;
}

if((PINA&0x0f)==0x08)
{
PORTB=0b00001010;
}

if((PINA&0x0f)==0x05)
{
PORTB=0b00000000;
}

if((PINA&0x0f)==0x01)
{
PORTB=0b00000100;
}

if((PINA&0x0f)==0x03)
{
PORTB=0b00000001;
}

if((PINA&0x0f)==0x07)
{
PORTB=0b00001000;
}

if((PINA&0x0f)==0x09)
{
PORTB=0b00000010;
}

else
{
PORTB=0;
}
}


}
