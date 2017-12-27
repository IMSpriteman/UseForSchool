/***********************************************
实验名：流水灯
实验效果：流水灯（位输出）
***********************************************/
#include<reg52.h>
#define uint unsigned int 		//16 0-65535
#define on 0
#define off 1

sbit led1 = P1^0;
sbit led2 = P1^1;
sbit led3 = P1^2;
sbit led4 = P1^3;
sbit led5 = P1^4;
sbit led6 = P1^5;
sbit led7 = P1^6;
sbit led8 = P1^7;

void delay(uint xms){			//延时xms
	uint i,j;
	for(i=xms;i>0;i--）
		for(j=112;j>0;j--);
}

void main(){
	while(1){
		led1 = on;		
		delay(200);		//延时200ms
		led1 = off;

		led2 = on;		
		delay(200);		//延时200ms
		led2 = off;

		led3 = on;		
		delay(200);		//延时200ms
		led3 = off;

		led4 = on;		
		delay(200);		//延时200ms
		led4 = off;

		led5 = on;		
		delay(200);		//延时200ms
		led5 = off;

		led6 = on;		
		delay(200);		//延时200ms
		led6 = off;

		led7 = on;		
		delay(200);		//延时200ms
		led7 = off;

		led8 = on;		
		delay(200);		//延时200ms
		led8 = off;
	}
}

/**********************************************
实验名：流水灯
实验效果:流水灯(循环位置 )
**********************************************/
#include<reg52.h>
#include<intrins.h>
#include"delay.h"
void main(){
	while(1){
		delay(500);
		P1=_crol_(P1，1); //将p1循环左移一位
	}
}

/********************************************
实验名：流水灯
实验效果：流水灯(位移操作)
********************************************/
#include<reg52.h>
void delay (unsigned int xms);

void main(){
	int i=0;
	while(1){
		P1 = 0xfe;		//1111 1110
		for(i=0;i<8;i++){
			delay(1000);
			P1 <<=1; 	//P1=P1<<1;
			P1 = P1 | 0x01;
		}
	}
}

void delay(uint xms){			//延时xms
	uint i,j;
	for(i=xms;i>0;i--）
		for(j=112;j>0;j--);
}