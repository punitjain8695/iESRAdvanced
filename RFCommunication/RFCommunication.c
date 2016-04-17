#include<avr/io.h>
#define F_CPU 16000000UL
#include<util/delay.h>
int main()
{
DDRB=255;
DDRD=0xf0;
while(1)
{
PORTD=0xef;
if((PIND&0x01)==0)
{
while((PIND&0x01)==0);
while((PIND&0x0f)==0x0f)
{
PORTB=0b00000110;
}
}

if((PIND&0x02)==0)
{
while((PIND&0x02)==0);
while((PIND&0x0f)==0x0f)
{
PORTB=0b00000100;
}
}

if((PIND&0x04)==0)
{
while((PIND&0x04)==0);
while((PIND&0x0f)==0x0f)
{
PORTB=0b00000010;
}
}

if((PIND&0x08)==0)
{
while((PIND&0x08)==0);
while((PIND&0x0f)==0x0f)
{
PORTB=0b00001001;
}
}
else
{
PORTB=0;
}

}
return 0;
}
