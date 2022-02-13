/********************************** (C) COPYRIGHT *******************************
* File Name          : SLEEP.h
* Author             : WCH
* Version            : V1.0
* Date               : 2018/11/12
* Description        : 
*******************************************************************************/



/******************************************************************************/
#ifndef __SLEEP_H
#define __SLEEP_H

#ifdef __cplusplus
extern "C"
{
#endif
	

/*********************************************************************
 * GLOBAL VARIABLES
 */
	
/*********************************************************************
 * FUNCTIONS
 */
extern void HAL_SleepInit( void );	

extern u32 CH58X_LowPower( u32 time );
/*********************************************************************
*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif