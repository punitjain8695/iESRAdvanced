#include<avr/io.h>
#define F_CPU 16000000UL
#include<util/delay.h>
#include<avr/lcd.h>
#include<string.h>
#include<avr/eeprom.h>

unsigned char loc=0x80;
char A[16];
char B[16];
char D[16];
int c=0;
int z=0;
int choice=0;;
int al;
int bl;
int i;
int set;
int p=0;
char e=0x030;

int button(char ch)
{
int z=0;
while((PIND&ch)==0);
for(int i=0;i<750;i++)
{
_delay_ms(1);
if((PIND&ch)==0)
{
while((PIND&ch)==0);
z++;
if(z==4){z=0;}
}
}
loc++;
return z;
}


void passinput()
{
_delay_ms(1000);
lcd_command(0x01);
lcd_command(0x80);
c=0;
while(1)
{
z=0;
lcd_command(loc);
//	1st row
PORTD=0xef;
_delay_ms(10);
if((PIND&0x01)==0)
{
z=button(0x01);
if(z==3)
{
lcd_data(49);
A[c]=49;
c++;
}
else 
{
lcd_data(65+z);
A[c]=65+z;
c++;
}
}

if((PIND&0x02)==0)
{
z=button(0x02);
if(z==3)
{
lcd_data(50);
A[c]=50;
c++;
}
else 
{
lcd_data(68+z);
A[c]=68+z;
c++;
}
}

if((PIND&0x04)==0)
{
z=button(0x04);
if(z==3)
{
lcd_data(51);
A[c]=51;
c++;
}
else 
{
lcd_data(71+z);
A[c]=71+z;
c++;
}
}

if((PIND&0x08)==0)
{
while((PIND&0x08)==0);
lcd_command(0x04);
loc--;
c--;
A[c]='\0';
lcd_command(loc);
lcd_data(' ');
lcd_command(loc);
lcd_command(0x06);
}

//	2nd row
PORTD=0xdf;
_delay_ms(10);
if((PIND&0x01)==0)
{
z=button(0x01);
if(z==3)
{
lcd_data(52);
A[c]=52;
c++;
}
else 
{
lcd_data(74+z);
A[c]=74+z;
c++;
}
}

if((PIND&0x02)==0)
{
z=button(0x02);
if(z==3)
{
lcd_data(53);
A[c]=53;
c++;
}
else 
{
lcd_data(77+z);
A[c]=77+z;
c++;
}
}

if((PIND&0x04)==0)
{
z=button(0x04);
if(z==3)
{
lcd_data(54);
A[c]=54;
c++;
}
else 
{
lcd_data(80+z);
A[c]=80+z;
c++;
}
}

if((PIND&0x08)==0)
{
while((PIND&0x08)==0);
choice=1;
break;
}


//	3rd row
PORTD=0xbf;
_delay_ms(10);

if((PIND&0x01)==0)
{
z=button(0x01);
if(z==3)
{
lcd_data(55);
A[c]=55;
c++;
}
else 
{
lcd_data(83+z);
A[c]=83+z;
c++;
}
}

if((PIND&0x02)==0)
{
z=button(0x02);
if(z==3)
{
lcd_data(56);
A[c]=56;
c++;
}
else 
{
lcd_data(86+z);
A[c]=86+z;
c++;
}
}

if((PIND&0x04)==0)
{
z=button(0x04);
if(z==2)
{
lcd_data(57);
A[c]=57;
c++;
}
else 
{
lcd_data(89+z);
A[c]=89+z;
c++;
}
}

if((PIND&0x08)==0)
{
while((PIND&0x08)==0);
choice=3;
goto stop;
}



//	4th row
PORTD=0x7f;
_delay_ms(10);
if((PIND&0x01)==0)
{
z=button(0x01);
lcd_data('*');
}
if((PIND&0x02)==0)
{
z=button(0x02);
lcd_data(48);
}
if((PIND&0x04)==0)
{
z=button(0x04);
lcd_data('#');
}
if((PIND&0x08)==0)
{
choice=4;
break;
}

}
stop: 
lcd_command(0x01);
}


int main()
{
DDRD=0xf0;
DDRC=255;
lcd_init();

DDRB=255;
PORTB=0;

while(1)
{
passinput();
if(choice==1)
{
lcd_command(0x01);
lcd_command(0x80);
_delay_ms(1000);
lcd_string("Enter Password");
_delay_ms(1000);
lcd_command(0x01);
lcd_command(0x80);
passinput();
set=eeprom_read_byte(0x072);
if(set!=1)
{
choice=2;
al=strlen(A);
eeprom_write_block(0x060,A,al);
eeprom_write_byte(0x070,al);
lcd_command(0x01);
lcd_command(0x80);
lcd_string(A);
_delay_ms(1000);
lcd_command(0x01);
lcd_command(0x80);
int t=0;
t=eeprom_read_byte(0x070);
lcd_number(t);
_delay_ms(1000);

e=0x030;
for(i=0;i<=al;i++)
{
eeprom_write_byte(e,A[i]);
e++;
}
e=0x030;
for(i=0;i<=al;i++)
{
A[i]='\0';
B[i]=eeprom_read_byte(e);
e++;
}

_delay_ms(1000);
lcd_command(0x01);
lcd_command(0x80);
lcd_string(B);

_delay_ms(1000);
lcd_command(0x01);
lcd_command(0x80);
lcd_string("password set");


set=1;
eeprom_write_byte(0x072,set);
}
}

if(choice==2)
{
_delay_ms(1000);
lcd_command(0x01);
lcd_command(0x80);
lcd_string(A);
_delay_ms(1000);
lcd_command(0x01);
lcd_command(0x80);
passinput();
}

if(choice==3)
{
al=strlen(A);
bl=eeprom_read_byte(0x070);
e=0x030;
for(i=0;i<bl;i++)
{
B[i]=eeprom_read_byte(e);
e++;
}

lcd_command(0x01);
lcd_command(0x80);
lcd_string("Checking password");
_delay_ms(1000);
lcd_command(0x01);
lcd_command(0x80);
if(al==bl)
{
lcd_command(0x01);
lcd_command(0x80);
lcd_string("Length Matched");
_delay_ms(1000);
lcd_command(0x01);
lcd_command(0x80);
for (i=0;i<al;i++)
{
_delay_ms(1000);
lcd_command(0x01);
lcd_command(0x81);
lcd_data(A[i]);
lcd_command(0x89);
lcd_data(B[i]);

if(A[i]==B[i])
{
p++;
}
else;
}
if(p==al)
{
_delay_ms(1000);
lcd_command(0x01);
lcd_command(0x80);
lcd_string("Password Matched");
PORTB=255;
_delay_ms(1000);
lcd_command(0x01);
lcd_command(0x80);
lcd_string("*:Change Password");
_delay_ms(1000);
lcd_command(0x01);
lcd_command(0x80);
lcd_string("#:Unlock");
_delay_ms(1000);
PORTB=0;
PORTD=0x7f;
while((PIND&0x0f)==0x0f);
while(1)
{
if((PIND&0x01)==0)
{
while((PIND&0x01)==0);
PORTB=0b10101010;
_delay_ms(1000);
PORTB=0b01010101;
set=2;
eeprom_write_byte(0x072,set);
choice=1;
break;
}
if((PIND&0x04)==0)
{
while((PIND&0x04)==0);
PORTB=255;
lcd_command(0x01);
lcd_command(0x80);
lcd_string("Access Granted");
break;
}
}
}

else if(p!=al)
{
_delay_ms(1000);
lcd_command(0x01);
lcd_command(0x80); 
lcd_string("Wrong Password");
choice=4;
}
}
else 
{
lcd_string("Wrong Password");
choice=4;}
}

if(choice==4)
{
_delay_ms(1000);
lcd_command(0x01);
lcd_command(0x80);
_delay_ms(1000);
lcd_string("Enter Password");
_delay_ms(1000);
lcd_command(0x01);
lcd_command(0x80);
passinput();
}
}
passinput();
return 0;
}

