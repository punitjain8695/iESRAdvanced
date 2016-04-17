#include<avr/io.h>
#define F_CPU 16000000UL
#include<util/delay.h>
#include<avr/lcd.h>
#include<avr/adc.h>
#define on 50

main()
{
int i=0,j=0,k=0;
DDRA=0;
DDRB=255;
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

//k=adc_read(2);

lcd_command(0x88);
lcd_number(i);

lcd_command(0x8f);
lcd_number(j);

//lcd_command(0xcc);
//lcd_number(k);


if((i>250&&i<390)&&(j> 300&& j< 500))
{
//go forward
PORTB=0b00000101;
_delay_ms(on);
}
if((i>450 &&i< 515)&&(j> 300&& j< 500))
{
//go back
PORTB=0b00001010;
_delay_ms(on);
}
if((i> 300&&i< 600)&&(j>300 && j< 385))
{
//go left
PORTB=0b00000100;
_delay_ms(on);
}
if((i>  300&&i< 600)&&(j> 450&& j<550 ))
{
//go right
PORTB=0b00000001;
_delay_ms(on);
}
if(((i> 520&&i< 600)&&(j>300 && j< 500))||((i> 390&&i< 420)&&(j>390 && j< 450)))
{
//be still
PORTB=0b00000000;
_delay_ms(on);
}
/*else
{
//be still
PORTB=0b00000000;
_delay_ms(on);
}
*/

}

}
