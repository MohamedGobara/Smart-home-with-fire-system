#define F_CPU 8000000
#include <util/delay.h>

#include "FireSystem_interface.h"


static u8 temprature ;
static u16 pass=1234 ;
static u16 temp_keypad=0 ;

void FireSystem_Init(void) {
	ADC_Init(VREF_AVCC,ADC_PRESCALER_64) ; 
	/* get first temprature sensor read */
	temprature = SENSORS_NTC10KGetTemp() ;
	
}
static u8 flag=0 ;
static u8 k=NO_KEY ;

void FireSystem_Runnable(void) {

	temprature = SENSORS_NTC10KGetTemp() ;
	k=KeyPad_GetKey() ;
	

	/* not enter in fire case */
	if(flag==0){
		LCD_GoTo(0,0) ;
		LCD_WriteNumber(temprature) ;
		LCD_WriteString(" C") ;
		LCD_WriteString("   ") ;
		
		/*  safe case */
		if(temprature<SAFE_LEVEL){
			
			LCD_GoTo(0,9) ;
			LCD_WriteString("Safe") ;
			
			DIO_WritePin(LED_GREEN_KIT,HIGH) ;
			DIO_WritePin(LED_BLUE_KIT,LOW) ;
			DIO_WritePin(LED_RED_KIT,LOW) ;
			DIO_WritePin(BUZZER_KIT,LOW) ;
			
		}


		/* heat case */

		else if(temprature>SAFE_LEVEL&&temprature<HEAT_LEVEL){
			
			LCD_GoTo(0,9) ;
			LCD_WriteString("Heat") ;
			
			DIO_WritePin(LED_GREEN_KIT,LOW) ;
			DIO_WritePin(LED_BLUE_KIT,HIGH) ;
			DIO_WritePin(LED_RED_KIT,LOW) ;
			DIO_WritePin(BUZZER_KIT,LOW) ;
			
		}
		/* fire case */
		else if (temprature>HEAT_LEVEL)
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
	else {
		
		if(k!=NO_KEY){
			
			
			
			
			if(k>='0'&&k<='9'){
				
				temp_keypad = (temp_keypad*10)+(k-'0') ;
				LCD_WriteString("*") ;

			}
			
			if(k=='=') {
				/* correct password*/
				if (temp_keypad==pass)
				{
					
					
					flag=0 ;
					LCD_Clear();
					temp_keypad=0 ;
					
				}
				
				/* wrong password */
				else {
					LCD_Clear() ;
					LCD_GoTo(0,0) ;
					LCD_WriteString("Wrong password") ;
					_delay_ms(500) ;
					LCD_Clear();
					LCD_GoTo(0,0) ;
					LCD_WriteString("<<Fire>>") ;
					LCD_WriteString("          ") ;
					LCD_GoTo(1,0) ;
					temp_keypad=0 ;
				}
				
			}
			
		}
		
	}
	

}




