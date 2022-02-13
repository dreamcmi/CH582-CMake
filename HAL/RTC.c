/********************************** (C) COPYRIGHT *******************************
 * File Name          : RTC.c
 * Author             : WCH
 * Version            : V1.1
 * Date               : 2019/11/05
 * Description        : RTC���ü����ʼ��
 *******************************************************************************/

/******************************************************************************/
/* ͷ�ļ����� */
#include "CH58x_common.h"
#include "HAL.h"

/*********************************************************************
 * CONSTANTS
 */
#define RTC_INIT_TIME_HOUR              0
#define RTC_INIT_TIME_MINUTE            0
#define RTC_INIT_TIME_SECEND            0

/***************************************************
 * Global variables
 */
u32V RTCTigFlag;

/*******************************************************************************
 * Function Name  : RTC_SetTignTime
 * Description    : ����RTC����ʱ��
 * Input          : 
 * Output         : None
 * Return         : None
 *******************************************************************************/
void RTC_SetTignTime( u32 time )
{
  R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;
  R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
  SAFEOPERATE;
  R32_RTC_TRIG = time;
  RTCTigFlag = 0;
}

/*******************************************************************************
 * @fn          RTC_IRQHandler
 *
 * @brief       RTC�жϴ���
 *
 * input parameters
 *
 * @param       None.
 *
 * output parameters
 *
 * @param       None.
 *
 * @return      None.
 */
__INTERRUPT
__HIGH_CODE
void RTC_IRQHandler( void )
{
  R8_RTC_FLAG_CTRL = ( RB_RTC_TMR_CLR | RB_RTC_TRIG_CLR );
  RTCTigFlag = 1;
}

/*******************************************************************************
 * @fn          HAL_Time0Init
 *
 * @brief       ϵͳ��ʱ����ʼ��
 *
 * input parameters
 *
 * @param       None.
 *
 * output parameters
 *
 * @param       None.
 *
 * @return      None.
 */
void HAL_TimeInit( void )
{
#if( CLK_OSC32K )
  R8_SAFE_ACCESS_SIG = 0x57;
  R8_SAFE_ACCESS_SIG = 0xa8;
  R8_CK32K_CONFIG &= ~(RB_CLK_OSC32K_XT|RB_CLK_XT32K_PON);
  R8_CK32K_CONFIG |= RB_CLK_INT32K_PON;
  Lib_Calibration_LSI();
#else
  R8_SAFE_ACCESS_SIG = 0x57;
  R8_SAFE_ACCESS_SIG = 0xa8;
  R8_CK32K_CONFIG |= RB_CLK_OSC32K_XT | RB_CLK_INT32K_PON | RB_CLK_XT32K_PON;
  R8_SAFE_ACCESS_SIG = 0;
#endif
  RTC_InitTime( 2020, 1, 1, 0, 0, 0 );    //RTCʱ�ӳ�ʼ����ǰʱ��
  TMOS_TimerInit( 0 );
}

/******************************** endfile @ time ******************************/
