#include "state.h"
#include "usart.h"
STATE state = state_1_begin; //当前状态，全局变量
/*
openmv[7] = {0x2c, 7, color&distance,  way_direction, angle, ball, 0x5B}
color&distance: 0,1,2,3,4,5,6
way_direction: -1,0,1
angle: 0~180
open: 0,1
*/
void action_quick() //快跑步态
{
	printf("action_quick\r\n");
}

void action_slow() //慢走步态
{
	printf("action_slow\r\n");
}

void action_climb() //爬楼步态
{
	printf("action_climb\r\n");
}

void action_left(void) //向左移动
{
	printf("action_left\r\n");
}

void action_right(void) //向右移动
{
	printf("action_right\r\n");
}

void action_stop() //停止步态
{
	printf("action_stop\r\n");
}

void action_open() //开箱动作
{
	printf("action_open\r\n");
	// pwm 打开舵机
	// 延时
	// pwm 关闭舵机
}

void state_trans(STATE st) //状态转移
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

void state_machine()
{
	switch (state)
	{
	case state_1_begin:
		// 执行动作
		action_slow(); // 慢步前进
		// 状态转移
		state_trans(state_2_recognize_ball);
		break;

	case state_2_recognize_ball:
		static uint8_t flag_state2 = 0; // 用来控制执行次数
		int ball;
		// 执行动作
		if (ball == 1)
		{
			flag_state2 = 1;
		}

		if (flag_state2 == 0)
		{
			action_stop();
		}
		else
		{
			action_slow(); // 开始前进
		}
		// 状态转移
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
		state_trans(state_4_yellow_climb);
		break;

	case state_4_yellow_climb:
		// 执行动作
		static uint32_t count_state4 = 0;
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
}
