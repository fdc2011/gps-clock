
#include <REG52.H>          //头文件包含 
#define uchar unsigned char       //宏定义 
#define uint  unsigned int 
/* ///////////////////////////////////////
;12C1052+74164+UC2003驱动1.8寸数码管四位电子钟
;11.592M晶振;GPS模块接在P3.0 P3.1
////////////////////////////////////////*/

sbit MIAO =P1^7;             //秒点 ,数码管第二位小数点,可以自己随意定义. 
//sbit HOU_S=P2^1;            //时十位位选 
//sbit HOU_G=P2^2;            //时个位位选 
//sbit MIN_S=P2^3;            //分十位位选 
//sbit MIN_G=P2^4;            //分个位位选 
//sbit SHAN=P1^0;
sbit led=P1^0; 
sbit K0=P2^0;
sbit K1=P2^1;
sbit K2=P2^2;
sbit K3=P2^3;
sbit K4=P2^4;
sbit K5=P2^5;
sbit K6=P2^6;
sbit K7=P2^7;
//sbit io=P3^4;             
//sbit SCK=P3^3;            


bit  SHAN;               //闪烁标志位 
uchar sec,min,hou;        //定义秒、分、时寄存器 
//uchar code LEDTab[]={0x7E,0x18,0x6D,0x3D,0x1B,0x37,0x77,0x1C,0x7F,0x3F}; //数码管段码表0--9码 
uchar code LEDTab[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};
uchar code GPRMC[]={"$GPRMC,"};//$GPRMC,字符串数据


uchar Get_Gps();   //比较接收$GPRMC,
void delay(uchar t);          //延时函数 
void init();              //初始化函数 
void display();             //显示函数
/*------------------------------------------------
                    定时器初始化子程序
------------------------------------------------*/
void Init_Timer0(void)
{
 TMOD |= 0x01;	  //使用模式1，16位定时器，使用"|"符号可以在使用多个定时器时不受影响		     
 //TH0=0x00;	      //给定初值
 //TL0=0x00;
 EA=1;            //总中断打开
 ET0=1;           //定时器中断打开
 TR0=1;           //定时器开关打开
} 

/*************************************** 
函 数 名：main 
功    能：主函数 
说    明： 
入口参数：无 
返 回 值：无 
****************************************/ 
void main()
 //TMOD |= 0x01;	  //使用模式1，16位定时器，使用"|"符号可以在使用多个定时器时不受影响		     
 //EA=1;            //总中断打开
 //ET0=1;           //定时器中断打开
 //TR0=1; 

{ 
Init_Timer0();
  init();
                //调用初始化函数 
  display();             //调用显示函数 
}  

/*************************************** 
函 数 名：init 
功    能：;初始化串口波特率4800
说    明：初始化定时器及中断 
***************************************/ 
void init() 
{/* P1=0;P3=0xff;//初始化IO口
TMOD=0X21;TH0=0X4C;TL0=0;SCON=0x50;       //定时器0模式1，50毫秒 
TH0=0Xfa;TL0=0Xfa;ET0=1;TR0=1;TR1=1;ES=1;EA=1;*///开定时器0中断、启动定时器0、开总中断 
/*	PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率

	TMOD &= 0x0F;		//清除定时器1模式位
	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
	TL1 = 0xB2;		//设定定时初值
	TH1 = 0xB2;		//设定定时器重装值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;*/		//启动定时器1
	TMOD = 0x20;
TL1 = 0xFD;
TH1 = 0xFD;          //波特率为：9600
ET1 = 0;             //T1用作波特率发生器，禁止T1中断
TR1 = 1;             //启动定时器T1
SCON = 0x70;         //方式1，SM2位为1
PCON = 0;            //波特率无倍增
EA = 1;
ES = 1;
} 

//***************************************/ 
/*void HC164(uchar dat)//:;164串行发送
{
    uchar i;
    for (i=0; i<8; i++)         //8位计数器
    {
        dat <<= 1;              //移出数据的最高位
        io = CY;               //送数据口
        SCK = 1;                //拉高时钟线
        SCK = 0;                //拉低时钟线
    }
}
/*************************************** 
函 数 名：display 
功    能：显示函数 
说    明： 
入口参数：无 
返 回 值：无 
***************************************/ 
void display()

{
  
  /* P2=0xff;
  K0=0;
  P0=LEDTab[t1];
  //P0= LEDTab[time[3]-32-16];
  delay1ms(s);
  P2=0xff;
  K1=0;
  P0=LEDTabd[t2];
  
  //P0= 0xbf;
  delay1ms(s);
  P2=0xff;
  K2=0;
  P0=LEDTab[t3];
  //P0= LEDTab[time[4]-32-16];
  delay1ms(s);
  P2=0xff;
  K3=0;
  P0=LEDTabd[10];
  //P0= LEDTab[time[5]-32-16];
  delay1ms(s);
  P2=0xff;
  delay1ms(s);
  
*/	  

  
  P0=0xff;
  P2=0xff;
  K4=0;
  P0= LEDTab[hou/10];
  delay(1);
  P2=0xff;
  K5=0;
  P0= LEDTab[hou%10];
  delay(1);
  P2=0xff;
  K6=0;
  P0= LEDTab[min/10];
  delay(1);
  P2=0xff;
  K7=0;
  P0= LEDTab[min%10];
  //P0= LEDTab[time[2]-32-16];
  delay(1);
  P2=0xff;
  } 
/*{ 
HC164(LEDTab[min%10]);       //分个位送数码管显示 
MIN_G=1;               //打开分个位位选 
delay(1);               //显示1毫秒 
MIN_G=0;              //关闭分个位位选 
HC164(LEDTab[min/10]);       //分十位送数码管显示 
MIN_S=1;               //打开分十位位选 
delay(1);               //显示1毫秒 
MIN_S=0;              //关闭分十位位选 
HC164(LEDTab[hou%10]);        //时个位送数码管显示 

HOU_G=1;               //打开时个位位选 
delay(1);               //显示1毫秒 
HOU_G=0;              //关闭时个位位选 

  HC164(LEDTab[hou/10]);       //时十位送数码管显示 
  HOU_S=1;              //打开时十位位选 
  delay(1);              //显示1毫秒 
  HOU_S=0;             //关闭时十位位选 

} /*

/*************************************** 
函 数 名：delay 
功    能：延时函数 
说    明： 
入口参数：t：延时时间长短 
返 回 值：无 
***************************************/ 
void delay(uchar t) 
{ 
uchar i;               //定义变量 
for(;t>0;t--)             //如果t大于0，t减1（外层循环） 
  for(i=124;i>0;i--);         //i等于124，如果i大于0，i减1 
} 

/*************************************** 
函 数 名：timer0 
功    能：定时器0中断函数 
说    明： 
入口参数：无 
返 回 值：无 
***************************************/ 
void timer0() interrupt 1        //定时器0（中断1） 
//void Timer0_isr(void) interrupt 1 
{ 
uchar tim1,tim2;           //定义临时变量 
//TL0=0;
//TH0=0X4C;        //重装定时器初值
//TR0=1;

 TH0=(65536-50000)/256; 
 TL0=(65536-50000)%256;

tim1++;                //每中断一次tim1加1 
while (tim1!=10) return;            //中断10（0.5秒）               
  SHAN=!SHAN;             //闪烁标志取反 
led=!led;
  tim1=0;tim2++;           //tim1清零，tim2加1 
while (tim2!=2) return;             //到了1秒? 

   tim2=0;sec++;         //tim2清零，秒加1 
  while (sec!=60) return;       //如果秒到60 


    sec=0;min++;       //秒变0，分加1 

if (min%10==0) ES=1; //每10分钟打开串口中断校时

   while (min!=60) return;       //如果分到60 


     min=0;hou++;       //分变0，时加1 
    while (hou!=24) return;
   hou=0;     //如果时到24，时变0 

} 

/*************************************** 
***************************************/ 
void timer4() interrupt 4        //（中断4） 
{ 

uchar i,p[5];
ES=0;//关串行中断，避免反复中断，下面接收用查询
	//led=!led;
while (Get_Gps())  //接收比较是否是收到$GPRMC，
   {
    ES=1;//如果收不到 打开串行中断后退出
    return;
   }

for(i=0;i<6;i++ )//读取当前时间，时分秒6个ANSI数据
    {
    while (!RI);
    RI=0;
p[5]= SBUF-0X30;//ANSI减30H是16进制数
    }


for(i=0;i<5;i++)//跳过5个数分别为. 毫秒3个数 ，
    {
    while (!RI);
    RI=0;
    }

    while (!RI);
    RI=0;
while (SBUF!='A')//接收到A是数据有效
   {
 
    ES=1;//如果收不到 打开串行中断后退出
    return;
   }

hou=p[0]*10;//处理数据，把6位数合成时分秒三位数
hou=hou+p[1]+8;//收到的是伦敦时间，北京东8区 ＋8小时

min=p[2]*10;
min=min+p[3];

sec=p[4]*10;
sec=sec+p[5];


if (hou<24)return;
hou=hou-24;//加8大于24小时减24保存成北京时间
}

//----------------------------


uchar Get_Gps()//;接收比较是否是收到$GPRMC，
{
  uchar i ;
for(i=0;i<7;i++)
    {
    while (!RI);
    RI=0;
    while(SBUF != GPRMC)
	  
    return 1;
    }

return 0;
}