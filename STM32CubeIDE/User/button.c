/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : module_name.c
  * @brief          : module_name driver / logic implementation
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes --------------------------------------------------------------------*/
#include "main.h"
#include "button.h"
#include "string.h"
#include "led_module.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define BUTTON_DEBOUNCE_MS  30U

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
BUTTON_t BUTTON;
/* USER CODE END PV */

/* Private function prototypes ------------------------------------------------*/
/* USER CODE BEGIN PFP */

void BUTTON_Init_(void);
static uint8_t BUTTON_Update(ButtonState *button, uint8_t rawPressed, uint32_t now);

/* USER CODE END PFP */

/* Private user code -----------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* Exported functions ----------------------------------------------------------*/
/* USER CODE BEGIN EF */

/*********************************************************************************
  * @brief
  * @param  None
  * @retval None
*********************************************************************************/
void BUTTON_Init(void)
{
	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* GPIO Ports Clock Enable */
	LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
	LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB);

	GPIO_InitStruct.Pin = LL_GPIO_PIN_2;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_DOWN;
	LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = LL_GPIO_PIN_10;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_DOWN;
	LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	memset(&BUTTON, 0, sizeof(BUTTON));

	uint32_t now = HAL_GetTick();

	BUTTON.K2.rawPressed = LL_GPIO_IsInputPinSet(BUTTON_K2_GPIO_Port, BUTTON_K2_Pin) ? 1U : 0U;
	BUTTON.K2.stablePressed = BUTTON.K2.rawPressed;
	BUTTON.K2.rawChangedAt = now;

	BUTTON.K3.rawPressed = LL_GPIO_IsInputPinSet(BUTTON_K3_GPIO_Port, BUTTON_K3_Pin) ? 1U : 0U;
	BUTTON.K3.stablePressed = BUTTON.K3.rawPressed;
	BUTTON.K3.rawChangedAt = now;
}

/*********************************************************************************
  * @brief
  * @param  None
  * @retval None
*********************************************************************************/
static uint8_t BUTTON_Update(ButtonState *button, uint8_t rawPressed, uint32_t now)
{
  if (rawPressed != button->rawPressed)
  {
    button->rawPressed = rawPressed;
    button->rawChangedAt = now;
  }

  if ((button->rawPressed != button->stablePressed) &&
      ((uint32_t)(now - button->rawChangedAt) >= BUTTON_DEBOUNCE_MS))
  {
    button->stablePressed = button->rawPressed;
    return button->stablePressed;
  }

  return 0U;
}

/*********************************************************************************
  * @brief
  * @param  None
  * @retval None
*********************************************************************************/
void BUTTON_Process(void)
{
	static s16 speed = 100;

	uint32_t now = HAL_GetTick();

	if (BUTTON_Update(&BUTTON.K2, LL_GPIO_IsInputPinSet(BUTTON_K2_GPIO_Port, BUTTON_K2_Pin), now) ? 1U : 0U)
	{
		/* Обработать нажатие K2 */
		static u8 trigg = 1;

		if(trigg) {
			LED_On(LED2);
			MC_StartMotor1();
		} else {
			LED_Off(LED2);
//			speed = 500;
//			MC_ProgramSpeedRampMotor1(RPM_2_SPEED_UNIT(speed), 0);
			MC_StopMotor1();
		}

		trigg = !trigg;
	}

	if (BUTTON_Update(&BUTTON.K3, LL_GPIO_IsInputPinSet(BUTTON_K3_GPIO_Port, BUTTON_K3_Pin), now) ? 1U : 0U)
	{
		static u8 trigg = 1;
		/* Обработать нажатие K3 */
		if(trigg == 1) {
			LED_On(LED3);
			speed = 11000;
			MC_ProgramSpeedRampMotor1(RPM_2_SPEED_UNIT(speed), 0);
		} else {
			speed = 300;
			MC_ProgramSpeedRampMotor1(RPM_2_SPEED_UNIT(speed), 0);
			LED_Off(LED3);
		}
		trigg = !trigg;
	}

//	switch(BUTTON.mainStateMachine) {
//	case 0:
//		BUTTON.mainStateMachine++;
//		break;
//
//	case 1:
//		break;
//
//	case 2:
//		break;
//
//	default:
//		BUTTON.mainStateMachine = 0;
//		break;
//	}
}

/* USER CODE END EF */
