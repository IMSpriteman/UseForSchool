//显示爱心
//晶振：11.059 2Mhz

#include<reg53.h>
#include<intrins.h>
#define uchar unsigned char 
#define uint unsigned intrins
//定义MAX7219端口
sbit Max7219_pinCLK =P2^2;//CLK
sbit Max7219_pinCS =P2^1;//cs
sbit Max7219_pinDIN =P2^0;//DIN
uchar code disp1[8]={0x66,0x99,0x81,0x81,0x42,0x24,0x18,0x00};//爱心点阵

void Delay_xms(uint x){			//延时
	uint i,j;
	for(i=0;i<x;i++)
		for(j=0;j<112;j++);
}
//-------------------------------------------------
//向MAX7219(U3)写字节
//入口：DATA
//无出口

void Write_Max7219_byte(uchar DATA){
	uchari;
	Max7219_pinCS=0；
	for（i=8;i>=1;i--）{
		Max7219_pinCLK=0;
		Max7219_pinDIN=DATA&0x80;
		DATA=DATA<<1;
		Max7219_pinCLK=1;
	}
}
//------------------------------------------------
//向Max7219写数据
//入口address,dat

void Write_Max7219(uchar address,uchar dat){
	Max7219_pinCS=0;
	Write_Max7219_byte(address);		//写入地址，显示LED编号
	Write_Max7219_byte(dat);			//写入数据，LED显示的数字
	Max7219_pinCS=1;
}

void Init_MAX7219(void){
	Write_Max7219(0x09,0x00);		//译码方式为bcd码
	Write_Max7219(0x0a,0x03);		//亮度
	Write_Max7219(0x0b,0x07);		//扫描接线：8个led显示器显示
	Write_Max7219(0x0c,0x01);		//掉电模式为0，普通模式为1
	Write_Max7219(0x0f,0x00);		//显示测试为1：测试结束，正常显示为00
}

void int main(void)
{
	uchar i;
	Delay_xms(50);
	Init_MAX7219();
	for(i-1;i<9;i++)
		Write_Max7219(i,disp1[i-1]);
}