#include <REG52.H>

sbit button = P0^0; //�������ӿ��ص�����
sbit mos = P0^1; //��������mos�ܵ�����

// ��ʱ����
void delay_ms(unsigned int time){
	unsigned int i, j;
	for(i = 0; i < time; i++){
		for(j = 0; j < 1000; j++){
		}
	}
}

// ��������
/*
int debounce(){
	int state = button; //�����ʼ״̬
	int count = 0; // ���ü�������ʼֵ
	while(count < 10){ //�������10��
		if(button != state){
			count = 0; //���ü�����
			state = button; //����״̬
		}else{
			count++; //����������
		}
		delay_ms(50); //��ʱ50ms
	}
	return state; //����������״̬
}
*/


void main(){
	while(1){
		if(button == 0){ //��һ�μ�ⰴ�������£�Ȼ������20ms
			delay_ms(20);
			if(button == 0){ //�ڶ��μ�ⰴ�������£���ͨ/�Ͽ�mos
				mos = !mos;
			}
		while(!button); //������δ�ɿ�ʱ��ִ�и���ѭ��
		} 
	}
}