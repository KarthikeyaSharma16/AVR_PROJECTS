/*
 * TASK-3.c
 *
 * Created: 2/3/2022 11:59:24 AM
 * Author : karth
 */ 

#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 16000000L
#include <string.h>

#define RS_high() PORTA |= (1<<0);
#define RS_low() PORTA &= ~(1<<0);

#define EN_high() PORTA |= (1<<1);
#define EN_low() PORTA &= ~(1<<1);

#define lcd_port PORTC

void lcd_init()
{
	lcd_cmd(0x38); _delay_ms(5);
	lcd_cmd(0x02); _delay_ms(5);
	lcd_cmd(0x01); _delay_ms(5);
	lcd_cmd(0x0c); _delay_ms(5);
	lcd_cmd(0x06); _delay_ms(5);
	lcd_cmd(0x80); _delay_ms(5);
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

void lcd_disp(unsigned int count)
{
	int count_2 = count;
	int ii, re, kk = 10000, num = 0;
	char arr[5];
	while (num < 5)
	{
		count_2 = count_2/kk;
		re = count_2%10;
		arr[num] = re + 48;
		num+=1;
		kk = kk/10;
		count_2 = count;
	}
	for (ii = 0; ii < 5; ii++)
	{
		lcd_data(arr[ii]);
	}
}

int main(void)
{
	DDRC = 0xff;
	DDRA = 0x11;
	DDRB &= ~(1<<2);
	DDRD &= ~(1<<2);
	DDRD &= ~(1<<3);
	
	lcd_init();
	int count = 0;
	
	char msg[] = "Up-Down Counter";
	int length = strlen(msg);
	int ii;
	for (ii = 0; ii< length; ii++)
	{
		lcd_data(msg[ii]);
	}
	
	
	while (1)
	{
		lcd_cmd(0xc0);
		if (PINB & 0x04)
		{
			count+=1;
			lcd_disp(count);
			_delay_ms(5000);
		}
		else if (PIND & 0x04)
		{
			count+=2;
			lcd_disp(count);
			_delay_ms(5000);
		}
		else if (PIND & 0x08)
		{
			count-=1;
			if (count < 0)
			{
				count = 0;
			}
			lcd_disp(count);
			_delay_ms(5000);
		}
		lcd_cmd(0x02);
	}
}

