/*
* projeto_cpp3.cpp
*
* Created: 22/09/2017 15:01:54
* Author : Fernando
*/

/*
* -lprintf_flt
*/
#define F_CPU 16000000UL
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

class UART
{
	private:
	char txt[50];
	
	public:
	UART(/* UART *this */);
	void writebyte(unsigned char data);
	void writestr(char *ptr);
	void print(int i);
	void print(float  f);
	void print(char* c);

};

UART::UART()
{
	UBRR0H = (uint8_t) (MYUBRR>>8);			
	UBRR0L = (uint8_t)(MYUBRR);
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);				
	UCSR0C = (3<<UCSZ00);						
}
void UART::print(int i)     
{
	sprintf(txt, "AN0 = %d \n", i);
	writestr(txt);
}
void UART::print(float  f) 
{
	sprintf(txt, "AN0 = %.2f \n", f);
	writestr(txt);
	
}	
	
void UART::print(char* c)   
{
	sprintf(txt, "AN0 = %c \n", c);
	writestr(txt);
}
	
void UART::writestr(char *ptr)
{
	while(*ptr != '\0')
	{
		writebyte(*ptr);
		ptr++;
	}
}

void UART::writebyte(unsigned char data)
{
	while(!(UCSR0A & (1<<UDRE0)));				
	UDR0 = data;							
}


int main(void)
{
	int i = 10;
	float t = 5.4;
	char c = 'A';
	
	UART serial;
	serial.print(i);
	serial.print(t);
	serial.print(c);
	
	while(1);
        return 0;
}

