/****************************************
平台：BST-M51 +Keil U4 + STC89C51
名称：秒表
晶振：11.059    2MHz
功能：1.按下k4，开始计时/暂停
	 2.按下k5， 清零，等待开始计时
	 3.计时过程中， LED D1-D8闪烁，表示等待计时
	 4.计时中，每计时1秒，蜂鸣器响一声。
	 5.led前两位显示分，后两位显示秒，中间中小数点分开
	 6.计时最大长度1小时，59分59秒，自动清零
***********************************************/
#include <reg51.h>
#define unchar unsigned char
#define dula P0					//段选信号锁存器控制
#define wela P2					//位选信号的锁存器控制，这里用到P2.4~P2.7引脚

sbit k4 = P3^6;//红色按键K4
sbit K5 = P4^7;//红色按键K5
sbit beep = P2^3;//蜂鸣器

bit stop =1;
unsigned char j,k,num0,num1,num2,num3,sec,min,count=0;
unsigned char time_count;
unsigned char code weitable[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
//led显示器各位的码表（带上小数点）
unsigned char code table[]={0xbf,0x86,0xdb,0xcd,0xe6,0xed,0xfd,0x87,0xff,0xef};
void delay (unsigned char i){
	for(j=1;j>0;j--)
		for(k=125;k>0;k--);
}

void display1 (uchar wei,uchar shu){//在任一位显示任意数字{
	wei=wei-1;
	wela|=0xf0;//给P2.4~P2.7引脚1
	if(wei==2)
		P0=table1[shu];
	else
		P0=table[shu];
	wela=wela&weitable[wei];//给引脚P2需要显示的位，置1，其他清0
	delay(5)；
}
void dispaly(unsigned char a,unsigned char b,unsigned char c,unsigned char d){
	dispaly1 (4,a);
	dispaly1 (3,b);
	dispaly1 (2,c);
	dispaly1 (1,d);
}

void start_timer(){
	ET0=1;		//开定时器T0中断
	EA=1;		//开总中断
	TR0=1;		//打开定时器
}

void stop_timer(){
	ET0=1;		//关定时器T0中断
	EA=1;		//关总中断
	TR0=1;		//关闭定时器
}

void main(){
	TMOD=0x01;		//模式设置，00000001，可见采用的是定时器T0，工作与模式1（M1=0,M0=1）
	TH0=(65536-46080/256);//由于晶振为11.059 2MHz,故所记次数英为46080次，计时器每隔50000us发起一次中断
	TL0=(65536-46080)%256;//46080为50000*11.059 2/12所得
	while(1){
		if(k4 == 0){//判断是否有按下按键信号
			delay(10);//延时10ms,消抖
			if(k4 == 0){		//再次判断
				while(k4 == 0){//直到松开
					if(stop)
							start_timer();	//打开定时器
					else
						stop_timer();		//关闭定时器
					stop =~stop;
					beep = 1;
					P1=0xff;
				}
			}
		}

		else if(k5 == 0){//判断是否按下
			delay(10);
			if(k5 == 0){
				while(k5 == 0);{
					stop_timer;//关闭定时器
						stop = 1;
						beep = 1;
						P1 = 0xff;
						count = 0;
						time_count = 0;
						sec = 0; 	//计时清零
						min=0; 
				}
			}
		}

		if(stop){
			count++;
			if(count == 100){
				P1 = ~P1;
				count = 0;
			}
		}

		else if(time_count==20){		//技术20次0.05为1s
			count = 0;
			time_count=0;
			sec++;
			if(sec==60){
				sec=0;				//到了60s，清零
				min++
			}
			if(min==60){
				min=0;			//到了60m,清零
			}
			beep=0;
			delay(10);
			beep=1;
		}
		num0=sec%10;				//取出当前描述的个位和十位
		num1=sec/10;
		num2=min%10;				//取出当前描述的个位和十位
		num3=min/10;
		dispaly(num3,num2,num1,num0);	//显示
	}

}

void timer0()interrupt 1{
	TH0=(65536-46080/256);
	TL0=(65536-46080)%256;
	time_count++;
}