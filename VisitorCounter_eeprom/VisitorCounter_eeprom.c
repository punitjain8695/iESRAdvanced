#include<avr/io.h>
#define F_CPU 16000000UL
#include<util/delay.h>
#include<avr/lcd.h>
#include<avr/eeprom.h>
int i;

void main()
{

char A[11];
DDRC=255;
DDRA=0;
lcd_init();
lcd_command(0x80);
eeprom_write_block("Sensor In :",0x000,11);
eeprom_read_block(A,0x000,11);
A[11]='\0';
lcd_string(A);
i=eeprom_read_word(0x100);
lcd_command(0x8f);
lcd_number(i);

while(1)
{
if((PINA&0x01)==1)
{
while((PINA&0x01)==1);
i++;
eeprom_write_word(0x100,i);
lcd_command(0x8f);
lcd_number(i);
}
}
}
