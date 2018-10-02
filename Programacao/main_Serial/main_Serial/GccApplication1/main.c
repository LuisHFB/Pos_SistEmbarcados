/*
 * GccApplication1.c
 *
 * Created: 29/09/2018 09:51:59
 * Author : Luis Bueno
 */ 

#include <avr/io.h>
#include <stdio.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include "defs.h"
#include "usart.h"
#include "defs.h"
#include "adc.h"
#include "lcd.h"

char matriz[20];
char *pot;
char aux = 0;

void decMatriz()
{
	if(matriz[0] == 'L' && matriz[1] == 'D')
	{
		switch (matriz[2])
		{
			case '0':
			if(matriz[3] == '0')
			{
				Set_bit(PORTB,5);
				}
				else
				{
				Clr_bit(PORTB,5);
			}
			break;
		}
	}
}

ISR(USART_RX_vect)
{
	char res;
	res = USART_Receive();
	if(res == '[')
	{
		pot = matriz; //Armazena o endereço da Matriz em Pot
		aux = 1;
	}else{
	if(aux == 1)
	{
		if((pot-matriz) < 20){
			*pot = res; //
			
			pot++;
		}
	}
	if(res == ']' && aux ==1)
	{
		decMatriz();
		aux = 0;
	}
}
	}



int main(void)
{
	uint16_t adc_result;
	char buffer[20];
	
	sei();
	
	USART_Init();
	USART_StrTx((const char*)"HELLO");
	USART_rxIE();
	
	adc_init();
	
	DisplayLCD_Init();
	DisplayLCD_Cmd(LCD_Clear);
	DisplayLCD_Out(1,2,"HELLO");
	
    while (1) 
    {
		adc_result = adc_read(0);
		sprintf(buffer, "%d \r\n", adc_result );
		
		cli();
		USART_StrTx(buffer);
		sei();
		
    }
}

