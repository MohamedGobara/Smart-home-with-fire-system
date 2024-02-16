
#ifndef FIRESYTEMSMART_INTERFACE_H_
#define FIRESYTEMSMART_INTERFACE_H_




#include "ADC_interface.h"
#include "KeyPad_interface.h"
#include "LCD_Interface.h"
#include "KIT.h"
#include "StdTypes.h"
#include "SENSORS_interface.h"


#define SAFE_LEVEL_SMART 40
#define HEAT_LEVEL_SMART 80

void FireSystemSmart_Init(void) ;

void FireSystemSmart_Runnable(void) ;

void FireSystemSmart_Safe (void) ;
void FireSystemSmart_Heat (void) ;
void FireSystemSmart_Danger (void) ;

void FireSystemSmart_ExitDangerMode(void)  ; 

#endif /* FIRESYTEMSMART_INTERFACE_H_ */