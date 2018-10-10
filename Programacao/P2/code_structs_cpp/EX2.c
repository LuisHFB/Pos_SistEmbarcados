/*
 * projeto_cpp3.cpp
 *
 * Created: 22/09/2017 15:01:54
 * Author : Fernando
 */ 

#include <avr/io.h>

class Data
{
  private:
   char  dia;
   char  mes;
   short ano;
   bool  status;
   	
  public:
   Data(/* Data *this */); //Construtora
   void data_altera(/*Data *this */ int dia, int mes, int ano); 
   void data_imprime(/*Data *this */) const;   	
};

Data::Data()
{
	this->dia = 30;
	this->mes = 9;
	this->ano = 2017; 
	this->status = true;
}
void Data::data_altera(/*Data *this */ int dia, int mes, int ano)
{
	this->dia = dia;
	this->mes = mes;
	this->ano = ano;
	this->status = true;
}

void Data::data_imprime(/*const Data *this */) const
{
	if(status)
	{
		//imprime no LCD
	} else {
		//mensagem de error!
	}
}
int main(void)
{
	Data dt; 
	dt.data_imprime();    
	dt.data_altera(12, 10, 2017);
	dt.data_imprime();

    while (1) 
    {
    }
    return 0;
}

