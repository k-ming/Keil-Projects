#include <reg51.H>
//��ʱ����
void delay_ms(unsigned int milliseconds){
	unsigned int i, j;
	for(i = 0; i < milliseconds; i++){
		for(j = 0; j < 144; j++){ //��ʱ1ms
		} 
	}
}

void main(){
	TMOD = 0x01;//���ö�ʱ��0Ϊģʽ1��16λ��ʱ��
	TH0 = 0xFC;// ���ö�ʱ��0�ĳ�ʼֵ������1ms��ʱ
	TL0 = 0x67;
	TR0 = 1;//������ʱ��
	
	while(1){
		if(TF0 == 1){//��鶨ʱ��0�Ƿ����
			TF0 = 0;//���������־�������Ҫִ�еĲ�������
			P0 = ~P0;//P0�ڵĵ�ȫ��
			//delay_ms(500);//��ʱ500ms
			//P0 = 0x00;//P0�ڵĵ�ȫ��
			//delay_ms(500);//��ʱ500ms
		}
	}
}