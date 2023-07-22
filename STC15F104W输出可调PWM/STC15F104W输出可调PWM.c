#include <STC15F2K60S2.H>
#include "SYS_DELAY_MS.H"

/* 以12MHZ时钟频率为例
时钟周期：1/时钟频率
机器周期(定时存储器加1的时间)：12*时钟周期
最大定时时间：65535 *12 * (1/12000000) = 71ms
假设PWM频率1000HZ, 则周期 = 1/1000 =0.001 = 1ms
设置定时器每0.01ms = 10us中断一次，则0.01 * 100 次 = 1ms
*/

#define MACH_Fosc 60   								//设置机器频率,单位HZ
#define MACH_PERIOD 1000000/MACH_Fosc  //计算机器周期 us
#define timer  MACH_PERIOD/100  			//假设中断100次，计算中断时长，单位us

typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;

uchar cnt=0;      //定义计数初始值为0
uchar duty=3;   //定义初始占空比 

// 定时器0初始化函数，可以在stc-isp软件中自动生成
void Timer0_Init(void)		//1毫秒@12.000MHz
{
	AUXR |= 0x80;			//定时器时钟1T模式
	TMOD &= 0xF0;			//设置定时器模式
	TL0 = (65536 - timer)%256;				//设置定期器初始值低8位
	TH0 = (65536 - timer)/256;				//设置定期器初始值高8位
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
}


//定时器0回调函数
void Timer0_Call(void) interrupt 1
{
	Timer0_Init(); 		//定时器初始化
	cnt++;  				// 每中断一次 计数+1
	if(cnt <= duty){
		P32 = 1;   					// P3^3引脚 输出50%的高电平输出
	}else if(cnt >=100){
		cnt = 0;						// 1s 已到，归零
	}else{
		P32 = 0;						//P3^3引脚 输出 50%的低电平输出
	}
	
}

//外部中断2初始化函数
void Interrupt2_Init(){
	INT_CLKO |= (1<<4); //00010000; 第5位设为1,或的关系, 其它位保持不变，  
										//EX2 =1 中断允许控制
//	EA = 1; 		//中断总开关， 已在main函数中打开
}

//外部中断2回调函数
void Interrupt2_Call() interrupt 10
{	
	if(duty < 100){
		duty += 30;   // 每中断一次，占空比加10；
	}else{
		duty = 0;  	//占空比到达100% ，设为初始值
	}
}

void main()
{
	Timer0_Init(); 			//定时器0初始化
	Interrupt2_Init();	//外部中断2初始化
	EA = 1 ;    	//开启中断总开关
	ET0 = 1;    // 定时器溢出后中断开启
	
	while(1){
		P31 = ~P31;   // P31/P30 交替取反，表现位led交替闪烁
		P30 = ~P31;
		DelayNms(300);
	};
}


