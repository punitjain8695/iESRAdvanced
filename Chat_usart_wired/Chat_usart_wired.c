#include<avr/io.h>
#define F_CPU 16000000UL
#include<util/delay.h>
#include<avr/lcd.h>
#define baud 9600
#define UBRR ((F_CPU/(16UL*baud)) -1)
#define maxsize 16
#include<avr/interrupt.h>
char c[maxsize];
char d[maxsize];
char *str;
char t='\0';
unsigned char loc=0x80;
int i=0,j=0;

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

usart_string_tx(char *str)
{
int j=0;
while(str[j]!='\0')
{
//lcd_data(str[j]);
usart_tx(str[j]);
j++;
_delay_ms(10);
}
}

ISR(USART_RXC_vect)
{
c[i]=UDR;
i++;

if(c[i]=='*')
{
for(char k=0xc0; k<0xcf;k++)
{
lcd_command(k);
lcd_data(32);
}

lcd_command(0xc0);
lcd_string(c);

/*
j=0;
while(c[j]=='\0')
{
c[j]='\0';
j++;
}
*/

}
}

void print()
{
lcd_command(0xc0);
lcd_string(c);


j=0;
while(c[j]=='\0')
{
c[j]='\0';
j++;
}
}



int button(char ch)
{
int z=0;
while((PINA&ch)==0);
for(int i=0;i<750;i++)
{
_delay_ms(1);
if((PINA&ch)==0)
{
while((PINA&ch)==0);
z++;
if(z==4){z=0;}
}
}
loc++;
return z;
}

keypad()
{
int z=0;
lcd_command(loc);
//	1st row
PORTA=0xef;
_delay_ms(10);
if((PINA&0x01)==0)
{
z=button(0x01);
if(z==3){t = (49);}
else t = (65+z);
}
if((PINA&0x02)==0)
{
z=button(0x02);
if(z==3){t = (50);}
else t = (68+z);
}
if((PINA&0x04)==0)
{
z=button(0x04);
if(z==3){t = (51);}
else t = (71+z);
}
if((PINA&0x08)==0)
{
while((PINA&0x08)==0);
lcd_command(0x04);
loc--;
lcd_command(loc);
t = (' ');
lcd_command(loc);
lcd_command(0x06);
}

//	2nd row
PORTA=0xdf;
_delay_ms(10);
if((PINA&0x01)==0)
{
z=button(0x01);
if(z==3){t = (52);}
else t = (74+z);
}
if((PINA&0x02)==0)
{
z=button(0x02);
if(z==3){t = (53);}
else t = (77+z);
}
if((PINA&0x04)==0)
{
z=button(0x04);
if(z==3){t = (54);}
else t = (80+z);
}

//	3rd row
PORTA=0xbf;
_delay_ms(10);
if((PINA&0x01)==0)
{
z=button(0x01);
if(z==3){t = (55);}
else t = (83+z);
}
if((PINA&0x02)==0)
{
z=button(0x02);
if(z==3){t = (56);}
else t = (86+z);
}
if((PINA&0x04)==0)
{
z=button(0x04);
if(z==2){t = (57);}
else t = (89+z);
}

//	4th row
PORTA=0x7f;
_delay_ms(10);
if((PINA&0x01)==0)
{
z=button(0x01);
t = ('*');
}
if((PINA&0x02)==0)
{
z=button(0x02);
t = (48);
}
if((PINA&0x04)==0)
{
z=button(0x04);
t = ('#');
}

}


void main()
{
DDRC=255;
DDRA=0xf0;
lcd_init();
sei();
lcd_command(0x80);
usart_init();
char i;
start:
while(1)
{
keypad();

if(t=='#')
{
//lcd_command(0x01);
for(char k=0x80; k<0x8f;k++)
{
lcd_command(k);
lcd_data(32);
}

lcd_command(0x80);
loc=0x80;
t=32;
goto start;
}

if((t>64 && t<91)||(t>47&&t<57))
{
d[i]=t;
lcd_command(loc);
lcd_data(d[i]);
i++;
t=32;
}

if(t=='*')
{
lcd_command(loc);
lcd_data(d[i]);
d[i]=t;
usart_string_tx(d);
lcd_command(0x8f);
lcd_data('S');
j=0;
while(str[j]!='\0')
{
d[j]='\0';
j++;
}
}




//i=usart_rx();
//lcd_command(0x80);
//usart_tx(i);
//lcd_data('A');
}
}


