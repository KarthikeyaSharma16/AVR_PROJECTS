/*
 * DisplayingMessageonLCDbygivingdigitalinput.c
 *
 * Created: 2/1/2022 10:54:50 PM
 * Author : karth
 */ 

/*
 * LED+LCDDisplayInterfacing.c
 *
 * Created: 2/1/2022 10:07:35 PM
 * Author : karth
 */ 

#include <avr/io.h>
#define F_CPU 16000000L
#include <util/delay.h>
#include <string.h>

//Make RS go high to activate the data register, make RS go low to activate the command register
#define RS_high() PORTA |= (1<<0);
#define RS_low() PORTA &= ~(1<<0);

//Make Enable pin of the micro-controller pin go high and low
#define EN_high() PORTA |= (1<<1);
#define EN_low() PORTA &= ~(1<<1);

#define lcd_port PORTC 

void lcd_init()
{
	//Delay ensures proper working of LCD
	lcd_com(0x38); _delay_ms(5); //2 lines and 5x7 matrix (character)
	lcd_com(0x02); _delay_ms(5); //Return home
	lcd_com(0x01); _delay_ms(5); //Clear lcd display screen
	lcd_com(0x0C); _delay_ms(5); //Display ON cursor OFF
	lcd_com(0x06); _delay_ms(5); //Increment cursor
	lcd_com(0x80); _delay_ms(5); //Force cursor to the beginning of the first line
}

void lcd_com(unsigned char cmd)
{
	lcd_port = cmd; //pass the command to the LCD port
	RS_low(); //Make RS go low to activate the command register.
	EN_high(); //Enable pin is set to high so that the LCD display reads the data received and executes the command.
	_delay_ms(1);
	EN_low(); //The LCD display doesn't care about R/W, RS and data lines whenever enable is low.
}

void lcd_data (unsigned char dat)
{
	lcd_port = dat; //pass the data to the LCD port
	RS_high(); //Make RS go high to activate the data register to print out the data.
	EN_high(); //Enable pin is set to high so that the LCD display reads the data received and executes the command.
	_delay_ms(1);
	EN_low();  //The LCD display doesn't care about R/W, RS and data lines whenever enable is low.
}

void lcd_init_2()
{
	lcd_com(0xC0);
}

void lcd_clear()
{
	lcd_com(0x01);
}

int main(void)
{
    DDRC = 0xff;
	DDRA = 0x03;
	DDRB &= ~(1<<2);
	
	lcd_init();
	
	char msg1[] = "RELEASE SWITCH TO TURN OFF";
	int length = strlen(msg1);
	int ii;
	
    while (1)
	{
		if(PINB & 0x04)
		{
			for (ii = 0; ii<length; ii++)
			{
				if (ii < 15)
				{
					lcd_data(msg1[ii]);
				}
				else if (ii == 15)
				{
				    lcd_init_2();
					lcd_data(msg1[ii]);	
				}
				else
				{
					lcd_data(msg1[ii]);
				}
		    }
        }
		else
		{
			lcd_clear();
		}
		lcd_com(0x02);
    }
}


