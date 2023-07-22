#include <STC15F2K60S2.H>
#include "SYS_DELAY_MS.H"

/* ��12MHZʱ��Ƶ��Ϊ��
ʱ�����ڣ�1/ʱ��Ƶ��
��������(��ʱ�洢����1��ʱ��)��12*ʱ������
���ʱʱ�䣺65535 *12 * (1/12000000) = 71ms
����PWMƵ��1000HZ, ������ = 1/1000 =0.001 = 1ms
���ö�ʱ��ÿ0.01ms = 10us�ж�һ�Σ���0.01 * 100 �� = 1ms
*/

#define MACH_Fosc 60   								//���û���Ƶ��,��λHZ
#define MACH_PERIOD 1000000/MACH_Fosc  //����������� us
#define timer  MACH_PERIOD/100  			//�����ж�100�Σ������ж�ʱ������λus

typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;

uchar cnt=0;      //���������ʼֵΪ0
uchar duty=3;   //�����ʼռ�ձ� 

// ��ʱ��0��ʼ��������������stc-isp������Զ�����
void Timer0_Init(void)		//1����@12.000MHz
{
	AUXR |= 0x80;			//��ʱ��ʱ��1Tģʽ
	TMOD &= 0xF0;			//���ö�ʱ��ģʽ
	TL0 = (65536 - timer)%256;				//���ö�������ʼֵ��8λ
	TH0 = (65536 - timer)/256;				//���ö�������ʼֵ��8λ
	TF0 = 0;				//���TF0��־
	TR0 = 1;				//��ʱ��0��ʼ��ʱ
}


//��ʱ��0�ص�����
void Timer0_Call(void) interrupt 1
{
	Timer0_Init(); 		//��ʱ����ʼ��
	cnt++;  				// ÿ�ж�һ�� ����+1
	if(cnt <= duty){
		P32 = 1;   					// P3^3���� ���50%�ĸߵ�ƽ���
	}else if(cnt >=100){
		cnt = 0;						// 1s �ѵ�������
	}else{
		P32 = 0;						//P3^3���� ��� 50%�ĵ͵�ƽ���
	}
	
}

//�ⲿ�ж�2��ʼ������
void Interrupt2_Init(){
	INT_CLKO |= (1<<4); //00010000; ��5λ��Ϊ1,��Ĺ�ϵ, ����λ���ֲ��䣬  
										//EX2 =1 �ж��������
//	EA = 1; 		//�ж��ܿ��أ� ����main�����д�
}

//�ⲿ�ж�2�ص�����
void Interrupt2_Call() interrupt 10
{	
	if(duty < 100){
		duty += 30;   // ÿ�ж�һ�Σ�ռ�ձȼ�10��
	}else{
		duty = 0;  	//ռ�ձȵ���100% ����Ϊ��ʼֵ
	}
}

void main()
{
	Timer0_Init(); 			//��ʱ��0��ʼ��
	Interrupt2_Init();	//�ⲿ�ж�2��ʼ��
	EA = 1 ;    	//�����ж��ܿ���
	ET0 = 1;    // ��ʱ��������жϿ���
	
	while(1){
		P31 = ~P31;   // P31/P30 ����ȡ��������λled������˸
		P30 = ~P31;
		DelayNms(300);
	};
}


