/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    touchsensing.c
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

/* Includes ------------------------------------------------------------------*/
#include "touchsensing.h"

/* USER CODE BEGIN 0 */
/* USER CODE END 0 */

/* USER CODE BEGIN 1 */
/* USER CODE END 1 */

/* Global variables ---------------------------------------------------------*/

/* USER CODE BEGIN 2 */
/* USER CODE END 2 */

/* TOUCHSENSING init function */
void MX_TOUCHSENSING_Init(void)
{
/***************************************/
   /**
  */

  tsl_user_Init();

  /* USER CODE BEGIN 3 */
  /* USER CODE END 3 */

}
/* USER CODE BEGIN 4 */
TSL_StateId_enum_T MX_TOUCHSENSING_GetStatus(void)
{

	return MyLinRots[0].p_Data->StateId;

}

TSL_tPosition_T MX_TOUCHSENSING_GetPosition(void)
{

	return MyLinRots[0].p_Data->Position;

}

tsl_user_status_t MX_TOUCHSENSING_Task(void)
{

	return tsl_user_Exec();

}
/* USER CODE END 4 */

/**
  * @}
  */

/**
  * @}
  */
