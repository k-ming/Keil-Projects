#include <STC15F2K60S2.H>
#include <sys_delay_ms.h>
#define LED P32

void int2_OpenMotor() interrupt 10
{
	P33 = ~P33; //P3^3����ȡ��, ��ͨ���߹ر�mos��
}

int main(){
	INT_CLKO |= 0x10;  //(EX2 = 1)ʹ��INT2�ж� P34����
	//EX2 = 1; ͷ�ļ���û�ж��壬���ǹٷ��ĵ����и�����λ
	EA = 1;   //���ⲿ�ж��ܿ���
	// �ⲿ�ж�2ֻ���½��ش�����û��IT2
	while(1){
		LED = ~LED;
		DelayNms(500);
	}
}

