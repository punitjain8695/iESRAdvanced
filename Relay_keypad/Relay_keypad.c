#include<avr/io.h>
#define F_CPU 16000000UL
#include<util/delay.h>

main()
{
DDRB=255;
DDRD=0xf0;
PORTB=0;
PORTD=0xef;
_delay_ms(10);

while(1)
{

if((PIND&0x01)==0)
{
while((PIND&0x01)==0);
while((PIND&0x0f)==0x0f)
{
PORTB|=0x01;
}
}

if((PIND&0x02)==0)
{
while((PIND&0x02)==0);
while((PIND&0x0f)==0x0f)
{
PORTB&=0x02;
}
}

if((PIND&0x04)==0)
{
while((PIND&0x04)==0);
while((PIND&0x0f)==0x0f)
{
PORTB|=0x02;
}
}
if((PIND&0x08)==0)
{
while((PIND&0x08)==0);
while((PIND&0x0f)==0x0f)
{
PORTB&=0x01;
}
}

}
}
