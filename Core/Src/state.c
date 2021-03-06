#include "state.h"
#include "tim.h"
STATE state = state_1_begin;	   // 当前状态，全局变量
STATE state_direction = state_mid; // 控制左右平衡
/*
openmv[7] = {0x2c, 7, color&distance,  way_direction, angle, ball, 0x5B}
color&distance: 0,1,2,3,4,5,6
way_direction: -1,0,1
angle: 0~180
open: 0,1
*/

/***** 动作函数 *****/
void action_quick() //快跑步态
{
	//printf("action_quick\r\n");
}

void action_slow() //慢走步态
{
	//printf("action_slow\r\n");
}

void action_climb() //爬楼步态
{
	//printf("action_climb\r\n");
}

void action_left(void) //向左移动
{
	//printf("action_left\r\n");
}

void action_right(void) //向右移动
{
	//printf("action_right\r\n");
}

void action_stop() //停止步态
{
	//printf("action_stop\r\n");
}

void action_open() //开箱动作
{
	//printf("action_open\r\n");
	// pwm 打开舵机
	// 延时
	// pwm 关闭舵机
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 900);
	HAL_Delay(2000);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 2000);
	HAL_Delay(2000);
}

/***** 状态切换 *****/
void state_trans(STATE st)
{
	switch (st)
	{
	case state_2_recognize_ball:
		if (state == state_1_begin && COLOR == BLUE)
		{
			state = st;
		}
		break;

	case state_3_green_user1:
		if (state == state_2_recognize_ball && COLOR == GREEN)
		{
			state = st;
		}
		break;

	case state_4_yellow_climb:
		if (state == state_3_green_user1 && COLOR == YELLOW)
		{
			state = st;
		}
		break;

	case state_5_red_downstairs:
		if (state == state_4_yellow_climb && COLOR == RED)
		{
			state = st;
		}
		break;

	case state_6_green_grass:
		if (state == state_5_red_downstairs && COLOR == GREEN)
		{
			state = st;
		}
		break;

	case state_7_brown_user3:
		if (state == state_6_green_grass && COLOR == BROWN)
		{
			state = st;
		}
		break;

	case state_1_begin:
		if (state == state_7_brown_user3)
		{
			state = st;
		}
		break;
	default:
		break;
	}
}
// 方向状态切换
void state_direction_trans(void)
{
	// if (DIRECTION == 0) // 正向
	// {
	// 	state_direction = state_mid;
	// }
	// else if (DIRECTION == 1) // 现在方向偏左，需要向右调整
	// {
	// 	state_direction = state_left;
	// }
	// else if (DIRECTION == -1)
	// {
	// 	state_direction = state_right;
	// }
}
/***** 状态执行 *****/
void state_machine()
{
	static uint8_t flag_state2 = 0; // 用来控制执行次数
	static uint32_t count_state4 = 0;
	// 赛道进程
	switch (state)
	{
	case state_1_begin:
		// 执行动作
		action_slow(); // 慢步前进
		// 状态转移，走到蓝色前切换
		state_trans(state_2_recognize_ball);
		printf("now is state 1\r\n");
		break;

	case state_2_recognize_ball:
		// 执行动作
		if (BALL == 1)
		{
			flag_state2 = 1;
		}

		if (flag_state2 == 0)
		{
			action_stop();
		}
		else
		{
			// HAL_Delay(3000); // 等待3s
			action_slow(); // 开始前进
		}
		// 状态转移
		printf("now is state 2\r\n");
		state_trans(state_3_green_user1);
		break;

	case state_3_green_user1:
		// 执行动作
		if (OPEN == 1)
		{
			action_stop(); // 停下来判断
			action_open(); // 找到正确用户，开舱门
						   // 在 atcion open中加延时使其不会在球还没出去的时候狗子就跑
		}
		else
		{
			action_slow(); // 继续前进
		}
		// 状态转移
		printf("now is state 3\r\n");
		state_trans(state_4_yellow_climb);
		break;

	case state_4_yellow_climb:
		// 执行动作
		if (count_state4 < 20000) // 停下来缓冲一下
		{
			action_stop();
			count_state4++;
		}
		else if (count_state4 < 40000) // 此次动作是上楼梯，40000还需再改
		{
			action_climb();
			count_state4++;
		}
		else // 此次动作是切换为慢速过窄桥
		{
			action_slow();
		}
		// 状态转移
		printf("now is state 4\r\n");
		state_trans(state_5_red_downstairs);
		break;

	case state_5_red_downstairs:
		// 执行动作
		if (OPEN == 1)
		{
			action_stop(); // 停下来判断
			action_open(); // 找到正确用户，开舱门
						   // 在 atcion open中加延时使其不会在球还没出去的时候狗子就跑
		}
		else
		{
			action_slow(); // 继续前进
		}
		// 状态转移
		state_trans(state_6_green_grass);
		break;

	case state_6_green_grass:
		// 执行动作
		action_slow(); // 继续前进
		// 状态转移
		state_trans(state_7_brown_user3);
		break;

	case state_7_brown_user3:
		// 执行动作
		if (OPEN == 1)
		{
			action_stop(); // 停下来判断
			action_open(); // 找到正确用户，开舱门
						   // 在 atcion open中加延时使其不会在球还没出去的时候狗子就跑
		}
		else
		{
			action_slow(); // 继续前进
		}
		// 状态转移
		state_trans(state_1_begin);
		break;

	default:
		break;
	}
	// 方向进程
	/*
	switch (state_direction)
	{
		// case state_mid:
		// 	// 状态转移
		// 	state_direction_trans();
		// 	break;
		// case state_right:
		// 	// 向左调整
		// 	action_left();
		// 	// 状态转移
		// 	state_direction_trans();
		// 	break;
		// case state_left:
		// 	// 向右调整
		// 	action_right();
		// 	// 状态转移
		// 	state_direction_trans();
		// 	break;
		// default:
		// 	break;
	}
	*/
}
