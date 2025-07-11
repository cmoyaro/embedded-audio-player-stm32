/**
  ******************************************************************************
  * @file    USB_Device/CDC_Standalone/USB_Device/App/usbd_cdc_if.h
  * @author  MCD Application Team
  * @brief   Header for usbd_cdc_interface.c file.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USBD_CDC_IF_H
#define __USBD_CDC_IF_H

/* Includes ------------------------------------------------------------------*/
#include "usbd_cdc.h"
#include "cmsis_os2.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Define size for the receive and transmit buffer over CDC */
#define APP_RX_DATA_SIZE  1024
#define APP_TX_DATA_SIZE  1024
/* User can use this section to tailor USARTx/UARTx instance used and associated 
   resources */
/* Definition for USARTx clock resources */

//#define USARTx                               USART1
//#define USARTx_CLK_ENABLE()                  __HAL_RCC_USART1_CLK_ENABLE()
//#define USARTx_RX_GPIO_CLK_ENABLE()          __HAL_RCC_GPIOA_CLK_ENABLE()
//#define USARTx_TX_GPIO_CLK_ENABLE()          __HAL_RCC_GPIOA_CLK_ENABLE()
//#define DMAx_CLK_ENABLE()                    __HAL_RCC_GPDMA1_CLK_ENABLE()

//#define USARTx_FORCE_RESET()                 __HAL_RCC_USART1_FORCE_RESET()
//#define USARTx_RELEASE_RESET()               __HAL_RCC_USART1_RELEASE_RESET()

/* Definition for USARTx Pins */
//#define USARTx_TX_PIN                        GPIO_PIN_9
//#define USARTx_TX_GPIO_PORT                  GPIOA
//#define USARTx_TX_AF                         GPIO_AF7_USART1
//#define USARTx_RX_PIN                        GPIO_PIN_10
//#define USARTx_RX_GPIO_PORT                  GPIOA
//#define USARTx_RX_AF                         GPIO_AF7_USART1

/* Definition for USARTx's NVIC: used for receiving data over Rx pin */
//#define USARTx_IRQn                          USART1_IRQn
//#define USARTx_IRQHandler                    USART1_IRQHandler

/* Definition for USARTx's GPDMA */
//#define USARTx_TX_GPDMA_CHANNEL              GPDMA1_Channel0_BASE
//#define USARTx_RX_GPDMA_CHANNEL              GPDMA1_Channel1_BASE

/* Definition for USARTx's GPDMA Request */
//#define USARTx_TX_GPDMA_REQUEST             GPDMA1_REQUEST_USART1_TX
//#define USARTx_RX_GPDMA_REQUEST             GPDMA1_REQUEST_USART1_RX

/* Definition for USARTx's NVIC */
//#define USARTx_GPDMA_TX_IRQn                GPDMA1_Channel0_IRQn
//#define USARTx_GPDMA_RX_IRQn                GPDMA1_Channel1_IRQn
//#define USARTx_GPDMA_TX_IRQHandler          GPDMA1_Channel0_IRQHandler
//#define USARTx_GPDMA_RX_IRQHandler          GPDMA1_Channel1_IRQHandler

/* Definition for TIMx clock resources */
//#define TIMx                                TIM3
//#define TIMx_CLK_ENABLE                    __HAL_RCC_TIM3_CLK_ENABLE
//#define TIMx_FORCE_RESET()                 __HAL_RCC_USART3_FORCE_RESET()
//#define TIMx_RELEASE_RESET()               __HAL_RCC_USART3_RELEASE_RESET()
 
/* Definition for TIMx's NVIC */
//#define TIMx_IRQn                          TIM3_IRQn
//#define TIMx_IRQHandler                    TIM3_IRQHandler

/* Periodically, the state of the buffer "UserTxBuffer" is checked.
   The period depends on CDC_POLLING_INTERVAL */
//#define CDC_POLLING_INTERVAL             5 /* in ms. The max is 65ms and the min is 1ms */

extern USBD_CDC_ItfTypeDef  USBD_CDC_fops;

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
uint8_t CDC_Itf_Transmit(uint8_t* Buf, uint16_t Len);
#endif /* __USBD_CDC_IF_H */

