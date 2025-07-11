/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    tsc.c
  * @brief   This file provides code for the configuration
  *          of the TSC instances.
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
#include "tsc.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

TSC_HandleTypeDef htsc;

/* TSC init function */
void MX_TSC_Init(void)
{

  /* USER CODE BEGIN TSC_Init 0 */

  /* USER CODE END TSC_Init 0 */

  /* USER CODE BEGIN TSC_Init 1 */

  /* USER CODE END TSC_Init 1 */

  /** Configure the TSC peripheral
  */
  htsc.Instance = TSC;
  htsc.Init.CTPulseHighLength = TSC_CTPH_16CYCLES;
  htsc.Init.CTPulseLowLength = TSC_CTPL_16CYCLES;
  htsc.Init.SpreadSpectrum = ENABLE;
  htsc.Init.SpreadSpectrumDeviation = 32;
  htsc.Init.SpreadSpectrumPrescaler = TSC_SS_PRESC_DIV1;
  htsc.Init.PulseGeneratorPrescaler = TSC_PG_PRESC_DIV1;
  htsc.Init.MaxCountValue = TSC_MCV_8191;
  htsc.Init.IODefaultMode = TSC_IODEF_OUT_PP_LOW;
  htsc.Init.SynchroPinPolarity = TSC_SYNC_POLARITY_FALLING;
  htsc.Init.AcquisitionMode = TSC_ACQ_MODE_NORMAL;
  htsc.Init.MaxCountInterrupt = DISABLE;
  htsc.Init.ChannelIOs = TSC_GROUP1_IO2|TSC_GROUP2_IO2|TSC_GROUP3_IO3|TSC_GROUP4_IO2;
  htsc.Init.ShieldIOs = 0;
  htsc.Init.SamplingIOs = TSC_GROUP1_IO1|TSC_GROUP2_IO1|TSC_GROUP3_IO2|TSC_GROUP4_IO1;
  if (HAL_TSC_Init(&htsc) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TSC_Init 2 */

  /* USER CODE END TSC_Init 2 */

}

void HAL_TSC_MspInit(TSC_HandleTypeDef* tscHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(tscHandle->Instance==TSC)
  {
  /* USER CODE BEGIN TSC_MspInit 0 */

  /* USER CODE END TSC_MspInit 0 */
    /* TSC clock enable */
    __HAL_RCC_TSC_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    /**TSC GPIO Configuration
    PB12     ------> TSC_G1_IO1
    PB13     ------> TSC_G1_IO2
    PC6     ------> TSC_G4_IO1
    PC7     ------> TSC_G4_IO2
    PC10     ------> TSC_G3_IO2
    PC11     ------> TSC_G3_IO3
    PB4 (NJTRST)     ------> TSC_G2_IO1
    PB5     ------> TSC_G2_IO2
    */
    GPIO_InitStruct.Pin = TS_G1_CS_Pin|TS_G2_CS_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF9_TSC;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = TS_G1_IO_Pin|TS_G2_IO_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF9_TSC;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = TS_G4_CS_Pin|TS_G3_CS_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF9_TSC;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = TS_G4_IO_Pin|TS_G3_IO_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF9_TSC;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* USER CODE BEGIN TSC_MspInit 1 */

  /* USER CODE END TSC_MspInit 1 */
  }
}

void HAL_TSC_MspDeInit(TSC_HandleTypeDef* tscHandle)
{

  if(tscHandle->Instance==TSC)
  {
  /* USER CODE BEGIN TSC_MspDeInit 0 */

  /* USER CODE END TSC_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TSC_CLK_DISABLE();

    /**TSC GPIO Configuration
    PB12     ------> TSC_G1_IO1
    PB13     ------> TSC_G1_IO2
    PC6     ------> TSC_G4_IO1
    PC7     ------> TSC_G4_IO2
    PC10     ------> TSC_G3_IO2
    PC11     ------> TSC_G3_IO3
    PB4 (NJTRST)     ------> TSC_G2_IO1
    PB5     ------> TSC_G2_IO2
    */
    HAL_GPIO_DeInit(GPIOB, TS_G1_CS_Pin|TS_G1_IO_Pin|TS_G2_CS_Pin|TS_G2_IO_Pin);

    HAL_GPIO_DeInit(GPIOC, TS_G4_CS_Pin|TS_G4_IO_Pin|TS_G3_CS_Pin|TS_G3_IO_Pin);

  /* USER CODE BEGIN TSC_MspDeInit 1 */

  /* USER CODE END TSC_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
