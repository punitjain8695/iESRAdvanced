#include<avr/io.h>
#define F_CPU 16000000UL
#include<util/delay.h>
#include<avr/lcd.h>
#include<avr/adc.h>

main()
{
DDRB=255;
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

if((x>450&&x<550)&&(y>470&&y<570))
{
PORTB=0;
}

if((x>100&&x<300)&&(y>400&&y<550))
{
PORTB=0b00000101;
}

if((x>800&&x<1000)&&(y>400&&y<550))
{
PORTB=0b00001010;
}

if((x>500&&x<700)&&(y>100&&y<300))
{
PORTB=0b00000001;
}

if((x>500&&x<700)&&(y>700&&y<900))
{
PORTB=0b00000100;
}

}


}
