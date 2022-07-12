/********************************** (C) COPYRIGHT *******************************
 * File Name          : CH58x_uart2.c
 * Author             : WCH
 * Version            : V1.2
 * Date               : 2021/11/17
 * Description
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/

#include "CH58x_common.h"

/*********************************************************************
 * @fn      UART2_DefInit
 *
 * @brief   串口默认初始化配置
 *
 * @param   none
 *
 * @return  none
 */
void UART2_DefInit(void)
{
    UART2_BaudRateCfg(115200);
    R8_UART2_FCR = (2 << 6) | RB_FCR_TX_FIFO_CLR | RB_FCR_RX_FIFO_CLR | RB_FCR_FIFO_EN; // FIFO打开，触发点4字节
    R8_UART2_LCR = RB_LCR_WORD_SZ;
    R8_UART2_IER = RB_IER_TXD_EN;
    R8_UART2_DIV = 1;
}

/*********************************************************************
 * @fn      UART2_BaudRateCfg
 *
 * @brief   串口波特率配置
 *
 * @param   baudrate    - 波特率
 *
 * @return  none
 */
void UART2_BaudRateCfg(uint32_t baudrate)
{
    uint32_t x;

    x = 10 * GetSysClock() / 8 / baudrate;
    x = (x + 5) / 10;
    R16_UART2_DL = (uint16_t)x;
}

/*********************************************************************
 * @fn      UART2_ByteTrigCfg
 *
 * @brief   串口字节触发中断配置
 *
 * @param   b       - 触发字节数 refer to UARTByteTRIGTypeDef
 *
 * @return  none
 */
void UART2_ByteTrigCfg(UARTByteTRIGTypeDef b)
{
    R8_UART2_FCR = (R8_UART2_FCR & ~RB_FCR_FIFO_TRIG) | (b << 6);
}

/*********************************************************************
 * @fn      UART2_INTCfg
 *
 * @brief   串口中断配置
 *
 * @param   s       - 中断控制状态，是否使能相应中断
 * @param   i       - 中断类型
 *                    RB_IER_MODEM_CHG  - 调制解调器输入状态变化中断使能位（仅 UART0 支持）
 *                    RB_IER_LINE_STAT  - 接收线路状态中断
 *                    RB_IER_THR_EMPTY  - 发送保持寄存器空中断
 *                    RB_IER_RECV_RDY   - 接收数据中断
 *
 * @return  none
 */
void UART2_INTCfg(FunctionalState s, uint8_t i)
{
    if(s)
    {
        R8_UART2_IER |= i;
        R8_UART2_MCR |= RB_MCR_INT_OE;
    }
    else
    {
        R8_UART2_IER &= ~i;
    }
}

/*********************************************************************
 * @fn      UART2_Reset
 *
 * @brief   串口软件复位
 *
 * @param   none
 *
 * @return  none
 */
void UART2_Reset(void)
{
    R8_UART2_IER = RB_IER_RESET;
}

/*********************************************************************
 * @fn      UART2_SendString
 *
 * @brief   串口多字节发送
 *
 * @param   buf     - 待发送的数据内容首地址
 * @param   l       - 待发送的数据长度
 *
 * @return  none
 */
void UART2_SendString(uint8_t *buf, uint16_t l)
{
    uint16_t len = l;

    while(len)
    {
        if(R8_UART2_TFC != UART_FIFO_SIZE)
        {
            R8_UART2_THR = *buf++;
            len--;
        }
    }
}

/*********************************************************************
 * @fn      UART2_RecvString
 *
 * @brief   串口读取多字节
 *
 * @param   buf     - 读取数据存放缓存区首地址
 *
 * @return  读取数据长度
 */
uint16_t UART2_RecvString(uint8_t *buf)
{
    uint16_t len = 0;

    while(R8_UART2_RFC)
    {
        *buf++ = R8_UART2_RBR;
        len++;
    }

    return (len);
}

