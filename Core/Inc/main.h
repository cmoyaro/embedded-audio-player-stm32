/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "string.h"
#include "stdbool.h"
#include "cbuffer.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define WIFI_RDY_Pin GPIO_PIN_13
#define WIFI_RDY_GPIO_Port GPIOC
#define WIFI_DRDY_Pin GPIO_PIN_14
#define WIFI_DRDY_GPIO_Port GPIOC
#define WIFI_EN_Pin GPIO_PIN_15
#define WIFI_EN_GPIO_Port GPIOC
#define BAR_LED0_Pin GPIO_PIN_0
#define BAR_LED0_GPIO_Port GPIOH
#define BAR_LED1_Pin GPIO_PIN_1
#define BAR_LED1_GPIO_Port GPIOH
#define TMP_I2C_SCL_Pin GPIO_PIN_0
#define TMP_I2C_SCL_GPIO_Port GPIOC
#define TMP_I2C_SDA_Pin GPIO_PIN_1
#define TMP_I2C_SDA_GPIO_Port GPIOC
#define AUDIO_IN_Pin GPIO_PIN_2
#define AUDIO_IN_GPIO_Port GPIOC
#define BAR_LED2_Pin GPIO_PIN_3
#define BAR_LED2_GPIO_Port GPIOC
#define BAR_LED5_Pin GPIO_PIN_0
#define BAR_LED5_GPIO_Port GPIOA
#define BAR_LED4_Pin GPIO_PIN_1
#define BAR_LED4_GPIO_Port GPIOA
#define BAR_LED3_Pin GPIO_PIN_2
#define BAR_LED3_GPIO_Port GPIOA
#define JOYSTICK_UP_Pin GPIO_PIN_3
#define JOYSTICK_UP_GPIO_Port GPIOA
#define AUDIO_OUT_Pin GPIO_PIN_4
#define AUDIO_OUT_GPIO_Port GPIOA
#define EXT_SPI_CLK_Pin GPIO_PIN_5
#define EXT_SPI_CLK_GPIO_Port GPIOA
#define EXT_SPI_MISO_Pin GPIO_PIN_6
#define EXT_SPI_MISO_GPIO_Port GPIOA
#define EXT_SPI_MOSI_Pin GPIO_PIN_7
#define EXT_SPI_MOSI_GPIO_Port GPIOA
#define EXT_SPI_NCS_Pin GPIO_PIN_4
#define EXT_SPI_NCS_GPIO_Port GPIOC
#define EXT_ADC_IN0_Pin GPIO_PIN_5
#define EXT_ADC_IN0_GPIO_Port GPIOC
#define EXT_ADC_IN1_Pin GPIO_PIN_0
#define EXT_ADC_IN1_GPIO_Port GPIOB
#define ACC_INT_Pin GPIO_PIN_1
#define ACC_INT_GPIO_Port GPIOB
#define ACC_INT_EXTI_IRQn EXTI1_IRQn
#define ACC_SPI_NCS_Pin GPIO_PIN_2
#define ACC_SPI_NCS_GPIO_Port GPIOB
#define ACC_SPI_CLK_Pin GPIO_PIN_10
#define ACC_SPI_CLK_GPIO_Port GPIOB
#define TS_G1_CS_Pin GPIO_PIN_12
#define TS_G1_CS_GPIO_Port GPIOB
#define TS_G1_IO_Pin GPIO_PIN_13
#define TS_G1_IO_GPIO_Port GPIOB
#define ACC_SPI_MISO_Pin GPIO_PIN_14
#define ACC_SPI_MISO_GPIO_Port GPIOB
#define ACC_SPI_MOSI_Pin GPIO_PIN_15
#define ACC_SPI_MOSI_GPIO_Port GPIOB
#define TS_G4_CS_Pin GPIO_PIN_6
#define TS_G4_CS_GPIO_Port GPIOC
#define TS_G4_IO_Pin GPIO_PIN_7
#define TS_G4_IO_GPIO_Port GPIOC
#define JOYSTICK_RI_Pin GPIO_PIN_8
#define JOYSTICK_RI_GPIO_Port GPIOC
#define JOYSTICK_DO_Pin GPIO_PIN_9
#define JOYSTICK_DO_GPIO_Port GPIOC
#define JOYSTICK_LE_Pin GPIO_PIN_8
#define JOYSTICK_LE_GPIO_Port GPIOA
#define AUDIO_SHDWN_Pin GPIO_PIN_9
#define AUDIO_SHDWN_GPIO_Port GPIOA
#define EXT_DIO0_Pin GPIO_PIN_10
#define EXT_DIO0_GPIO_Port GPIOA
#define TS_G3_CS_Pin GPIO_PIN_10
#define TS_G3_CS_GPIO_Port GPIOC
#define TS_G3_IO_Pin GPIO_PIN_11
#define TS_G3_IO_GPIO_Port GPIOC
#define WIFI_UART_TX_Pin GPIO_PIN_12
#define WIFI_UART_TX_GPIO_Port GPIOC
#define WIFI_UART_RX_Pin GPIO_PIN_2
#define WIFI_UART_RX_GPIO_Port GPIOD
#define TS_G2_CS_Pin GPIO_PIN_4
#define TS_G2_CS_GPIO_Port GPIOB
#define TS_G2_IO_Pin GPIO_PIN_5
#define TS_G2_IO_GPIO_Port GPIOB
#define EXT_UART_TX_Pin GPIO_PIN_6
#define EXT_UART_TX_GPIO_Port GPIOB
#define EXT_UART_RX_Pin GPIO_PIN_7
#define EXT_UART_RX_GPIO_Port GPIOB
#define EXT_DIO1_Pin GPIO_PIN_3
#define EXT_DIO1_GPIO_Port GPIOH
#define EXT_I2C_SCL_Pin GPIO_PIN_8
#define EXT_I2C_SCL_GPIO_Port GPIOB
#define EXT_I2C_SDA_Pin GPIO_PIN_9
#define EXT_I2C_SDA_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
