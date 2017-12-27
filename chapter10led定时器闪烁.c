//1.第一个LED同定时器T0设定的时间周期闪烁
//定时器

#include<reg52.h>
sbit led=P1^0;

void timer0_init(){
	TMOD=0x01;	//定时器T0选择工作方式1
	TH0=0x00;	//设置初始值
	Tl0=0x00;
	EA=1;		//打开总中断
	ET0=1;		//打开定时器T0
	TR0=1;		//启动定时器T0
}

void main(){
	led=1;
	timer0_init();
	while(1);
}

void timer0()interrupt 1{
	TH0=0x00;				//set primary
	TL0=0x00;
	led=~led;
}

//2.第一个LED以500ms精确频率闪烁

#include<reg52.h>

sbit led=P1^0;
int i=1;

void timer1_init(){
	TMOD=0x10;//定时器T0选择工作方式1
	TH1=0x4c;	//设置初始值，
	TL1=0x00;
	EA=1;
	ET1=1;
	TR1=1;
}