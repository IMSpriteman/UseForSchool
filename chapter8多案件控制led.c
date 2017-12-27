//1.多按键控制
//每个键独立控制2个LED

#include<reg52.h>

sbit led1=P1^0;//红
sbit led2=P1^1;
sbit led3=P1^2;//绿
sbit led4=P1^3;
sbit led5=P1^4;//黄
sbit led6=P1^5;
sbit led7=P1^6;//蓝
sbit led8=P1^7;

sbit k1=P3^4;  //button
sbit k2=P3^5;
sbit k3=P3^6;
sbit k4=P3^7;

void main(){
	P1=0xff;
	while(1){
		led1=k1;
		led2=k1;
		
		if(k1==0){		//red
			led1=0;
			led2=0;
		}
		else{
			led1=1;
			led2=1;
		}
		 //下面同上类推：
		/*led3=k2;
		led4=k2;
		led5=k3;
		led6=k3;
		led7=k4;
		led8=k4;*/
		led3=k2;
		led4=k2;
		
		if(k2==0){		//green
			led3=0;
			led4=0;
		}
		else{
			led3=1;
			led4=1;
		}
		
		led5=k3;
		led6=k3;
		
		if(k3==0){		//yellow
			led5=0;
			led6=0;
		}
		else{
			led5=1;
			led6=1;
		}
		
		led7=k4;
		led8=k4;
		
		if(k4==0){		//blue
			led7=0;
			led8=0;
		}
		else{
			led7=1;
			led8=1;
		}
	}
}

//2.单键控制LED
//按下一个键，松开后状态改变

#include<reg52.h>
sbit led1=P1^0;   //定义灯
sbit k1=P3^4;		//定义按钮

void delay(unsigned int xms) //延时delay ms

{
	unsigned int i,j;
	for (i=xms ;i>0;i--)
		for(j=112;j>0;j--);
}

void main(){
	P1=0xff;//熄灭所有灯
	while(1){
		if(k1==0){		//监听信号
			delay(10);		//延时10ms消抖；
			if(k1==0){
				while(k1==0);	//直到松开按键
				led1=~led1;		//翻转led1状态
			}
		}
	}
}