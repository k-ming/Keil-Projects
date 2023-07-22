#include <STC15F2K60S2.H>
#include <intrins.h>
#include <stdio.h>

// —” ±1ms
void Delay1ms()		//@11.0592MHz
{
	unsigned char data i, j;

	_nop_();
	_nop_();
	_nop_();
	i = 11;
	j = 190;
	do
	{
		while (--j);
	} while (--i);
}



//—” ±n ms
void Delay_ms(unsigned int num){
	unsigned int i;
	for(i=0; i<num; i++){
		Delay1ms();
	}
}

void main(){
	P33 = 1;
	Delay_ms(500);
	P33 = 0;
	Delay_ms(500);
}