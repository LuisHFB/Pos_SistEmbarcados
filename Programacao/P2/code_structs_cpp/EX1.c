/*
 * projeto_cpp2.cpp
 *
 * Created: 22/09/2017 14:13:36
 * Author : Fernando
 */ 

#include <avr/io.h>
#define true 1
struct Data
{
	int dia;
	int mes;
	int ano;
	int status;	
};

struct Data data_altera(struct Data dt, int dia, int mes, int ano)
{
	dt.dia = dia;
	dt.mes = mes;
	dt.ano = ano; 
	if(/*validarData()*/ true)
	{
		dt.status = 1;
	} else {
		dt.status = 0; 
	}
	return dt;
}

struct Data data_inicia(struct Data dt)
{
	dt.dia = 23;
	dt.mes = 9;
	dt.ano = 2017;
	dt.status = 0; 
	return dt;
}
void data_imprime(struct Data dt)
{
	if(dt.status)
	{ 
	   //Imprime data no lcd, serial..etc	
	} else {
		//mensagem de erro
	}
}
int main(void)
{
	struct Data relogio; 
	relogio = data_inicia(relogio);
	data_imprime(relogio);
        relogio = data_altera(relogio, 12, 10, 2017); 
	data_imprime(relogio);
	
        while (1) 
        {
		
        }

        return 0;
}

