
#ifndef FIRESYSTEM_INTERFACE_H_
#define FIRESYSTEM_INTERFACE_H_


#include "ADC_interface.h"
#include "KeyPad_interface.h"
#include "LCD_Interface.h"
#include "KIT.h"
#include "StdTypes.h"
#include "SENSORS_interface.h"


#define SAFE_LEVEL 40
#define HEAT_LEVEL 80

void FireSystem_Init(void) ; 

void FireSystem_Runnable(void) ; 

void FireSystem_Safe (void) ; 
void FireSystem_Heat (void) ; 
void FireSystem_Danger (void) ; 

#endif /* FIRESYSTEM_INTERFACE_H_ */