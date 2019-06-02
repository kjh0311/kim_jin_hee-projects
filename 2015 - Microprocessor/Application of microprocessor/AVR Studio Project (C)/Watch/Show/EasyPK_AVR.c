/***************************************************************

 EASY PROCESSOR KIT - Huins R&D Center hgl

****************************************************************/

// IO ADDRESS MAP
// STEP MOTOR
#define STEP_MOTOR_CS (*(volatile unsinged char *)0x4000 )

#define LED_CS        (*(volatile unsigned char *)0x4800 )
#define ADC_CS        (*(volatile unsigned char *)0x4C00 )
#define DAC_CS        (*(volatile unsigned char *)0x5000 )
                         
#define KEY_DATA      (*(volatile unsigned char *)0x5400 )
#define KEY_SCAN      (*(volatile unsigned char *)0x5800 )
                         
#define EX_CS0        (*(volatile unsigned char *)0x5C00 )
#define EX_CS1        (*(volatile unsigned char *)0x6000 )

#include "LCD_MAP.h"                         
                         
#define FND_DATA      (*(volatile unsigned char *)0x6C00 )
#define FND_CS        (*(volatile unsigned char *)0x7000 )

// GRAPHIC LCD

                         

// DOTMATRIX
#define DOT_COLG      (*(volatile unsigned char *)0x7400 )
#define DOT_COLR      (*(volatile unsigned char *)0x7800 )
#define DOT_ROW       (*(volatile unsigned char *)0x7C00 )

// GPIO Control
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &=~_BV(bit))


volatile unsigned char led_count, led_toggle_flag, ExtGraphLcdCnt;

#include <avr/io.h>
void Platform_Init(void){
	
	MCUCR = 0x80 ;
	XMCRA = 0x44 ;
	XMCRB = 0x80 ;

	DDRB = 0xf0 ; // 1111 0000 : ��Ʈ 4���� ������� ����
	DDRE = 0x0c ; // 0000 1100 : ��Ʈ 2���� ������� ����
    DDRD = 0x30 ; // 0011 0000 : ��Ʈ 2���� ������� ����	
}

void Timer0_Init(void){ 
	TIMSK = 0x01; 	
	TCCR0 = 0x07 ; // CLK / 1024
     
    TCNT0 = 178 ;
	/***********************************************************
    // Clock Source = System clock/1024
    // 10mSEC ���� �����÷� ���ͷ�Ʈ 
  
    X * ���� * ( 1 / 8  ) = 10mSEC 
    X * 1024  *  ( 1.25 * 10^-7) = 10m SEC
    X = 78.125
    256 - 78.125 = 178  = TCNT0
     
    ************************************************************/

}

void led_run(void){	
	if(led_count >= 50){   // CPU LED RUN
  	if(led_toggle_flag == 0){
    	cbi(PORTE, 2 ) ;
		cbi(PORTE, 3 ) ;
    	led_count = 0 ;
    	led_toggle_flag = 1 ;
    }
	
    else if(led_toggle_flag == 1){
       sbi(PORTE , 2 ) ;
	   sbi(PORTE , 3 ) ;
       led_count = 0 ;
       led_toggle_flag = 0 ;
    } 
	
  }
}


// Update 20080409 - Hong
// GPID LED Control
void CpuLedSet(int sel){	
	// Initailization
	sbi(PORTE,2);
	sbi(PORTE,3);
	sbi(PORTD,4);
	sbi(PORTD,5);
	sbi(PORTB,4);
	sbi(PORTB,5);
	sbi(PORTB,6);
	sbi(PORTB,7);

	switch(sel) {
		case 0 :
   			cbi(PORTE, 2);
			break;
		case 1 :
			cbi(PORTE, 3);
			break;
		case 2 :
			cbi(PORTD, 4);
			break;
		case 3 :
			cbi(PORTD, 5);
			break;
		case 4 :
			cbi(PORTB, 4);
			break;
		case 5 :
			cbi(PORTB, 5);
			break;
		case 6 :
			cbi(PORTB, 6);
			break;
		case 7 :
			cbi(PORTB, 7);
			break;
	}

} 

// Update 20080409 - Hong
// Extend FND Control
void ExtFndSet(unsigned int sel) {
	
	switch(sel) {
	case 0 : 
		FND_DATA = ~0x3F;
		break;
	case 1 : 
		FND_DATA = ~0x06;
		break;
	case 2 : 
		FND_DATA = ~0x5B;
		break;
	case 3 : 
		FND_DATA = ~0x4F;
		break;
	case 4 : 
		FND_DATA = ~0x66;
		break;
	case 5 : 
		FND_DATA = ~0x6D;
		break;
	case 6 : 
		FND_DATA = ~0x7C;
		break;
	case 7 : 
		FND_DATA = ~0x07;
		break;
	case 8 : 
		FND_DATA = ~0x7F;
		break;
	case 9 : 
		FND_DATA = ~0x6F;
		break;
	case 10 : 
		FND_DATA = ~0x80;
		break;
	}
}

// ����ũ���� ������ ������ �Լ�
extern void Delay_us(unsigned char time_us)
{
	register unsigned char i;

	for(i = 0; i < time_us; i++)
	{
		asm volatile("PUSH R0");
		asm volatile("POP R0");
		asm volatile("PUSH R0");
		asm volatile("POP R0");
		asm volatile("PUSH R0");
		asm volatile("POP R0");
	}
}

// �̸��� ������ ������ �Լ�
extern void Delay_ms(unsigned int time_ms)
{
	register unsigned int i;

	for(i = 0; i < time_ms; i++)
	{
		Delay_us(250);
		Delay_us(250);
		Delay_us(250);
		Delay_us(250);
	}
}




/* LCD�� ���ڸ� ����ϴ� �Լ� */
void LCD_data(unsigned char lcd_data)
{		
	LCD_CONTROL = 0x02;				// E = 0, Rs = 1
	LCD_DATA = lcd_data;				// output data
	LCD_CONTROL = 0x03;				// E = 1
	Delay_us(1);
	LCD_CONTROL = 0x02;				// E = 0
	Delay_us(50);
}

/* Text LCD�� ������ ����� ó���ϴ� �Լ� */
void LCD_command(unsigned char command)		
{
	LCD_CONTROL = 0x00;				// E = 0, Rs = 0
	LCD_DATA = command;			    // output command
	LCD_CONTROL = 0x01;				// E = 1
	Delay_us(1);
	LCD_CONTROL = 0x00;				// E = 0
	Delay_us(50);
}

/* LCD�� ���ڿ��� ����ϴ� �Լ� 
    : ���ڿ� Ŀ�ǵ�� ���ڿ� �����͸� �޾Ƽ� �ѹ��ھ� ���Ѵ�. */
void LCD_Print(unsigned char command, char *string) 
{
  LCD_command(command);				// ����� �������� �����Ѵ�
  while(*string != '\0')			// ���ڿ��� ������ ���� �ݺ�
    { 
		LCD_data(*string);
       	string++;					// �����͸� �̵���Ų��.
    }
}

/* LCD�� �ʱ�ȭ ���ִ� �Լ� */
void LCD_initialize(void)			// Text LCD ����� �ʱ�ȭ �Ѵ�.
{
  LCD_command(0x38);				// ��µ� LCD ���� (8 bit, 2 line, 5x7 dot)
  LCD_command(0x0C);				// �������(display ON, cursor OFF)
  LCD_command(0x06);				// ��¼���(increment, not shift)
  LCD_command(0x01);				// Text LCDȭ�� �����
  Delay_ms(2);
}
