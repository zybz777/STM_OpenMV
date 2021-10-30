
#include "state.h"
#include "usart.h"
#include <stdio.h>
STATE state = state_slow;//当前状态，全局变量



//openmv[7] = {0x2c, 7, color&distance,  way_direction, angle, ball, 0x5B}

//color&distance: 0,1,2,3,4,5,6
//way_direction: -1,0,1
//angle: 0~180
//open: 0,1


void action_quick()//快跑步态
{
    printf("action_quick\r\n");

}

void action_slow()//慢走步态
{
    printf("action_slow\r\n");
}

void action_climb()//爬楼步态
{
    printf("action_climb\r\n");
}

void action_stop()//停止步态
{
    printf("action_stop\r\n");
}

void action_open()//开箱动作
{
    printf("action_open\r\n");
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

void state_machine()
{
	
	//判断当前状态：
	//openmv[7] = {0x2c, 7, color&distance,  way_direction, angle, open, 0x5B}
//color&distance: 0,1,2,3,4,5,6
//way_direction: -1,0,1
//angle: 0~180
//open: 0,1
	  if(openmv[2]==YELLOW){//上台阶
			state=state_climb;
		}
		else if(openmv[2]==BLUE){//从起点出发
			//state=state_slow;
		}
		else if((openmv[2]==RED)&&(openmv[5]==0)){//下斜坡
			state=state_slow;
		}
		else if((openmv[2]==GREEN)&&(openmv[5]==0)){//进草地
			state=state_slow;
		}
		else if((openmv[2]==GREEN)&&(openmv[5]==1)){//到达1号住户区
			state=state_open;
		}
		else if((openmv[2]==RED)&&(openmv[5]==1)){//到达2号住户区
			state=state_open;
		}
		else if((openmv[2]==BROWN)&&(openmv[5]==1)){//到达3号住户区
			state=state_open;
		}
	
	//执行状态对应的动作
    switch(state)
    {
			  int flag_quick=1;
			  int flag_slow=1;
			  int flag_climb=1;
			  int flag_open=1;
			  int flag_look=1;
			
        case state_quick:
					if(flag_quick){
						action_quick();
				    flag_quick=0;
						flag_slow=1;
			      flag_climb=1;
			      flag_open=1;
			      flag_look=1;
					}
            break;
        case state_slow:
					if(flag_slow){
						action_slow();
				    flag_slow=0;
						flag_quick=1;
						flag_climb=1;
						flag_open=1;
						flag_look=1;
						
					}
            
            break;
        case state_climb:
					if(flag_climb){
						action_climb();
				    flag_climb=0;
						flag_quick=1;
						flag_slow=1;
						flag_open=1;
						flag_look=1;
					}
            
            break;
				case state_open:
					if(flag_open){
						action_open();
				    action_stop();
				    flag_open=0;
						flag_climb=1;
						flag_quick=1;
						flag_slow=1;
						flag_look=1;
					}
            
            break;
				case state_look:
					if(flag_look){
						action_stop();
				    flag_look=0;
						flag_quick=1;
						flag_slow=1;
			      flag_climb=1;
			      flag_open=1;
					}
            break;
        default:
            break;
    }
}
