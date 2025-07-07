/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usb_otg.c
  * @brief   This file provides code for the configuration
  *          of the USB_OTG instances.
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
#include "usb_otg.h"

/* USER CODE BEGIN 0 */
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_cdc.h"
#include "usbd_cdc_if.h"

void MX_USB_OTG_FS_PCD_Private_PushBytes(uint8_t *pu8Data, uint16_t u16Length)
{
	CBUFFER_Push(CBUFFER_USB_RX, pu8Data, u16Length);
}

USBD_HandleTypeDef hUsbDeviceFS;
/* USER CODE END 0 */

PCD_HandleTypeDef hpcd_USB_OTG_FS;

/* USB_OTG_FS init function */

void MX_USB_OTG_FS_PCD_Init(void)
{

  /* USER CODE BEGIN USB_OTG_FS_Init 0 */
  /* Init circular buffer */
  CBUFFER_Init(CBUFFER_USB_RX);

  /* Unlink previous class resources */
  hUsbDeviceFS.pClass = NULL;
  hUsbDeviceFS.pUserData = NULL;
  hUsbDeviceFS.pConfDesc = NULL;

  /* Assign USBD Descriptors */
  hUsbDeviceFS.pDesc = &CDC_Desc;

  /* Set Device initial State */
  hUsbDeviceFS.dev_state = USBD_STATE_DEFAULT;
  hUsbDeviceFS.id = 0;
  /* USER CODE END USB_OTG_FS_Init 0 */

  /* USER CODE BEGIN USB_OTG_FS_Init 1 */
  hpcd_USB_OTG_FS.pData = &hUsbDeviceFS;
  hUsbDeviceFS.pData = &hpcd_USB_OTG_FS;
  /* Init Device Library */
  /* USER CODE END USB_OTG_FS_Init 1 */
  hpcd_USB_OTG_FS.Instance = USB_OTG_FS;
  hpcd_USB_OTG_FS.Init.dev_endpoints = 6;
  hpcd_USB_OTG_FS.Init.speed = PCD_SPEED_FULL;
  hpcd_USB_OTG_FS.Init.phy_itface = PCD_PHY_EMBEDDED;
  hpcd_USB_OTG_FS.Init.Sof_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.low_power_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.lpm_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.battery_charging_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.use_dedicated_ep1 = DISABLE;
  hpcd_USB_OTG_FS.Init.vbus_sensing_enable = DISABLE;
  hpcd_USB_OTG_FS.Init.dma_enable = DISABLE;
  if (HAL_PCD_Init(&hpcd_USB_OTG_FS) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USB_OTG_FS_Init 2 */
  HAL_PCDEx_SetRxFiFo(&hpcd_USB_OTG_FS, 0x100);
  HAL_PCDEx_SetTxFiFo(&hpcd_USB_OTG_FS, 0, 0x10);
  HAL_PCDEx_SetTxFiFo(&hpcd_USB_OTG_FS, 1, 0x10);

  /* Add supported class and start the library */
  if (USBD_RegisterClass(&hUsbDeviceFS, USBD_CDC_CLASS) != USBD_OK) {
	  Error_Handler();
  }
  if (USBD_CDC_RegisterInterface(&hUsbDeviceFS, &USBD_CDC_fops) != USBD_OK) {
	  Error_Handler();
  }
  if (USBD_Start(&hUsbDeviceFS) != USBD_OK) {
	  Error_Handler();
  }
  /* USER CODE END USB_OTG_FS_Init 2 */

}

void HAL_PCD_MspInit(PCD_HandleTypeDef* pcdHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
  if(pcdHandle->Instance==USB_OTG_FS)
  {
  /* USER CODE BEGIN USB_OTG_FS_MspInit 0 */
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_CRSInitTypeDef RCC_CRSInitStruct = {0};

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48;
  	RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;

  	if (HAL_RCC_OscConfig(&RCC_OscInitStruct)!= HAL_OK)
  	{
  	  Error_Handler();
  	}
  /* USER CODE END USB_OTG_FS_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_CLK48;
    PeriphClkInit.IclkClockSelection = RCC_CLK48CLKSOURCE_HSI48;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USB_OTG_FS GPIO Configuration
    PA11     ------> USB_OTG_FS_DM
    PA12     ------> USB_OTG_FS_DP
    */
    GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF10_USB;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USB_OTG_FS clock enable */
    __HAL_RCC_USB_CLK_ENABLE();

    /* Enable VDDUSB */
    if(__HAL_RCC_PWR_IS_CLK_DISABLED())
    {
      __HAL_RCC_PWR_CLK_ENABLE();
      HAL_PWREx_EnableVddUSB();
      __HAL_RCC_PWR_CLK_DISABLE();
    }
    else
    {
      HAL_PWREx_EnableVddUSB();
    }

    /* USB_OTG_FS interrupt Init */
    HAL_NVIC_SetPriority(OTG_FS_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(OTG_FS_IRQn);
  /* USER CODE BEGIN USB_OTG_FS_MspInit 1 */
    /* Enable CRS Clock */
    __HAL_RCC_CRS_CLK_ENABLE();

    /* Default Synchro Signal division factor (not divided) */
    RCC_CRSInitStruct.Prescaler = RCC_CRS_SYNC_DIV1;

    /* Set the SYNCSRC[|:0] bits according to CRS_Source value */
    RCC_CRSInitStruct.Source = RCC_CRS_SYNC_SOURCE_USB;

    /* HSI48 is synchronized with USB SOF at 1KHz rate */
    RCC_CRSInitStruct.ReloadValue = RCC_CRS_RELOADVALUE_DEFAULT;
    RCC_CRSInitStruct.ErrorLimitValue = RCC_CRS_ERRORLIMIT_DEFAULT;
    RCC_CRSInitStruct.Polarity = RCC_CRS_SYNC_POLARITY_RISING;

    /* Set the TRIM[5:0] to the default value */
    RCC_CRSInitStruct.HSI48CalibrationValue = RCC_CRS_HSI48CALIBRATION_DEFAULT;

    /* Start automatic syncrhonization */
    HAL_RCCEx_CRSConfig(&RCC_CRSInitStruct);
  /* USER CODE END USB_OTG_FS_MspInit 1 */
  }
}

void HAL_PCD_MspDeInit(PCD_HandleTypeDef* pcdHandle)
{

  if(pcdHandle->Instance==USB_OTG_FS)
  {
  /* USER CODE BEGIN USB_OTG_FS_MspDeInit 0 */

  /* USER CODE END USB_OTG_FS_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USB_CLK_DISABLE();

    /**USB_OTG_FS GPIO Configuration
    PA11     ------> USB_OTG_FS_DM
    PA12     ------> USB_OTG_FS_DP
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_11|GPIO_PIN_12);

    /* USB_OTG_FS interrupt Deinit */
    HAL_NVIC_DisableIRQ(OTG_FS_IRQn);
  /* USER CODE BEGIN USB_OTG_FS_MspDeInit 1 */

  /* USER CODE END USB_OTG_FS_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
/* USB deinit function */
void MX_USB_OTG_FS_PCD_DeInit(void)
{

	USBD_Stop(&hUsbDeviceFS);
	USBD_DeInit(&hUsbDeviceFS);
	/* DeInit circular buffer */
	CBUFFER_DeInit(CBUFFER_USB_RX);

}
/* USB cable detection function */
bool MX_USB_OTG_FS_PCD_CablePluggedIn(void)
{

	return ((hUsbDeviceFS.dev_state == USBD_STATE_CONFIGURED) ? (true) : (false));

}
/* USB transmit function */
HAL_StatusTypeDef MX_USB_OTG_FS_PCD_Transmit(uint8_t *pData, uint16_t Size)
{

	HAL_StatusTypeDef eResult = HAL_OK;

	switch (CDC_Itf_Transmit(pData, Size)) {
		case USBD_OK:
			eResult = HAL_OK;
			break;
		case USBD_BUSY:
			eResult = HAL_BUSY;
			break;
		case USBD_EMEM:
		case USBD_FAIL:
			eResult = HAL_ERROR;
		default:
			break;
	}

	return eResult;

}
/* USB receive function */
HAL_StatusTypeDef MX_USB_OTG_FS_PCD_Receive(uint8_t *pData, uint16_t Size)
{

	if (Size <= CBUFFER_GetUsageSpace(CBUFFER_USB_RX)) {
		CBUFFER_Pop(CBUFFER_USB_RX, pData, Size);
		return HAL_OK;
	}
	else {
		return HAL_ERROR;
	}

}
/* USER CODE END 1 */
