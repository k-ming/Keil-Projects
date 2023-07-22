#include <STC15F2K60S2.H>

// 定时器0初始化，可以在stc-isp软件中自动生成
void Timer0_Init(void)		//1毫秒@12.000MHz
{
	AUXR |= 0x80;			//定时器时钟1T模式
	TMOD &= 0xF0;			//设置定时器模式
	TL0 = 0x20;				//设置定时初始值
	TH0 = 0xD1;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
}



//定时器0溢出回调函数
void Timer0_Call(void) interrupt 1
{
	P33 = ~P33; //每1ms将P3^3口取反一次
}

//外部中断2回调函数
void Interrupt2_Call(void) interrupt 10
{
	ET0 = ~ET0; // 定时器0溢出中断关闭
	if(ET0 == 1){
		P33 = 1;
	}else{
		P33 =0;
	} //导通/断开mos
	
}

void main(){
	Timer0_Init(); //调用定时器0初始化
	ET0 = 1; // 定时器0溢出中断开启
	INT_CLKO |= 0X10; //EX2=1 开启外部中断2
	EA = 1; // 打开中断总开关
}