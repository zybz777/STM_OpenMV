
#include "state.h"
#include "usart.h"
#include <stdio.h>
STATE state = state_slow;//��ǰ״̬��ȫ�ֱ���



//openmv[7] = {0x2c, 7, color&distance,  way_direction, angle, ball, 0x5B}

//color&distance: 0,1,2,3,4,5,6
//way_direction: -1,0,1
//angle: 0~180
//open: 0,1


void action_quick()//���ܲ�̬
{
    printf("action_quick\r\n");

}

void action_slow()//���߲�̬
{
    printf("action_slow\r\n");
}

void action_climb()//��¥��̬
{
    printf("action_climb\r\n");
}

void action_stop()//ֹͣ��̬
{
    printf("action_stop\r\n");
}

void action_open()//���䶯��
{
    printf("action_open\r\n");
}

/*
void trans(STATE st)//״̬ת��
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
	
	//�жϵ�ǰ״̬��
	//openmv[7] = {0x2c, 7, color&distance,  way_direction, angle, open, 0x5B}
//color&distance: 0,1,2,3,4,5,6
//way_direction: -1,0,1
//angle: 0~180
//open: 0,1
	  if(openmv[2]==YELLOW){//��̨��
			state=state_climb;
		}
		else if(openmv[2]==BLUE){//��������
			//state=state_slow;
		}
		else if((openmv[2]==RED)&&(openmv[5]==0)){//��б��
			state=state_slow;
		}
		else if((openmv[2]==GREEN)&&(openmv[5]==0)){//���ݵ�
			state=state_slow;
		}
		else if((openmv[2]==GREEN)&&(openmv[5]==1)){//����1��ס����
			state=state_open;
		}
		else if((openmv[2]==RED)&&(openmv[5]==1)){//����2��ס����
			state=state_open;
		}
		else if((openmv[2]==BROWN)&&(openmv[5]==1)){//����3��ס����
			state=state_open;
		}
	
	//ִ��״̬��Ӧ�Ķ���
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
