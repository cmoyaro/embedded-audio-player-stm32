/**
  ******************************************************************************
  * @file    USB_Device/CDC_Standalone/USB_Device/App/usbd_cdc_if.c
  * @author  MCD Application Team
  * @brief   Source file for USBD CDC interface
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

/* Includes ------------------------------------------------------------------ */
#include "usbd_cdc_if.h"

/* Private typedef ----------------------------------------------------------- */
/* Private define ------------------------------------------------------------ */

/* Private macro ------------------------------------------------------------- */
/* Private variables --------------------------------------------------------- */
//USBD_CDC_LineCodingTypeDef LineCoding = {
//  115200,                       /* baud rate */
//  0x00,                         /* stop bits-1 */
//  0x00,                         /* parity - none */
//  0x08                          /* nb. of bits 8 */
//};

uint8_t UserRxBuffer[APP_RX_DATA_SIZE]; /* Received Data over USB are stored in
                                         * this buffer */
uint8_t UserTxBuffer[APP_TX_DATA_SIZE]; /* Received Data over UART (CDC
                                         * interface) are stored in this buffer
                                         */
/* Definitions for UsbSemaphoreHandle */
osSemaphoreId_t UsbSemaphoreHandle;
const osSemaphoreAttr_t UsbSemaphore_attributes = {
  .name = "UsbSemaphore"
};
/* USB handler declaration */
extern USBD_HandleTypeDef hUsbDeviceFS;

extern void MX_USB_OTG_FS_PCD_Private_PushBytes(uint8_t *pData, uint16_t Size);

/* Private function prototypes ----------------------------------------------- */
static int8_t CDC_Itf_Init(void);
static int8_t CDC_Itf_DeInit(void);
static int8_t CDC_Itf_Control(uint8_t Cmd, uint8_t * pBuf, uint16_t Size);
static int8_t CDC_Itf_Receive(uint8_t * pBuf, uint32_t * Len);
static int8_t CDC_TransmitCplt(uint8_t *pBuf, uint32_t * Len, uint8_t epNum);

USBD_CDC_ItfTypeDef USBD_CDC_fops = {
  CDC_Itf_Init,
  CDC_Itf_DeInit,
  CDC_Itf_Control,
  CDC_Itf_Receive,
  CDC_TransmitCplt
};

/* Private functions --------------------------------------------------------- */

/**
  * @brief  Initializes the CDC media low layer
  * @param  None
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_Itf_Init(void)
{
  /* ##-1- Creation of Semaphore ############################################## */
  UsbSemaphoreHandle = osSemaphoreNew(1, 1, &UsbSemaphore_attributes);
  /* ##-2- Set Application Buffers ############################################ */
  USBD_CDC_SetTxBuffer(&hUsbDeviceFS, UserTxBuffer, 0);
  USBD_CDC_SetRxBuffer(&hUsbDeviceFS, UserRxBuffer);
  /* ##-3- Arm the USB reception ############################################## */
  USBD_CDC_ReceivePacket(&hUsbDeviceFS);

  return (USBD_OK);
}

/**
  * @brief  CDC_Itf_DeInit
  *         DeInitializes the CDC media low layer
  * @param  None
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_Itf_DeInit(void)
{
  return (USBD_OK);
}

/**
  * @brief  CDC_Itf_Control
  *         Manage the CDC class requests
  * @param  Cmd: Command code
  * @param  Buf: Buffer containing command data (request parameters)
  * @param  Len: Number of data to be sent (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_Itf_Control(uint8_t Cmd, uint8_t * pBuf, uint16_t Size)
{
  switch (Cmd)
  {
  case CDC_SEND_ENCAPSULATED_COMMAND:
    /* Add your code here */
    break;

  case CDC_GET_ENCAPSULATED_RESPONSE:
    /* Add your code here */
    break;

  case CDC_SET_COMM_FEATURE:
    /* Add your code here */
    break;

  case CDC_GET_COMM_FEATURE:
    /* Add your code here */
    break;

  case CDC_CLEAR_COMM_FEATURE:
    /* Add your code here */
    break;

    /*******************************************************************************/
    /* Line Coding Structure                                                       */
    /*-----------------------------------------------------------------------------*/
    /* Offset | Field       | Size | Value  | Description                          */
    /* 0      | dwDTERate   |   4  | Number |Data terminal rate, in bits per second*/
    /* 4      | bCharFormat |   1  | Number | Stop bits                            */
    /*                                        0 - 1 Stop bit                       */
    /*                                        1 - 1.5 Stop bits                    */
    /*                                        2 - 2 Stop bits                      */
    /* 5      | bParityType |  1   | Number | Parity                               */
    /*                                        0 - None                             */
    /*                                        1 - Odd                              */
    /*                                        2 - Even                             */
    /*                                        3 - Mark                             */
    /*                                        4 - Space                            */
    /* 6      | bDataBits  |   1   | Number Data bits (5, 6, 7, 8 or 16).          */
    /*******************************************************************************/
  case CDC_SET_LINE_CODING:
//    LineCoding.bitrate = (uint32_t) (pBuf[0] | (pBuf[1] << 8) |
//                                     (pBuf[2] << 16) | (pBuf[3] << 24));
//    LineCoding.format = pBuf[4];
//    LineCoding.paritytype = pBuf[5];
//    LineCoding.datatype = pBuf[6];
//
//    /* Set the new configuration */
//    ComPort_Config();
    break;

  case CDC_GET_LINE_CODING:
//    pBuf[0] = (uint8_t) (LineCoding.bitrate);
//    pBuf[1] = (uint8_t) (LineCoding.bitrate >> 8);
//    pBuf[2] = (uint8_t) (LineCoding.bitrate >> 16);
//    pBuf[3] = (uint8_t) (LineCoding.bitrate >> 24);
//    pBuf[4] = LineCoding.format;
//    pBuf[5] = LineCoding.paritytype;
//    pBuf[6] = LineCoding.datatype;
    break;

  case CDC_SET_CONTROL_LINE_STATE:
    /* Add your code here */
    break;

  case CDC_SEND_BREAK:
    /* Add your code here */
    break;

  default:
    break;
  }

  return (USBD_OK);
}

/**
  * @brief  CDC_Itf_Receive
  *         Data received over USB OUT endpoint are sent over CDC interface
  *         through this function.
  * @param  Buf: Buffer of data to be transmitted
  * @param  Len: Number of data received (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_Itf_Receive(uint8_t * Buf, uint32_t * Len)
{
  MX_USB_OTG_FS_PCD_Private_PushBytes(Buf, (uint16_t)*Len);
  USBD_CDC_SetRxBuffer(&hUsbDeviceFS, &Buf[0]);
  USBD_CDC_ReceivePacket(&hUsbDeviceFS);

  return (USBD_OK);
}

/**
  * @brief  CDC_Itf_Transmit
  *         Data to send over USB IN endpoint are sent over CDC interface
  *         through this function.
  *         @note
  *
  *
  * @param  Buf: Buffer of data to be sent
  * @param  Len: Number of data to be sent (in bytes)
  * @retval USBD_OK if all operations are OK else USBD_FAIL or USBD_BUSY
  */
uint8_t CDC_Itf_Transmit(uint8_t* Buf, uint16_t Len)
{
  uint8_t result = USBD_OK;

  osSemaphoreAcquire(UsbSemaphoreHandle, osWaitForever);
  USBD_CDC_SetTxBuffer(&hUsbDeviceFS, Buf, Len);
  result = USBD_CDC_TransmitPacket(&hUsbDeviceFS);

  return result;
}

/**
  * @brief  CDC_TransmitCplt
  *         Data transmitted callback
  *
  *         @note
  *         This function is IN transfer complete callback used to inform user that
  *         the submitted Data is successfully sent over USB.
  *
  * @param  Buf: Buffer of data to be received
  * @param  Len: Number of data received (in bytes)
  * @retval Result of the operation: USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CDC_TransmitCplt(uint8_t *Buf, uint32_t *Len, uint8_t epNum)
{
  UNUSED(Buf);
  UNUSED(Len);
  UNUSED(epNum);
  osSemaphoreRelease(UsbSemaphoreHandle);

  return (USBD_OK);
}
