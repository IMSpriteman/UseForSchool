//1.外部中断下降沿触发
//按一个键触发P3.3下降沿，使用LED触发前后4位电平状态转换

#include<reg52.h>

void main(){
	P1=0xof;//0000 1111 下面4个亮，上面四个灭
	EX1=1;//INT1中断允许
	EA=1;//	全局中断打开
	IT1=1;//触发方式为下降沿
	while(1);
}

void jump_low() interrput 2{
	P1=~P1;
}

//2.外部中断低电平触发
//给P3.2引脚触发中断，使LED状态置换
#include<reg52.h>

void delay(unsigned int xms) //延时delay ms

{
	unsigned int i,j;
	for (i=xms ;i>0;i--)
		for(j=112;j>0;j--);
}

void main(){
	P1=0xof;//0000 1111 下面4个亮，上面四个灭
	EX1=1;//INT1中断允许
	EA=1;//	全局中断打开
	IT0=0;//触发方式为下降沿
	while(1);
}

void low()interrput 0{
	P1=~P1;
	delay(200);
}