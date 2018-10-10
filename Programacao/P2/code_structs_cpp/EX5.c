/*
* projeto_cpp4.cpp
*
* Created: 22/09/2017 17:11:43
* Author : Fernando
*/

#include <avr/io.h>
#include <stdio.h>

union Valor
{
	uint32_t dword;

	struct
	{
		uint16_t word0;
		uint16_t word1;
	};

	struct
	{
		uint8_t byte0;
		uint8_t byte1;
		uint8_t byte2;
		uint8_t byte3;
	};
	
	struct {
		uint8_t bit0 : 1;
		uint8_t bit1 : 1;
		uint8_t bit2 : 1;
		uint8_t bit3 : 1;
		uint8_t bit4 : 1;
		uint8_t bit5 : 1;
		uint8_t bit6 : 1;
		uint8_t bit7 : 1;
	};

};

	
 char txt[20];

int main(void)
{
    
	volatile union Valor data;
	
	uint16_t adc = 0xFFAA; 
	
        data.byte0 = (uint8_t)adc; 
	data.byte1 = (uint8_t)(adc>>8); 
	sprintf(txt, "%u",  data.word0);
	
	//Resultado: txt[] = {"65450"}    
	
	data.bit0 = 1;
	
	while (1);
        return 0;
}

