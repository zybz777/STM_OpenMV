/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STATE_H__
#define __STATE_H__

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_hal.h"
#include "usart.h"
/* USER CODE BEGIN Private defines */
// 定义颜色
#define BLACK 0
#define BROWN 3
#define RED 2
#define GREEN 1
#define YELLOW 4
#define BLUE 5
// 定义串口接受的信息位
#define COLOR openmv[2]
#define DIRECTION openmv[3]
#define ANGLE openmv[4]
#define OPEN openmv[5]
#define BALL openmv[6]
typedef enum
{
    state_1_begin,
    state_2_recognize_ball,
    state_3_green_user1,
    state_4_yellow_climb,
    state_5_red_downstairs,
    state_6_green_grass,
    state_7_brown_user3, // 七个状态流转
    state_right,
    state_mid,
    state_left, // 三个状态控制左右位置
} STATE;

/* 状态切换&&执行 */
void state_trans(STATE st);
void state_direction_trans(void);
void state_machine(void);

/* USER CODE END Private defines */

/* USER CODE BEGIN Prototypes */
/* 动作函数 */

// 下层运动机构
void action_quick(void); //快跑步态
void action_slow(void);  //慢走步态
void action_climb(void); //爬楼步态
void action_stop(void);  //停止步态
void action_left(void);  //向左移动
void action_right(void); //向右移动

// 上层机构
void action_open(void); //开箱动作
/* USER CODE END Prototypes */

#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
