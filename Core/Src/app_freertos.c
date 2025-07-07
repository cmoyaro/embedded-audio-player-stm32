/**
 ******************************************************************************
 * File Name          : app_freertos.c
 * Description        : Code for freertos applications
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

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os2.h"
/* Private includes ----------------------------------------------------------*/
#include "touchsensing.h"
#include "i2c.h"
#include "usart.h"
#include "adc.h"
#include "dac.h"
#include "tim.h"
#include "stdbool.h"
#include "string.h"
#include "stdio.h"
#include "usb_otg.h"
#include "audio.h"

/* Private typedef -----------------------------------------------------------*/
typedef enum {
	LED_0 = 0, LED_1, LED_2, LED_3, LED_4, LED_5, LED_MAX

} bar_led;

typedef enum {
	BUTTON_UP = 0, BUTTON_DOWN, BUTTON_RIGHT, BUTTON_LEFT, BUTTON_MAX

} joystick_btn;

typedef struct {
	GPIO_TypeDef *pPort;
	uint16_t Pin;

} gpio_t;

/* Private define ------------------------------------------------------------*/
#define JOYSTICK_UP_FLAG 	0x01
#define JOYSTICK_DO_FLAG 	0x02
#define JOYSTICK_RI_FLAG 	0x04
#define JOYSTICK_LE_FLAG 	0x08

#define ADC_CONV_CPLT_FLAG 	0x01
#define ADC_ERROR_FLAG 	 	0x02

#define DAC_CONV_CPLT_FLAG 	0x01
#define DAC_ERROR_FLAG 	 	0x02

#define AUDIO_BUFFER_LEN			40960
#define DMA_TRANSFER_LEN	1024 /*Dividimos el valor original en 8*/
#define DAC_TRANSFER_LEN	8192  /* Maximum value */

/*Creamos unas constantes necesarias para el ej1*/
#define MAX_VOLUMEN 26
#define MAX_SENSIBILITY 21
/*Creamos una constante necesaria para el ej2*/
#define MAX_AUDIO 680

/*Creamos una constante necesaria para el ej4*/
#define AUDIO_ESCALA 0.0625
/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
gpio_t gpio_led_bar[LED_MAX] = { { .pPort = BAR_LED0_GPIO_Port, .Pin =
BAR_LED0_Pin }, { .pPort = BAR_LED1_GPIO_Port, .Pin = BAR_LED1_Pin }, { .pPort =
BAR_LED2_GPIO_Port, .Pin = BAR_LED2_Pin }, { .pPort =
BAR_LED3_GPIO_Port, .Pin = BAR_LED3_Pin }, { .pPort = BAR_LED4_GPIO_Port, .Pin =
BAR_LED4_Pin }, { .pPort =
BAR_LED5_GPIO_Port, .Pin = BAR_LED5_Pin }, };

gpio_t gpio_joystick[BUTTON_MAX] = { { .pPort = JOYSTICK_UP_GPIO_Port, .Pin =
JOYSTICK_UP_Pin }, { .pPort = JOYSTICK_DO_GPIO_Port, .Pin =
JOYSTICK_DO_Pin }, { .pPort = JOYSTICK_RI_GPIO_Port, .Pin =
JOYSTICK_RI_Pin }, { .pPort = JOYSTICK_LE_GPIO_Port, .Pin =
JOYSTICK_LE_Pin }, };

uint32_t u32DataBlock_Audio[AUDIO_BUFFER_LEN] = { 0 };
uint32_t u32RecordedAudio[AUDIO_BUFFER_LEN] = { 0 };

/*Variables creadas por mi*/
int position = 0; //Necesario para TocandoTarea()
int volumeFactor = 1; //Necesario para TocandoTarea()
int loopEnable = 0; //Necesario para act 3
int hasRecording = 0; //Necesario para act 4

/* Definitions for JoystickUpTask */
osThreadId_t JoystickUpTaskHandle;
const osThreadAttr_t JoystickUpTask_attributes = { .name = "JoystickUpTask",
		.priority = (osPriority_t) osPriorityNormal, .stack_size = 128 * 4 };

/* Definitions for JoystickDoTask */
osThreadId_t JoystickDoTaskHandle;
const osThreadAttr_t JoystickDoTask_attributes = { .name = "JoystickDoTask",
		.priority = (osPriority_t) osPriorityNormal, .stack_size = 128 * 4 };

/* Definitions for JoystickRiTask */
osThreadId_t JoystickRiTaskHandle;
const osThreadAttr_t JoystickRiTask_attributes = { .name = "JoystickRiTask",
		.priority = (osPriority_t) osPriorityNormal, .stack_size = 128 * 4 };

/* Definitions for JoystickLeTask */
osThreadId_t JoystickLeTaskHandle;
const osThreadAttr_t JoystickLeTask_attributes = { .name = "JoystickLeTask",
		.priority = (osPriority_t) osPriorityNormal, .stack_size = 128 * 4 };

/* Definitions for AudioTask */
osThreadId_t AudioTaskHandle;
const osThreadAttr_t AudioTask_attributes = { .name = "AudioTask", .priority =
		(osPriority_t) osPriorityNormal, .stack_size = 128 * 4 };

/* Definitions for JoystickEvent */
osEventFlagsId_t JoystickEventHandle;
const osEventFlagsAttr_t JoystickEvent_attributes = { .name = "JoystickEvent" };

/* Definitions for Dac1Event */
osEventFlagsId_t Dac1EventHandle;
const osEventFlagsAttr_t Dac1Event_attributes = { .name = "Dac1Event" };

/* Definitions for Adc1Event */
osEventFlagsId_t Adc1EventHandle;
const osEventFlagsAttr_t Adc1Event_attributes = { .name = "Adc1Event" };

/* Private function prototypes -----------------------------------------------*/
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc);
void HAL_ADC_ErrorCallback(ADC_HandleTypeDef *hadc);

void HAL_DAC_ConvCpltCallbackCh1(DAC_HandleTypeDef *hdac);
void HAL_DAC_ErrorCallbackCh1(DAC_HandleTypeDef *hdac);

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
	if (ADC1 == hadc->Instance) {
		osEventFlagsSet(Adc1EventHandle, ADC_CONV_CPLT_FLAG);
	}
}

void HAL_ADC_ErrorCallback(ADC_HandleTypeDef *hadc) {
	if (ADC1 == hadc->Instance) {
		osEventFlagsSet(Adc1EventHandle, ADC_ERROR_FLAG);
	}
}

void HAL_DAC_ConvCpltCallbackCh1(DAC_HandleTypeDef *hdac) {
	if (DAC1 == hdac->Instance) {
		osEventFlagsSet(Dac1EventHandle, DAC_CONV_CPLT_FLAG);
	}
}

void HAL_DAC_ErrorCallbackCh1(DAC_HandleTypeDef *hdac) {
	if (DAC1 == hdac->Instance) {
		osEventFlagsSet(Dac1EventHandle, DAC_ERROR_FLAG);
	}
}

void LEDTurnOff(bar_led led);
void LEDTurnOn(bar_led led);
void LEDToggle(bar_led led);
void LEDClear(void); //Para limpiar los LEDs
GPIO_PinState JoystickReadButton(joystick_btn button);
HAL_StatusTypeDef AudioOutOneShot(void);
HAL_StatusTypeDef AudioInOneShot(void);

void LEDTurnOff(bar_led led) {
	HAL_GPIO_WritePin(gpio_led_bar[led].pPort, gpio_led_bar[led].Pin,
			GPIO_PIN_SET);
}

void LEDTurnOn(bar_led led) {
	HAL_GPIO_WritePin(gpio_led_bar[led].pPort, gpio_led_bar[led].Pin,
			GPIO_PIN_RESET);
}

void LEDToggle(bar_led led) {
	HAL_GPIO_TogglePin(gpio_led_bar[led].pPort, gpio_led_bar[led].Pin);
}
void LEDClear() {
	for (int i = 0; i < LED_MAX; i++) {
		LEDTurnOff(i);
	}
}
GPIO_PinState JoystickReadButton(joystick_btn button) {
	return HAL_GPIO_ReadPin(gpio_joystick[button].pPort,
			gpio_joystick[button].Pin);
}

HAL_StatusTypeDef AudioOutOneShot(void) {
	uint32_t dac_flag, sample_num = 0;

	/*
	 * We turn on the pin that manages the power of the output enabling the speaker to reproduce the sound
	 */
	HAL_GPIO_WritePin(AUDIO_SHDWN_GPIO_Port, AUDIO_SHDWN_Pin, GPIO_PIN_SET);

	/*
	 * We start the TIM2 to mark the sampling rate reproduction of each sample
	 */

	if (HAL_OK != MX_TIM2_Start()) {
		return HAL_ERROR;
	}
	if (hasRecording == 1) {
		for (sample_num = 0; AUDIO_BUFFER_LEN > sample_num; sample_num++)
			u32DataBlock_Audio[sample_num] = u32RecordedAudio[sample_num]
					* volumeFactor;
	} else {
		for (sample_num = 0; AUDIO_BUFFER_LEN > sample_num; sample_num++)
			u32DataBlock_Audio[sample_num] =
					u32DataBlock_AudioExample[sample_num] * volumeFactor;
	}

	/*
	 * We move through the entire array producing sound using the Digital to Analog converter (DAC1) and
	 * using the DMA as an intermediate buffer. Each sample of the array is a sample for the DAC
	 * So using the DMA (8192 samples) we sent them to the DAC also the sound is produced with the timming
	 * determined by TIM2
	 */
	for (sample_num = 0; AUDIO_BUFFER_LEN > sample_num; sample_num +=
	DMA_TRANSFER_LEN) {

		//LEDTurnOff(led_num--);
		LEDClear();
		/*
		 * We initialize tha DAC with a block (at least) of 8192 samples
		 */
		if (HAL_OK != MX_DAC1_Start(&u32DataBlock_Audio[sample_num],
		DMA_TRANSFER_LEN)) {
			return HAL_ERROR;
		}
		int ledsToActivate = (u32DataBlock_Audio[sample_num] * 1.9)
				/ (MAX_AUDIO);
		for (int i = 0; i < ledsToActivate; i++) {
			LEDTurnOn(i);
		}

		/*
		 * We wait for the completion reproduction using the Flag DAC_CONV_CPLT_FLAG
		 */
		dac_flag = osEventFlagsWait(Dac1EventHandle, DAC_CONV_CPLT_FLAG,
		osFlagsWaitAny, osWaitForever);
		if (DAC_CONV_CPLT_FLAG != dac_flag) {
			return HAL_ERROR;
		}

	}
	for (int i = 0; i <= position; i++) {
		LEDTurnOn(i);
	}
	/*
	 * Stop the TIM2
	 */
	if (HAL_OK != MX_TIM2_Stop()) {
		return HAL_ERROR;
	}

	/*
	 * Stop the DAC
	 */
	if (HAL_OK != MX_DAC1_Stop()) {
		return HAL_ERROR;
	}
	/*
	 * Turn of the speaker
	 */
	HAL_GPIO_WritePin(AUDIO_SHDWN_GPIO_Port, AUDIO_SHDWN_Pin, GPIO_PIN_RESET);

	return HAL_OK;
}

/*Función obtenida de la Solución PEC 3 y modificada ligeramente para la práctica */

HAL_StatusTypeDef AudioInOneShot(void) {
	uint32_t adc_flag, sample_num = 0;
	bar_led led_num = LED_0;
// Apaguem els leds
	for (uint8_t i = 0; i < LED_MAX; i++) {
		LEDTurnOff((bar_led) i);
	}
// Activem el micro
	HAL_GPIO_WritePin(AUDIO_IN_GPIO_Port, AUDIO_IN_Pin, GPIO_PIN_SET);

// Calibrar el ADC
	if (HAL_OK != MX_ADC1_Calibration()) {
		return HAL_ERROR;
	}
// Iniciem el TIM2
	if (HAL_OK != MX_TIM2_Start()) {
		return HAL_ERROR;
	}
// Processem
	for (sample_num = 0; AUDIO_BUFFER_LEN > sample_num; sample_num +=
	DAC_TRANSFER_LEN) {
// Engeguem els leds de forma paulatina
		if (led_num < LED_MAX) {
			LEDTurnOn(led_num++);
		}
		if (HAL_OK != MX_ADC1_Start(&u32RecordedAudio[sample_num],
		DAC_TRANSFER_LEN)) {
			MX_TIM2_Stop();
			return HAL_ERROR;
		}
		adc_flag = osEventFlagsWait(Adc1EventHandle, ADC_CONV_CPLT_FLAG,
		osFlagsWaitAny, osWaitForever);
		if (adc_flag != ADC_CONV_CPLT_FLAG) {
			MX_TIM2_Stop();
			MX_ADC1_Stop();
			return HAL_ERROR;
		}
		for (uint32_t i = 0; i < DAC_TRANSFER_LEN; i++) {
			u32RecordedAudio[sample_num + i] *= AUDIO_ESCALA;
		}
	}
// Anem parant perifèrics
	if (HAL_OK != MX_ADC1_Stop()) {
		MX_TIM2_Stop();
		return HAL_ERROR;
	}
	if (HAL_OK != MX_TIM2_Stop()) {
		return HAL_ERROR;
	}
// Apaguem micro
	HAL_GPIO_WritePin(AUDIO_IN_GPIO_Port, AUDIO_IN_Pin, GPIO_PIN_RESET);

//Se apagan los LEDs y se establece conforme a la variable position
	LEDClear();
	for (int i = 0; i <= position; i++) {
		LEDTurnOn(i);
	}
	return HAL_OK;
}

void JoystickUpTask(void *argument);
void JoystickDoTask(void *argument);
void JoystickRiTask(void *argument);
void JoystickLeTask(void *argument);
void AudioTask(void *argument);
void TocandoTarea(void);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
 * @brief  FreeRTOS initialization
 * @param  None
 * @retval None
 */
void MX_FREERTOS_Init(void) {

	/* creation of JoystickUpTask */
	JoystickUpTaskHandle = osThreadNew(JoystickUpTask, NULL,
			&JoystickUpTask_attributes);

	/* creation of JoystickDoTask */
	JoystickDoTaskHandle = osThreadNew(JoystickDoTask, NULL,
			&JoystickDoTask_attributes);

	/* creation of JoystickRiTask */
	JoystickRiTaskHandle = osThreadNew(JoystickRiTask, NULL,
			&JoystickRiTask_attributes);

	/* creation of JoystickLeTask */
	JoystickLeTaskHandle = osThreadNew(JoystickLeTask, NULL,
			&JoystickLeTask_attributes);

	/* creation of AudioTask */
	AudioTaskHandle = osThreadNew(AudioTask, NULL, &AudioTask_attributes);

	/* creation of JoystickEvent */
	JoystickEventHandle = osEventFlagsNew(&JoystickEvent_attributes);

	/* creation of Dac1Event */
	Dac1EventHandle = osEventFlagsNew(&Dac1Event_attributes);

	/* creation of Adc1Event */
	Adc1EventHandle = osEventFlagsNew(&Adc1Event_attributes);

}
/**
 * @brief Function implementing the JoystickUpTask thread.
 * @param argument: Not used
 * @retval None
 */
void JoystickUpTask(void *argument) {
	/* Infinite loop */
	for (;;) {
		// Wait for Joystick Button Pulsed
		if (GPIO_PIN_SET == JoystickReadButton(BUTTON_UP)) {
			// Wait 50ms for bouncing
			osDelay(50);
			hasRecording = 1; //Pasa de 0 a 1 y por tanto significa que se debera reproducir la grabación
			// Check if Joystick Button is still pulsed
			if (GPIO_PIN_SET == JoystickReadButton(BUTTON_UP)) {
				// Send Event
				osEventFlagsSet(JoystickEventHandle, JOYSTICK_UP_FLAG);
				// Wait for Joystick Button Release
				while (GPIO_PIN_SET == JoystickReadButton(BUTTON_UP))
					;
				// Wait 50ms for bouncing
				osDelay(50);
			}
		} else {
			osDelay(1);
		}
	}
}

/**
 * @brief Function implementing the JoystickDoTask thread.
 * @param argument: Not used
 * @retval None
 */
void JoystickDoTask(void *argument) {
	/* Infinite loop */
	for (;;) {
		// Wait for Joystick Button Pulsed
		if (GPIO_PIN_SET == JoystickReadButton(BUTTON_DOWN)) {
			// Wait 50ms for bouncing
			osDelay(50);
			// Check if Joystick Button is still pulsed
			if (GPIO_PIN_SET == JoystickReadButton(BUTTON_DOWN)) {
				// Send Event
				osEventFlagsSet(JoystickEventHandle, JOYSTICK_DO_FLAG);
				// Wait for Joystick Button Release
				while (GPIO_PIN_SET == JoystickReadButton(BUTTON_DOWN))
					;
				// Wait 50ms for bouncing
				osDelay(50);
			}
		} else {
			osDelay(1);
		}
	}
}

/**
 * @brief Function implementing the JoystickRiTask thread.
 * @param argument: Not used
 * @retval None
 */
void JoystickRiTask(void *argument) {
	/* Infinite loop */
	for (;;) {
		// Wait for Joystick Button Pulsed
		if (GPIO_PIN_SET == JoystickReadButton(BUTTON_RIGHT)) {
			// Wait 50ms for bouncing
			osDelay(50);
			loopEnable = 1; //Se hará un bucle
			// Check if Joystick Button is still pulsed
			if (GPIO_PIN_SET == JoystickReadButton(BUTTON_RIGHT)) {
				// Send Event
				osEventFlagsSet(JoystickEventHandle, JOYSTICK_RI_FLAG);
				// Wait for Joystick Button Release
				while (GPIO_PIN_SET == JoystickReadButton(BUTTON_RIGHT))
					;
				// Wait 50ms for bouncing
				osDelay(50);
			}
		} else {
			osDelay(1);
		}
	}
}

/**
 * @brief Function implementing the JoystickLeTask thread.
 * @param argument: Not used
 * @retval None
 */
void JoystickLeTask(void *argument) {
	/* Infinite loop */
	for (;;) {
		// Wait for Joystick Button Pulsed
		if (GPIO_PIN_SET == JoystickReadButton(BUTTON_LEFT)) {
			// Wait 50ms for bouncing
			osDelay(50);
			loopEnable = 0; //Se terminara el bucle
			// Check if Joystick Button is still pulsed
			if (GPIO_PIN_SET == JoystickReadButton(BUTTON_LEFT)) {
				// Send Event
				osEventFlagsSet(JoystickEventHandle, JOYSTICK_LE_FLAG);
				// Wait for Joystick Button Release
				while (GPIO_PIN_SET == JoystickReadButton(BUTTON_LEFT))
					;
				// Wait 50ms for bouncing
				osDelay(50);
			}
		} else {
			osDelay(1);
		}
	}
}

/**
 * @brief Function implementing the AudioTask thread.
 * @param argument: Not used
 * @retval None
 */
void AudioTask(void *argument) {
	uint32_t joystick_flag;
	/* Infinite loop */
	for (;;) {
		joystick_flag = osEventFlagsGet(JoystickEventHandle);

		switch (joystick_flag) {
		case JOYSTICK_UP_FLAG:
			if (HAL_OK != AudioInOneShot()) {
				goto error;
			}
			osEventFlagsClear(JoystickEventHandle, JOYSTICK_UP_FLAG);
			break;

		case JOYSTICK_DO_FLAG:
			if (HAL_OK != AudioOutOneShot()) {
				goto error;
			}
			for (; loopEnable == 1;) {
				joystick_flag = osEventFlagsGet(JoystickEventHandle);
				if (joystick_flag == JOYSTICK_LE_FLAG) {
					osEventFlagsClear(JoystickEventHandle, JOYSTICK_LE_FLAG);
				} else {
					if (HAL_OK != AudioOutOneShot()) {
						goto error;
					}
				}
			}
			osEventFlagsClear(JoystickEventHandle, JOYSTICK_DO_FLAG);
			break;

		case JOYSTICK_RI_FLAG:
			osEventFlagsClear(JoystickEventHandle, JOYSTICK_RI_FLAG);
			break;
		case JOYSTICK_LE_FLAG:
			osEventFlagsClear(JoystickEventHandle, JOYSTICK_LE_FLAG);
			break;
		default:
			TocandoTarea(); //Utilizamos la función
			break;
		}
		osDelay(1);
	}
	error: osThreadExit();
}
/*Creamos la función solicitada en el ej 1 */
void TocandoTarea() {
	if (TSL_USER_STATUS_BUSY != MX_TOUCHSENSING_Task()) {
		if (TSL_STATEID_DETECT == MX_TOUCHSENSING_GetStatus()) {
			position = MX_TOUCHSENSING_GetPosition() / MAX_SENSIBILITY;
			int volumen = MX_TOUCHSENSING_GetPosition() / MAX_VOLUMEN;
			int multiplicador = 1 << volumen; // Usamos el desplazamiento de bits para 2^volumen
			volumeFactor = multiplicador; // Actualizamos los LEDs según la posición detectada
			LEDClear(); //Limpiamos los LEDs

			for (int i = 0; i <= position; i++) {
				LEDTurnOn(i);
			}
		}
	}
}

