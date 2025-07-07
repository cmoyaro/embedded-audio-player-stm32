/* **************  COPYRIGHT (c) 2019 DIPRO TECHNOLOGIES  ******************* */
/**
 * @file 	   cbuffer.c
 * @brief      Gestion de una cola circular de 8 bits.
 *
 * @author     Marc Garcia - mgarcia@diprotech.io
 * @version    3.0
 * @date       11/03/2019
 */
/* ************************************************************************** */

/* --------------------- Private Includes ----------------------------------- */
/** @defgroup CBUFFER_Private_Includes CBUFFER Private Includes
  * @{
  */

#include "cbuffer.h"

/**
  * @}
  */

/* --------------------- Private Defines ------------------------------------ */
/** @defgroup CBUFFER_Private_Defines CBUFFER Private Defines
  * @{
  */



/**
  * @}
  */

/* --------------------- Private Data Types --------------------------------- */
/** @defgroup CBUFFER_Private_DataTypes CBUFFER Private Data Types
  * @{
  */

typedef struct
{
	/* ----- Configuration ----- */

	/* ----- Variables ----- */
	volatile uint16_t u16HeadIndex;
	volatile uint16_t u16TailIndex;
	volatile uint16_t u16CurrentNumItems;
	volatile uint8_t au8Buffer[CBUFFER_BUFFER_SIZE];
	bool bIsInitialized;
	/* ----- Substructure functions ----- */

} s_CBUFFER;

/**
  * @}
  */

/* --------------------- Private Variables ---------------------------------- */
/** @defgroup CBUFFER_Private_Variables CBUFFER Private Variables
  * @{
  */

volatile s_CBUFFER asCBUFFER[CBUFFER_ITEMS_MAX] =
	{
		{.bIsInitialized = false}
	};

/**
  * @}
  */

/* --------------------- Private Routine Headers ---------------------------- */
/** @defgroup CBUFFER_Private_Headers CBUFFER Private Headers
  * @{
  */



/**
  * @}
  */

/* --------------------- Private Routines ----------------------------------- */
/** @defgroup CBUFFER_Private_Methods CBUFFER Private Methods
  * @{
  */



/**
  * @}
  */

/* --------------------- Public Routines ------------------------------------ */
/** @defgroup CBUFFER_Public_Methods CBUFFER Public Methods
  * @{
  */

/**
 * @brief      	Metodo para inicializar el m�dulo.
 *
 * @pre        	Ninguna.
 *
 * @post       	Modulo inicializado.
 *
 * @param[in]  	eItem:		Enum del tipo e_CBUFFER_Items que indica el
 *                   		bufer circular a tratar.
 *
 * @return		Ninguno.
 */
void CBUFFER_Init(e_CBUFFER_Items eItem)
{

	if (false == asCBUFFER[eItem].bIsInitialized)
	{
		/* Initialise variables */
		asCBUFFER[eItem].u16CurrentNumItems = 0U;
		asCBUFFER[eItem].u16HeadIndex = 0U;
		asCBUFFER[eItem].u16TailIndex = 0U;
		/* Set initialise flag */
		asCBUFFER[eItem].bIsInitialized = true;
	}

}

/**
 * @brief     	Metodo para desinicializar el m�dulo.
 *
 * @pre        	Llamar a CBUFFER_Init().
 *
 * @post       	Modulo desinicializado.
 *
 * @param[in]  	eItem:		Enum del tipo e_CBUFFER_Items que indica el
 *                   		bufer circular a tratar.
 *
 * @return		Ninguno.
 */
void CBUFFER_DeInit(e_CBUFFER_Items eItem)
{

	if (true == asCBUFFER[eItem].bIsInitialized)
	{
		/* Deinitialise variables */
		asCBUFFER[eItem].u16CurrentNumItems = 0U;
		asCBUFFER[eItem].u16HeadIndex = 0U;
		asCBUFFER[eItem].u16TailIndex = 0U;
		/* Reset initialise flag */
		asCBUFFER[eItem].bIsInitialized = false;
	}

}

/**
 * @brief      	Metodo para escribir, uno o m�s, bytes en el b�fer circular.
 *
 * @warning		Este metodo requiere que haya tantas posiciones libres en el
 * 				bufer como bytes se quieran escribir. Para ello, llamar antes
 * 				a CBUFFER_GetFreeSpace(), y asegurar que la escritura es
 * 				posible. Si no, se puede corromper el b�fer circular!!
 *
 * @pre        	Llamar a CBUFFER_Init().
 *
 * @post       	Bytes escritos en el bufer circular.
 *
 * @param[in]  	eItem		Enum del tipo e_CBUFFER_Items que indica el
 *                   		bufer a tratar.
 * @param[out] 	ptu8Data    Puntero al array de bytes que se quieren escribir
 * 							en el bufer circular.
 * @param[in]  	u16Length   Longitud del array. Valor mayor o igual a 1.
 *
 * @return     	Ninguno.
 */
void CBUFFER_Push(e_CBUFFER_Items eItem, uint8_t *pu8Data, uint16_t u16Length)
{

	uint16_t u16Temporal = 0U;

	/* Push one, or more, bytes in the circular buffer */
	for (;u16Length > u16Temporal; u16Temporal++)
	{
		asCBUFFER[eItem].au8Buffer[asCBUFFER[eItem].u16TailIndex++] = pu8Data[u16Temporal];
		asCBUFFER[eItem].u16TailIndex &= ~CBUFFER_BUFFER_SIZE;
	}
	/* Increase all bytes pushed */
	asCBUFFER[eItem].u16CurrentNumItems += u16Length;

}

/**
 * @brief      	Metodo para escribir un unico byte en el bufer circular.
 *
 * @warning		Este metodo requiere que haya, almenos, una posicion libre
 * 				en el b�fer. Para ello, llamar antes a CBUFFER_IsFull(),
 * 				y asegurar que la escritura es posible. Si no, se puede
 * 				corromper el bufer circular!!
 *
 * @pre        	Llamar a CBUFFER_Init().
 *
 * @post       	Byte escrito en el bufer circular.
 *
 * @param[in]  	eItem		Enum del tipo e_CBUFFER_Items que indica el
 *                   		bufer a tratar.
 * @param[in]  	u8Byte      Byte a escribir.
 *
 * @return     	Ninguno.
 */
void CBUFFER_PushByte(e_CBUFFER_Items eItem, uint8_t u8Byte)
{

	/* Push one byte in a circular buffer */
	asCBUFFER[eItem].au8Buffer[asCBUFFER[eItem].u16TailIndex++] = u8Byte;
	asCBUFFER[eItem].u16TailIndex &= ~CBUFFER_BUFFER_SIZE;
	/* Increase the byte pushed */
	asCBUFFER[eItem].u16CurrentNumItems++;

}

/**
 * @brief      	Metodo para obtener, uno o mas, bytes del bufer circular.
 *
 * @warning		Este metodo requiere que se saque un numero menor, o igual, a
 * 				los bytes almacenados en el bufer. Para ello, llamar antes a
 * 				CBUFFER_GetUsageSpace(), y asegurar que la lectura es
 * 				posible. Si no se puede acabar sacando basura!!
 *
 * @pre        	Llamar a CBUFFER_Init().
 *
 * @post       	Bytes extraidos del bufer circular.
 *
 * @param[in]  	eItem		Enum del tipo e_CBUFFER_Items que indica el
 *                   		bufer a tratar.
 * @param[out] 	pu8Data    Puntero al array de datos para almacenar los bytes
 * 							extraidos.
 * @param[in]  	u16Length   Longitud del array. Valor mayor o igual a 1.
 *
 * @return     	Ninguno.
 */
void CBUFFER_Pop(e_CBUFFER_Items eItem, uint8_t *pu8Data, uint16_t u16Length)
{

	uint16_t u16Temporal = 0U;

	/* Extract bytes from a circular buffer */
	for (; u16Length > u16Temporal; u16Temporal++)
	{
		pu8Data[u16Temporal] = asCBUFFER[eItem].au8Buffer[asCBUFFER[eItem].u16HeadIndex++];
		asCBUFFER[eItem].u16HeadIndex &= ~CBUFFER_BUFFER_SIZE;
	}
	/* Decrease all bytes extracted */
	asCBUFFER[eItem].u16CurrentNumItems -= u16Length;

}

/**
 * @brief      	Metodo para extraer un unico byte del bufer circular.
 *
 * @warning		Este metodo requiere que se lea un byte del bufer. Para
 * 				ello, llamar antes a CBUFFER_IsEmpty(), y asegurar
 * 				que la lectura es posible. Si no se puede leer basura!!
 *
 * @pre        	Llamar a CBUFFER_Init().
 *
 * @post       	Byte extraido del bufer circular.
 *
 * @param[in]  	eItem		Enum del tipo e_CBUFFER_Items que indica el
 *                   		bufer a tratar.
 * @param[out] 	u8Byte    	Byte a extraer.
 *
 * @return     	Ninguno.
 */
void CBUFFER_PopByte(e_CBUFFER_Items eItem, uint8_t *u8Byte)
{


	/* Extract one byte from a circular buffer */
	*u8Byte = asCBUFFER[eItem].au8Buffer[asCBUFFER[eItem].u16HeadIndex++];
	asCBUFFER[eItem].u16HeadIndex &= ~CBUFFER_BUFFER_SIZE;
	/* Decrease the byte extracted */
	asCBUFFER[eItem].u16CurrentNumItems--;

}

/**
 * @brief      	Metodo para leer bytes del buffer circular, sin extraerlos.
 *
 * @warning		Este metodo requiere que se lea un numero menor, o igual, a
 * 				los bytes almacenados en el bufer. Para ello, llamar antes a
 * 				CBUFFER_GetUsageSpace(), y asegurar que la lectura es
 * 				posible. Si no se puede acabar leyendo basura!!
 *
 * @pre        	Llamar a CBUFFER_Init().
 *
 * @post       	Ninguno.
 *
 * @param[in]  	eItem		Enum del tipo e_CBUFFER_Items que indica el
 *                   		bufer a tratar.
 * @param[in]  	u16Position Posicion del bufer a partir del cual empezar a leer.
 * @param[out] 	ptu8Data    Puntero al array de datos para almacenar los bytes
 * 							leidos.
 * @param[in]  	u16Length   Longitud del array. Valor mayor o igual a 1.
 *
 * @return     	Ninguno.
 */
void CBUFFER_Read(e_CBUFFER_Items eItem, uint16_t u16Position, uint8_t *pu8Data, uint16_t u16Length)
{

	uint16_t u16Temporal = 0U, u16StartPos = 0U;

	/* Set start position to read */
	u16StartPos = asCBUFFER[eItem].u16HeadIndex + u16Position;
	u16StartPos &= ~CBUFFER_BUFFER_SIZE;
	/* Read the bytes from a circular buffer */
	for (; u16Length > u16Temporal; u16Temporal++)
	{
		pu8Data[u16Temporal] = asCBUFFER[eItem].au8Buffer[u16StartPos++];
		u16StartPos &= ~CBUFFER_BUFFER_SIZE;
	}

}

/**
 * @brief      	Metodo para eliminar los bytes mas nuevos del bufer circular.
 *
 * @warning		Este metodo requiere que se borre un numero menor, o igual, a
 * 				los bytes almacenados en el bufer. Para ello, llamar antes a
 * 				CBUFFER_GetUsageSpace(), y asegurar que el borrado es
 * 				posible. Si no se puede corromper el bufer circular!!
 *
 * @note		Util para eliminar los ecos producidos por algunas transmisiones.
 * 				Vease protocolo 485.
 *
 * @pre        	Llamar a CBUFFER_Init().
 *
 * @post       	Bytes eliminados del bufer circular.
 *
 * @param[in]  	eItem		Enum del tipo e_CBUFFER_Items que indica el
 *                   		bufer a tratar.
 * @param[in]  	u16Length   Longitud de bytes a borrar.
 *
 * @return     	Ninguno
 */
void CBUFFER_RemoveLastBytes(e_CBUFFER_Items eItem, uint16_t u16Length)
{

	/* Decrease the bytes to be removed */
	asCBUFFER[eItem].u16CurrentNumItems -= u16Length;
	/* Set a tail position */
	asCBUFFER[eItem].u16TailIndex = asCBUFFER[eItem].u16HeadIndex + asCBUFFER[eItem].u16CurrentNumItems;
	asCBUFFER[eItem].u16TailIndex &= ~CBUFFER_BUFFER_SIZE;

}

/**
 * @brief      	Metodo para obtener el espacio (en numero de bytes) ocupado.
 *
 * @pre        	Llamar a CBUFFER_Init().
 *
 * @post       	Ninguno.
 *
 * @param[in]  	eItem		Enum del tipo e_CBUFFER_Items que indica el
 *                   		bufer a tratar.
 *
 * @return     	Numero de bytes ocupados.
 */
uint16_t CBUFFER_GetUsageSpace(e_CBUFFER_Items eItem)
{

	return asCBUFFER[eItem].u16CurrentNumItems;

}

/**
 * @brief      	Metodo para obtener el espacio (en numero de bytes) libre para
 * 				ocupar.
 *
 * @pre        	Llamar a CBUFFER_Init().
 *
 * @post       	Ninguno.
 *
 * @param[in]  	eItem		Enum del tipo e_CBUFFER_Items que indica el
 *                   		bufer a tratar.
 *
 * @return     	Numero de bytes libres para ocupar.
 */
uint16_t CBUFFER_GetFreeSpace(e_CBUFFER_Items eItem)
{

	return (CBUFFER_BUFFER_SIZE - asCBUFFER[eItem].u16CurrentNumItems);

}

/**
 * @brief      	Metodo para obtener la longitud (en numero de bytes) del bufer.
 *
 * @pre        	Llamar a CBUFFER_Init().
 *
 * @post       	Ninguno.
 *
 * @param[in]  	eItem		Enum del tipo e_CBUFFER_Items que indica el
 *                   		bufer a tratar.
 *
 * @return     	Longitud del bufer en bytes.
 */
uint16_t CBUFFER_GetBufferSize(e_CBUFFER_Items eItem)
{

	return (CBUFFER_BUFFER_SIZE);

}

/**
 * @brief      	Metodo para vaciar completamente el buffer circular.
 *
 * @pre        	Llamar a CBUFFER_Init().
 *
 * @post       	Cola circular vacia.
 *
 * @param[in]  	eItem		Enum del tipo e_CBUFFER_Items que indica el
 *                   		bufer a tratar.
 *
 * @return     	Ninguno.
 */
void CBUFFER_Flush(e_CBUFFER_Items eItem)
{

	/* Reset quantity and pointers */
	asCBUFFER[eItem].u16CurrentNumItems = 0U;
	asCBUFFER[eItem].u16HeadIndex = 0U;
	asCBUFFER[eItem].u16TailIndex = 0U;

}

/**
 * @brief      	Metodo para comprobar si el bufer circular esta completamente
 * 				vacio.
 *
 * @pre        	Llamar a CBUFFER_Init().
 *
 * @post       	Ninguno.
 *
 * @param[in]  	eItem		Enum del tipo e_CBUFFER_Items que indica el
 *                   		bufer a tratar.
 *
 * @return     	Booleano que representa el estado del modulo.
 * @retval     	true   		Vacio.
 * @retval     	false  		No vacio.
 */
bool CBUFFER_IsEmpty(e_CBUFFER_Items eItem)
{

	return ((0U == asCBUFFER[eItem].u16CurrentNumItems) ? (true) : (false));

}

/**
 * @brief      	Metodo para comprobar si el bufer circular esta completamente
 * 				lleno.
 *
 * @pre        	Llamar a CBUFFER_Init().
 *
 * @post       	Ninguno.
 *
 * @param[in]  	eItem		Enum del tipo e_CBUFFER_Items que indica el
 *                   		bufer a tratar.
 *
 * @return     	Booleano que representa el estado del modulo.
 * @retval     	true   		Lleno.
 * @retval     	false  		No lleno.
 */
bool CBUFFER_IsFull(e_CBUFFER_Items eItem)
{

	return ((asCBUFFER[eItem].u16CurrentNumItems >= CBUFFER_BUFFER_SIZE) ? (true) : (false));

}

/**
  * @}
  */
