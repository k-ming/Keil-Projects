#include <REG52.H>

sbit button = P0^0; //定义连接开关的引脚
sbit mos = P0^1; //设置连接mos管的引脚

// 延时函数
void delay_ms(unsigned int time){
	unsigned int i, j;
	for(i = 0; i < time; i++){
		for(j = 0; j < 1000; j++){
		}
	}
}

// 按键消抖
/*
int debounce(){
	int state = button; //保存初始状态
	int count = 0; // 设置计数器初始值
	while(count < 10){ //连续检测10次
		if(button != state){
			count = 0; //重置计数器
			state = button; //更新状态
		}else{
			count++; //计数器递增
		}
		delay_ms(50); //延时50ms
	}
	return state; //返回消抖的状态
}
*/


void main(){
	while(1){
		if(button == 0){ //第一次检测按键被按下，然后消抖20ms
			delay_ms(20);
			if(button == 0){ //第二次检测按键被按下，导通/断开mos
				mos = !mos;
			}
		while(!button); //当按键未松开时，执行该死循环
		} 
	}
}