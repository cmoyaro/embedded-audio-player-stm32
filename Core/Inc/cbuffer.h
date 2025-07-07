/* **************  COPYRIGHT (c) 2019 DIPRO TECHNOLOGIES  ******************* */
/**
 * @file 	   cbuffer.h
 * @brief      Gestion de una cola circular de 8 bits.
 *
 * @author     Marc Garcia - mgarcia@diprotech.io
 * @version    3.0
 * @date       11/03/2019
 */
/* ************************************************************************** */

#ifndef CBUFFER_H
#define	CBUFFER_H

/* --------------------- Public Includes ------------------------------------ */
/** @defgroup CBUFFER_Public_Includes CBUFFER Public Includes
  * @{
  */

#include "main.h"

/**
  * @}
  */

/* --------------------- Public Defines ------------------------------------- */
/** @defgroup CBUFFER_Public_Defines CBUFFER Public Defines
  * @{
  */

/**
  * @brief  CBUFFER thresholds
  */
#define CBUFFER_ITEMS_MAX 		((uint8_t)1U)
#define CBUFFER_BUFFER_SIZE 	((uint16_t)1024U)	/* Only power-of-2 numbers (E.g. 16, 128, 512...) */

/**
  * @}
  */

/* --------------------- Public Data Types ---------------------------------- */
/** @defgroup CBUFFER_Public_DataTypes CBUFFER Public Data Types
  * @{
  */

/**
  * @brief  UTIL CIRCBUF items
  */
typedef enum
{
	CBUFFER_USB_RX = 0U,

} e_CBUFFER_Items;

/**
  * @}
  */

/* --------------------- Public Variables ----------------------------------- */
/** @defgroup CBUFFER_Public_Variables CBUFFER Public Variables
  * @{
  */



/**
  * @}
  */

/* --------------------- Public Routine headers ----------------------------- */
/** @defgroup CBUFFER_Public_Headers CBUFFER Public Headers
  * @{
  */

void CBUFFER_Init(e_CBUFFER_Items eItem);
void CBUFFER_DeInit(e_CBUFFER_Items eItem);
void CBUFFER_Push(e_CBUFFER_Items eItem, uint8_t *pu8Data, uint16_t u16Length);
void CBUFFER_PushByte(e_CBUFFER_Items eItem, uint8_t u8Byte);
void CBUFFER_Pop(e_CBUFFER_Items eItem, uint8_t *pu8Data, uint16_t u16Length);
void CBUFFER_PopByte(e_CBUFFER_Items eItem, uint8_t *u8Byte);
void CBUFFER_Read(e_CBUFFER_Items eItem, uint16_t u16Position, uint8_t *pu8Data, uint16_t u16Length);
void CBUFFER_RemoveLastBytes(e_CBUFFER_Items eItem, uint16_t u16Length);
uint16_t CBUFFER_GetUsageSpace(e_CBUFFER_Items eItem);
uint16_t CBUFFER_GetFreeSpace(e_CBUFFER_Items eItem);
uint16_t CBUFFER_GetBufferSize(e_CBUFFER_Items eItem);
void CBUFFER_Flush(e_CBUFFER_Items eItem);
bool CBUFFER_IsEmpty(e_CBUFFER_Items eItem);
bool CBUFFER_IsFull(e_CBUFFER_Items eItem);

/**
  * @}
  */

#endif	/* CBUFFER_H */
