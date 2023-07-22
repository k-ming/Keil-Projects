#include <STC15F2K60S2.H>
#include <sys_delay_ms.h>
#define LED P32

void int2_OpenMotor() interrupt 10
{
	P33 = ~P33; //P3^3引脚取反, 导通或者关闭mos管
}

int main(){
	INT_CLKO |= 0x10;  //(EX2 = 1)使能INT2中断 P34引脚
	//EX2 = 1; 头文件中没有定义，但是官方文档中有该引脚位
	EA = 1;   //打开外部中断总开关
	// 外部中断2只能下降沿触发，没有IT2
	while(1){
		LED = ~LED;
		DelayNms(500);
	}
}

