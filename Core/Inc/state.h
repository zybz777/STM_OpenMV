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
void action_quick(void); //���ܲ�̬
void action_slow(void);  //���߲�̬
void action_climb(void); //��¥��̬
void action_stop(void);  //ֹͣ��̬
void action_open(void);  //���䶯��

void state_trans(void);
void state_machine(void);
/* USER CODE END Prototypes */

#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
