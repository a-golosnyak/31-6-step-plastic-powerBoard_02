/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : module_name.h
  * @brief          : Header for module_name.c file.
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MODULE_NAME_H
#define __MODULE_NAME_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
//typedef struct
//{
//	uint8_t	sendData	:1;
//} Flag_t;

typedef struct
{
  uint8_t rawPressed;
  uint8_t stablePressed;
  uint32_t rawChangedAt;
} ButtonState;

typedef struct
{
	uint32_t	Counter;
	uint8_t	mainStateMachine;

	ButtonState K2;
	ButtonState K3;
//	Flag_t flag;
}BUTTON_t;

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

#define BUTTON_K2_GPIO_Port		GPIOB
#define BUTTON_K2_Pin 			LL_GPIO_PIN_10

#define BUTTON_K3_GPIO_Port		GPIOB
#define BUTTON_K3_Pin 			LL_GPIO_PIN_2

/* USER CODE END EM */

/* Exported variables ---------------------------------------------------------*/
/* USER CODE BEGIN EV */
void BUTTON_Init(void);
void BUTTON_Process(void);

/* USER CODE END EV */

/* Exported functions prototypes ---------------------------------------------*/
/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

#ifdef __cplusplus
}
#endif

#endif /* __MODULE_NAME_H */
