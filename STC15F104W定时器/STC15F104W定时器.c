#include <STC15F2K60S2.H>

// ��ʱ��0��ʼ����������stc-isp������Զ�����
void Timer0_Init(void)		//1����@12.000MHz
{
	AUXR |= 0x80;			//��ʱ��ʱ��1Tģʽ
	TMOD &= 0xF0;			//���ö�ʱ��ģʽ
	TL0 = 0x20;				//���ö�ʱ��ʼֵ
	TH0 = 0xD1;				//���ö�ʱ��ʼֵ
	TF0 = 0;				//���TF0��־
	TR0 = 1;				//��ʱ��0��ʼ��ʱ
}



//��ʱ��0����ص�����
void Timer0_Call(void) interrupt 1
{
	P33 = ~P33; //ÿ1ms��P3^3��ȡ��һ��
}

//�ⲿ�ж�2�ص�����
void Interrupt2_Call(void) interrupt 10
{
	ET0 = ~ET0; // ��ʱ��0����жϹر�
	if(ET0 == 1){
		P33 = 1;
	}else{
		P33 =0;
	} //��ͨ/�Ͽ�mos
	
}

void main(){
	Timer0_Init(); //���ö�ʱ��0��ʼ��
	ET0 = 1; // ��ʱ��0����жϿ���
	INT_CLKO |= 0X10; //EX2=1 �����ⲿ�ж�2
	EA = 1; // ���ж��ܿ���
}