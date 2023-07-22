//—” ±1ms
void Delay1ms()		//@11.0592MHz
{
	unsigned char data i, j;

	i = 15;
	j = 90;
	do
	{
		while (--j);
	} while (--i);
}

//—” ±n ms
void DelayNms(unsigned int num){
	unsigned int i;
	for(i=0; i<num; i++){
		Delay1ms();
	}
}
