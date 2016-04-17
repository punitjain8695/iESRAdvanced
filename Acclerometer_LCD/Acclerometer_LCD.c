#include<avr/io.h>
#define F_CPU 16000000UL
#include<util/delay.h>
#include<avr/lcd.h>
#include<avr/adc.h>

main()
{
int i=0,j=0,k=0;
DDRA=0;
DDRC=255;
lcd_init();
adc_init();

lcd_command(0x80);
lcd_data('X');

lcd_command(0x89);
lcd_data('Y');

lcd_command(0xc0);
lcd_data('Z');

while(1)
{
i=adc_read(0);
j=adc_read(1);
k=adc_read(2);

lcd_command(0x87);
lcd_number(i);

lcd_command(0x8e);
lcd_number(j);

lcd_command(0xcb);
lcd_number(k);

_delay_ms(1000);
}

}
