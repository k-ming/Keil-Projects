#include <STC15F2K60S2.H>
#include <intrins.h>
#define motor P33   //�궨��һ�����, P33���Ÿ����ߵ�ƽʱ������ͨmos���������
#define btn P34   //�궨��һ����ť��P34����͵�ƽʱ��ʾ��ť����
// ��ʱ1ms
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


// ��ʱ N ms
void DelayNms(unsigned int num){
	unsigned int i;
	for(i=0; i<num; i++){
		Delay1ms(); // ִ��num����ʱ1ms
	}
}


void main(){
	while(1){
		if(btn == 0){ //��һ�μ�ⰴť
			DelayNms(2);//����2ms���ٴμ�ⰴť
			if(btn == 0){
				motor =~motor; //motor���ŵ�ֵȡ�����򿪻�ر�
			}
			while(~btn); //��ť����δ�ɿ���������
		}
	}
}
