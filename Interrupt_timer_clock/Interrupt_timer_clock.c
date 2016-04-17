#include<avr/io.h>
#define F_CPU 16000000UL
#include<util/delay.h>
#include<avr/interrupt.h>
#include<avr/lcd.h>
int x=0,sec=0,min=0,hr=0;
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
DDRC=255;
lcd_init();
lcd_command(0x85);
lcd_data(':');
lcd_command(0x8A);
lcd_data(':');
lcd_command(0x8E);
lcd_data('S');
lcd_command(0x89);
lcd_data('M');
lcd_command(0x84);
lcd_data('H');

//GICR=(1<<INT0);
//MCUCR=(1<<ISC01);
while(1)
{
PORTB=0xf0;
lcd_command(0x8C);
lcd_num(sec);
lcd_command(0x87);
lcd_number(min);
lcd_command(0x82);
lcd_number(hr);
}
}



ISR(TIMER0_OVF_vect)
{
x++;
if(x==7500)
{
PORTB=~PORTB;
_delay_ms(35);
x=0;

sec++;
if(sec==60)
{
sec=0;
min++;
if(min==60)
{
min=0;
hr++;
}
}
}

}
