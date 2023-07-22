#include <STC15F2K60S2.H>
#include <intrins.h>
#define motor P33   //宏定义一个电机, P33引脚给出高电平时点亮导通mos管驱动电机
#define btn P34   //宏定义一个按钮，P34输入低电平时表示按钮按下
// 延时1ms
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


// 延时 N ms
void DelayNms(unsigned int num){
	unsigned int i;
	for(i=0; i<num; i++){
		Delay1ms(); // 执行num次延时1ms
	}
}


void main(){
	while(1){
		if(btn == 0){ //第一次检测按钮
			DelayNms(2);//消抖2ms后再次检测按钮
			if(btn == 0){
				motor =~motor; //motor引脚的值取反，打开或关闭
			}
			while(~btn); //按钮按下未松开不做处理
		}
	}
}
