#include<avr/io.h>
#define F_CPU 16000000UL
#include<util/delay.h>
#include<avr/lcd.h>
#define baud 9600
#define UBRR ((F_CPU/(16UL*baud)) -1)
#include<avr/interrupt.h>


usart_init()
{
UBRRL=UBRR;
UBRRH=(UBRR>>8);
UCSRB=(1<<RXEN)|(1<<TXEN)|(1<<RXCIE);
UCSRC=(1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);
}

usart_tx(char data)
{
while((UCSRA&0b00100000)==0);
UDR=data;
}

char usart_rx()
{
while((UCSRA&0b10000000)==0);
return UDR;
}

void main()
{
DDRC=255;
DDRB=255;
lcd_init();
sei();
lcd_command(0x80);
//lcd_data('A');
usart_init();
char i;
while(1)
{
i++;
//i=usart_rx();
//lcd_command(0x80);
usart_tx(i);
//lcd_data('A');


_delay_ms(1000);
PORTB=255;
_delay_ms(20);
PORTB=0;

}

}

/*ISR(USART_RXC_vect)
{
char c=UDR;

lcd_data(c);
if(c=='F')
{PORTB=0b00000001;}

if(c=='B')
{PORTB=0b00000010;}

//usart_tx(c);
}*/
