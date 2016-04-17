#include<avr/io.h>
#define F_CPU 16000000UL
#include<util/delay.h>
#include<avr/lcd.h>
#include<avr/adc.h>


main()
{

int RPM=0;
DDRC=255;
lcd_init();
DDRA=0;

DDRB&=~(1<<PB0);

while(1)
{
PORTB=255;
TCNT0=0;
_delay_ms(1000);
RPM=TCNT0*60;
lcd_command(0x87);
lcd_number(RPM);

}

}
