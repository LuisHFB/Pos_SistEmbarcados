/*
 * TestADC.c
 *
 * Created: 04/10/2018 23:18:24
 * Author : Luis Bueno
 */ 

#include <avr/io.h>

void adc_init()
{
	ADMUX = (1<<REFS0); // Seta referencia p/ 5V
	
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0); // Liga ADC converter e seta Prescale para 128
}

uint16_t adc_read(uint8_t ch)
{
	ch &= 0b000111;
	ADMUX = (ADMUX & 11111000)|ch; //seta o canal de leitura de ADMUX sem alterar os resto dos bits
	
	ADCSRA |= (1<<ADSC);//|(1 << ADIF); // começa leitura ADC setando a flag ADSC (ADC Start) para 1 
	
	while (ADCSRA &(1<<ADSC)) //Espera até ADSC virar 0 de novo
	 //while (!(ADCSRA & (1<<ADIF))); ?!?!? Checa a flag de fim de conversão
	
	return (ADC);
		
}

int main(void)
{
    /* Replace with your application code */
    while (1) 
    {
    }
}

