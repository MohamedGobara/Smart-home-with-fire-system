
#ifndef SMARTHOME_INTERFACE_H_
#define SMARTHOME_INTERFACE_H_
#define F_CPU 8000000
#include <util/delay.h>


#include "StdTypes.h"
#include "UART_Services.h"
#include "Timer_Services.h"
#include "DIO_interface.h"
#include "KIT.h"
#include "AdditionalFun.h"
#include "LCD_Interface.h"
#include "SERVO_interface.h"
#include "FireSytemSmart_interface.h"

// LEDS
#define RIGHT_LIGHTING PINB0

#define FRONT_LIGHTING PINB1

#define LEFT_LIGHTING  PINB2

// FAN
#define MAIN_FAN PINC3

/*


servo -> PIND4

*/



typedef  struct SmartHome_s{
	
	u8* str_command ;
	
	void (*f_ptr) (u8) ;
	
}SmartHome_commandStruct;


void SmartHome_init(void)  ;

void SmartHome_Runnable(void) ;

void SmartHome_turnOnLed(u8 n) ;

void SmartHome_turnOffLed(u8 n) ;

void SmartHome_turnOnFan (u8 n) ;

void SmartHome_turnOffFan (u8 n) ;

void SmartHome_OpenDoor(u8 n) ;

void SmartHome_closeDoor(u8 n) ;

void SmartHome_stopFireAlarm(u8 n) ; 


#endif /* SMARTHOME_INTERFACE_H_ */