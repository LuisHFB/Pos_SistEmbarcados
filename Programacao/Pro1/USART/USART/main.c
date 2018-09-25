/*
 * USART.c
 *
 * Created: 20/09/2018 20:07:00
 * Author : Luis Bueno
 */ 

#include <avr/io.h>
#include "usart.h"
#include "util/delay.h"

int main(void)
{	
	USART_Init();

    while (1) 
    {
		USART_StrTx("Digite o primeiro numero: ");
		_delay_ms(100);
		unsigned char c = USART_Receive();
		USART_Transmit(c);
		USART_StrTx("\n");
		
		USART_StrTx("Digite o segundo valor: ");
		_delay_ms(100);
		unsigned char d = USART_Receive();
		USART_Transmit(d);
		USART_StrTx("\n");
		
		int soma = (c + d)-0x30;
		USART_StrTx("A soma dos dois valores eh: ");
		USART_Transmit(soma);
		USART_StrTx("\n\n");
    }
}

