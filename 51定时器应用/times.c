#include <reg51.H>
//延时函数
void delay_ms(unsigned int milliseconds){
	unsigned int i, j;
	for(i = 0; i < milliseconds; i++){
		for(j = 0; j < 144; j++){ //延时1ms
		} 
	}
}

void main(){
	TMOD = 0x01;//设置定时器0为模式1，16位定时器
	TH0 = 0xFC;// 设置定时器0的初始值，用于1ms定时
	TL0 = 0x67;
	TR0 = 1;//启动定时器
	
	while(1){
		if(TF0 == 1){//检查定时器0是否溢出
			TF0 = 0;//重置溢出标志，并添加要执行的操作任务
			P0 = ~P0;//P0口的灯全亮
			//delay_ms(500);//延时500ms
			//P0 = 0x00;//P0口的灯全灭
			//delay_ms(500);//延时500ms
		}
	}
}