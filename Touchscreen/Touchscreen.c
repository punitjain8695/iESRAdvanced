#include<avr/io.h>
#define F_CPU 16000000UL
#include<util/delay.h>
#include<avr/lcd.h>
#include<avr/adc.h>

main()
{

DDRC=255;
lcd_init();
adc_init();
int x=0,y=0;
while(1)
{
DDRA=0b00000101;
PORTA=0b00000100;
_delay_ms(10);
x=adc_read(3);

DDRA=0b00001010;
PORTA=0b00001000;
_delay_ms(10);
y=adc_read(2);

lcd_command(0x8f);
lcd_number(x);

lcd_command(0xcf);
lcd_number(y);
_delay_ms(100);


}


}
