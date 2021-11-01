#include "state.h"
#include "usart.h"
STATE state = state_slow; //当前状态，全局变量
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
void state_trans() //状态转移
{
	switch (COLOR)
	{
	case YELLOW:
		// 可能需要加个计数来过滤掉误判状态
		state = state_climb; //上台阶
		break;
	case BLUE:
		//从起点出发
		break;
	case RED:
		if (OPEN == 1)
		{
			state = state_open; //到达2号住户区，打开舱门
		}
		else
		{
			state = state_slow; //下斜坡
		}
		break;
	case GREEN:
		if (OPEN == 1)
		{
			state = state_open; //到达1号住户区，打开舱门
		}
		else
		{
			state = state_slow; //正常直行
		}
		break;
	case BROWN:
		if (OPEN == 1)
		{
			state = state_open; //到达3号住户区，打开舱门
		}
		else
		{
			state = state_slow; //正常直行
		}
		break;
	default:
		break;
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
	state_trans();
	//执行状态对应的动作
	switch (state)
	{
		static uint8_t flag_quick = 1;
		static uint8_t flag_slow = 1;
		static uint8_t flag_climb = 1;
		static uint8_t flag_open = 1;
		static uint8_t flag_look = 1;

	case state_quick:
		if (flag_quick)
		{
			action_quick();
			flag_quick = 0;
			flag_slow = 1;
			flag_climb = 1;
			flag_open = 1;
			flag_look = 1;
		}
		break;
	case state_slow:
		if (flag_slow)
		{
			action_slow();
			flag_quick = 1;
			flag_slow = 0;
			flag_climb = 1;
			flag_open = 1;
			flag_look = 1;
		}
		break;
	case state_climb:
		if (flag_climb)
		{
			action_climb();
			flag_quick = 1;
			flag_slow = 1;
			flag_climb = 0;
			flag_open = 1;
			flag_look = 1;
		}
		break;
	case state_open:
		if (flag_open)
		{
			action_open();
			action_stop();
			flag_climb = 1;
			flag_quick = 1;
			flag_slow = 1;
			flag_open = 0;
			flag_look = 1;
		}
		break;
	case state_look:
		if (flag_look)
		{
			action_stop();
			flag_quick = 1;
			flag_slow = 1;
			flag_climb = 1;
			flag_open = 1;
			flag_look = 0;
		}
		break;
	default:
		break;
	}
}
