#include<avr/io.h>
#define F_CPU 16000000UL
#include<util/delay.h>
#include<avr/lcd.h>
#include<avr/eeprom.h>

main()
{
DDRC=255;
lcd_init();
int j=0;
int i=99999;
eeprom_write_word(0x001,i);
j=eeprom_read_word(0x001);
lcd_command(0x8f);
lcd_number(j);

}
