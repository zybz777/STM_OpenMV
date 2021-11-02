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

/*
void trans(STATE st)//状态转移
{
    int state_wrong = 0;
    if(st == state1 && state != state4)
    {
        state_wrong = 1;
    }
    if(st == state2 && state != state1)
    {
        state_wrong = 1;
    }
    if(st == state3 && state != state2)
    {
        state_wrong = 1;
    }
    if(st == state4 && state != state3)
    {
        state_wrong = 1;
    }
    else
    {
        state = st;
    }
    
    if(state_wrong == 1)
    {
        return;
    }
}
*/
void state_trans(STATE st) //状态转移
{
	if (state == state_1_begin && st == state_2_recognize_ball)
	{
		if (COLOR == BLUE)
		{
			state = st;
		}
	}
	else if (state == state_2_recognize_ball && st == state_3_green_user1)
	{
		if (COLOR == GREEN)
		{
			state = st;
		}
	}
	else if (state == state_3_green_user1 && st == state_4_yellow_climb)
	{
		if (COLOR == YELLOW)
		{
			state = st;
		}
	}
	else if (state == state_4_yellow_climb && st == state_5_red_downstairs)
	{
		if (COLOR == RED)
		{
			state = st;
		}
	}
	else if (state == state_5_red_downstairs && st == state_6_green_grass)
	{
		if (COLOR == GREEN)
		{
			state = st;
		}
	}
	else if (state == state_6_green_grass && st == state_7_brown_user3)
	{
		if (COLOR == BROWN)
		{
			state = st;
		}
	}
	else if (state == state_7_brown_user3 && st == state_1_begin)
	{
		state = st;
	}
}

void state_machine()
{

	//判断当前状态：
	//openmv[7] = {0x2c, 7, color&distance,  way_direction, angle, open, 0x5B}
	//color&distance: 0,1,2,3,4,5,6
	//way_direction: -1,0,1
	//angle: 0~180
	//open: 0,1
	// 状态切换
	// state_trans();
	//执行状态对应的动作
	switch (state)
	{
	}
}
