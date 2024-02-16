#include "SmartHome_interface.h"

#define NumofCommands 7



static volatile u8 receive_str[25] ;
static u8 command_str[20] ;
static u8 command_num ;
static u8 f_search=0 ;

const SmartHome_commandStruct command_struct_arr[]={

	
	{
		"turn on led",
		SmartHome_turnOnLed
	},
	{
		"turn off led",
		SmartHome_turnOffLed
	},
	{
		"turn on fan",
		SmartHome_turnOnFan
	},
	{
		"turn off fan",
		SmartHome_turnOffFan
	} ,
	{
		"open door",
		SmartHome_OpenDoor
	},
	{
		"close door",
		SmartHome_closeDoor
	},
	{
		"stop alarm",
		
		SmartHome_stopFireAlarm
	}
	//6
} ;

void SmartHome_init(void) {
	SERVO_init() ;
	UART_init() ;
	UART_ReceiveString_Asynch(&receive_str) ;
	FireSystemSmart_Init() ;
}

static u8 i , x=0 ;

extern volatile u8 finishedRx_f ;

void SmartHome_Runnable(void){
	
	FireSystemSmart_Runnable() ;
	
	if(UART_ReceiveString_AsynchFinshedCheck()){
	
		SubStringtoStrAndNum(&receive_str,&command_str,&command_num) ;
		/* search command in array of struct  */
		for (i=0 ; i < NumofCommands&&f_search==0 ;i++)
		{
			/* command found */
			if(string_compare(&command_str,command_struct_arr[i].str_command)) {
				f_search=1 ;
				
			}
		}
		
		if(f_search==1) {
	
			/* active function */
			command_struct_arr[i-1].f_ptr(command_num) ;
			UART_SendString_BusyW8("Done") ;
			UART_SendDatau8_BusyW8(10) ;
			f_search=0 ;
			
		}
		else if(f_search==0) {

			UART_SendString_BusyW8("syntax error") ;
			UART_SendDatau8_BusyW8(10) ;
			
		}
		finishedRx_f=0 ;
		
		
	}
	
	
}


/* configration */



void SmartHome_turnOnLed(u8 n) {
	
	if(n==0) {
		DIO_WritePin(RIGHT_LIGHTING,HIGH) ;
	}
	else if(n==1){
		DIO_WritePin(FRONT_LIGHTING,HIGH) ;
	}
	
	else if(n==2){
		DIO_WritePin(LEFT_LIGHTING,HIGH) ;
	}
}


void SmartHome_turnOffLed(u8 n) {
	
	if(n==0) {
		
		
		DIO_WritePin(RIGHT_LIGHTING,LOW) ;
	}
	else if(n==1){
		DIO_WritePin(FRONT_LIGHTING,LOW) ;
	}
	
	else if(n==2){
		DIO_WritePin(LEFT_LIGHTING,LOW) ;
	}
}


void SmartHome_turnOnFan (u8 n) {
	
	if(n==0) {
		DIO_WritePin(MAIN_FAN,HIGH) ;
		
	}



}



void SmartHome_turnOffFan (u8 n) {
	

	if(n==0) {
		DIO_WritePin(MAIN_FAN,LOW) ;
		
	}

}




void SmartHome_OpenDoor(u8 n) {


	if(n==0) {
		SERVO_SG90_SetAngle(25) ;
	}

}




void SmartHome_closeDoor(u8 n) {
	if(n==0) {

		SERVO_SG90_SetAngle(120) ;
	}


	
	
}



void SmartHome_stopFireAlarm(u8 n)  {
	
	
	if(n==0) {
		
		FireSystemSmart_ExitDangerMode() ;
		
	}
}