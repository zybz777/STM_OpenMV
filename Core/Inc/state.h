/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STATE_H__
#define __STATE_H__

/* Includes ------------------------------------------------------------------*/

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
typedef enum
{
    state_1_begin,
    state_2_recognize_ball,
    state_3_green_user1,
    state_4_yellow_climb,
    state_5_red_downstairs,
    state_6_green_grass,
    state_7_brown_user3
} STATE;

/* 状态切换&&执行 */
void state_trans(void);
void state_machine(void);
/* USER CODE END Private defines */

/* USER CODE BEGIN Prototypes */
/* 动作函数 */
void action_quick(void); //快跑步态
void action_slow(void);  //慢走步态
void action_climb(void); //爬楼步态
void action_stop(void);  //停止步态
void action_open(void);  //开箱动作
void action_left(void);  //向左移动
void action_right(void); //向右移动
/* USER CODE END Prototypes */

#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
