#include "SENSORS_interface.h"
#include "StdTypes.h"

static u16 arr_adc[10] = {0} ;
static u16 average_temp=0  , total_temp=0  ;
void TempFilter_Init(void)  {
	
	/* get first 10 temp */
	for(u8 i =  0 ; i<10 ; i++) {
		
		
		arr_adc[i]  =  SENSORS_NTC10KGetTemp() ;
	}
	/* sum first 10 temp */
	for(u8 i = 0 ; i<10 ; i++) {
		
		
		total_temp+=arr_adc[i] ;
	}
	/* calculate average */
	average_temp =  total_temp/10 ;
}
void TempFilter_Runnable(void)   {
	
	static u8 index_arrADC = 0 ;

	if(index_arrADC<10)  {
		
		arr_adc[index_arrADC] = SENSORS_NTC10KGetTemp() ;
		index_arrADC++ ;
		
	}
	else  {
		
		index_arrADC = 0 ;
	}
	
	/* calculate average every get temperature */
	for(u8 i = 0 ; i<10 ; i++) {
		
		
		total_temp+=arr_adc[i] ;
	}
	
	average_temp =  total_temp/10 ;
	
}  // Low execution time

u16 TempFilter_Getter(void)  {
	
	return average_temp ;
}  //No time
