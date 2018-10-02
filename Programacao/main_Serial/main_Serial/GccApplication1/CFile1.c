void decMatriz():
{
	if(matriz[0] == 'L' && matriz[1] == 'D')
	{
		switch (matriz[2])
		{
			case '0':
			if(matriz[3] == '0')
			{
				Set_bit(PORTB,5);
				}else{
				Clr_bit(PORTB,5);
			}
			break;
		}
	}
}