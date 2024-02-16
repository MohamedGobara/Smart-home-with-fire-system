#define F_CPU 8000000
#include <util/delay.h>

#include "FireSytemSmart_interface.h"


static u8 temprature ;
static u16 pass=1234 ;
static u16 temp_keypad=0 ;

void FireSystemSmart_Init(void) {
	ADC_Init(VREF_AVCC,ADC_PRESCALER_64) ;
	/* get first temprature sensor read */
	temprature = SENSORS_NTC10KGetTemp() ;
	
}
static u8 flag=0 ;
static u8 k=NO_KEY ;

void FireSystemSmart_Runnable(void) {

	temprature = SENSORS_NTC10KGetTemp() ;
	//k=KeyPad_GetKey() ;
	

	/* not enter in fire case */
	if(flag==0){
		LCD_GoTo(0,0) ;
		LCD_WriteNumber(temprature) ;
		LCD_WriteString(" C") ;
		LCD_WriteString("   ") ;
		
		/*  safe case */
		if(temprature<SAFE_LEVEL_SMART){
			
			LCD_GoTo(0,9) ;
			LCD_WriteString("Safe") ;
			
			DIO_WritePin(LED_GREEN_KIT,HIGH) ;
			DIO_WritePin(LED_BLUE_KIT,LOW) ;
			DIO_WritePin(LED_RED_KIT,LOW) ;
			DIO_WritePin(BUZZER_KIT,LOW) ;
			
		}


		/* heat case */

		else if(temprature>SAFE_LEVEL_SMART&&temprature<HEAT_LEVEL_SMART){
			
			LCD_GoTo(0,9) ;
			LCD_WriteString("Heat") ;
			
			DIO_WritePin(LED_GREEN_KIT,LOW) ;
			DIO_WritePin(LED_BLUE_KIT,HIGH) ;
			DIO_WritePin(LED_RED_KIT,LOW) ;
			DIO_WritePin(BUZZER_KIT,LOW) ;
			
		}
		/* fire case */
		else if (temprature>HEAT_LEVEL_SMART)
		{
			LCD_Clear() ;
			LCD_GoTo(0,0) ;
			LCD_WriteString("<< Fire >>") ;
			DIO_WritePin(LED_GREEN_KIT,LOW) ;
			DIO_WritePin(LED_BLUE_KIT,LOW) ;
			DIO_WritePin(LED_RED_KIT,HIGH) ;
			DIO_WritePin(BUZZER_KIT,HIGH) ;
			flag=1 ;
			LCD_GoTo(1,0) ;
			
		}
		
	}
	
	
}





void FireSystemSmart_ExitDangerMode(void) {
	
	DIO_WritePin(BUZZER_KIT,LOW) ;
	flag=0  ; 
}