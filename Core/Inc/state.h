/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STATE_H__
#define __STATE_H__


/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
typedef enum
{
    state_quick,
    state_slow,
    state_climb,
    state_open,
    state_look,
} STATE;
/* USER CODE END Private defines */
extern uint8_t openmv[7];
void state_machine();

/* USER CODE BEGIN Prototypes */
/* USER CODE END Prototypes */


#endif /* __USART_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
