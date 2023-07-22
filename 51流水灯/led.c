#include <reg51.H>
#include <intrins.h>
//ÑÓ³Ùº¯Êý
void delay_ms(int a){
	int i,j;
	for(i = 0; i < a; i++){
		for(j = 0; j < 1000; j++) _nop_();
	}
}

void main(void){
	while(1){
		P0=0xfe;
		delay_ms(50);
		P0=0xfd;
		delay_ms(50);
		P0=0xfb;
		delay_ms(50);
		P0=0xf7;
		delay_ms(50);
		P0=0xef;
		delay_ms(50);
		P0=0xdf;
		delay_ms(50);
		P0=0xbf;
		delay_ms(50);
		P0=0x7f;
		delay_ms(50);
	}
}