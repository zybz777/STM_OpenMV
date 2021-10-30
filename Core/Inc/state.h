/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STATE_H__
#define __STATE_H__

/* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
#define BLACK 0
#define BROWN 3
#define RED 2
#define GREEN 1
#define YELLOW 4
#define BLUE 5

typedef enum
{
    state_quick,
    state_slow,
    state_climb,
    state_open,
    state_look,
} STATE;
/* USER CODE END Private defines */

/* USER CODE BEGIN Prototypes */
void action_quick(void); //快跑步态
void action_slow(void);  //慢走步态
void action_climb(void); //爬楼步态
void action_stop(void);  //停止步态
void action_open(void);  //开箱动作

void state_trans(void);
void state_machine(void);
/* USER CODE END Prototypes */

#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
