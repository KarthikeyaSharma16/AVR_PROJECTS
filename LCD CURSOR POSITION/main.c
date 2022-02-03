/*
 * LCD_CursorPosition.c
 *
 * Created: 2/2/2022 2:24:30 PM
 * Author : karth
 */ 

#define  F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>

#define lcd_port PORTC

#define RS_high() PORTA |= (1<<0);
#define RS_low() PORTA &= ~(1<<0);

#define EN_high() PORTA |= (1<<1);
#define EN_low() PORTA &= ~(1<<1);

void lcd_pos(int m, int n)
{
	if(m == 1)
	{
		lcd_cmd(0x80 + n);
	}
	else if(m == 2)
	{
		lcd_cmd(0xc0 + n);
	}
}

void lcd_cmd(unsigned char cmd)
{
	lcd_port = cmd;
	RS_low();
	EN_high();
	_delay_ms(1);
	EN_low();	
}

void lcd_data(unsigned char dat)
{
	lcd_port = dat;
	RS_high();
	EN_high();
	_delay_ms(1);
	EN_low();
}

void lcd_init()
{
	lcd_cmd(0x38); _delay_ms(5);
	lcd_cmd(0x02); _delay_ms(5);
	lcd_cmd(0x01); _delay_ms(5);
	lcd_cmd(0x0c); _delay_ms(5);
	lcd_cmd(0x06); _delay_ms(5);
}

int main(void)
{
    DDRC = 0xff;
	DDRA = 0x11;
	
	lcd_init();
	
    lcd_pos(2,4);
	lcd_data('i');
	
	lcd_pos(1,6);
	lcd_data('H');
	
}

