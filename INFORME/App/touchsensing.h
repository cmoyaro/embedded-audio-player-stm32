/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    touchsensing.h
  * @author  MCD Application Team
  * @brief   This file provides code for the configuration
  *                      of the touchsensing instances.
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
#ifndef __touchsensing_H
#define __touchsensing_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "tsl_conf.h"
#include "tsl_user.h"

/* USER CODE BEGIN 0 */
/* USER CODE END 0 */

/* Global variables ---------------------------------------------------------*/

/* USER CODE BEGIN 1 */
/* USER CODE END 1 */

/* TOUCHSENSING init function */
void  MX_TOUCHSENSING_Init(void);

/* USER CODE BEGIN 2 */
TSL_StateId_enum_T MX_TOUCHSENSING_GetStatus(void);
TSL_tPosition_T MX_TOUCHSENSING_GetPosition(void);
tsl_user_status_t MX_TOUCHSENSING_Task(void);
/* USER CODE END 2 */

#ifdef __cplusplus
}
#endif
#endif /*__touchsensing_H */

/**
  * @}
  */

/**
  * @}
  */
