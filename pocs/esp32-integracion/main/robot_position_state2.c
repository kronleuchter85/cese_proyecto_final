
#include "robot_position_state2.h"
#include <stdio.h>
#include <string.h>

robot_position_t position_state;

robot_position_t robot_position_state_update(char * cmd){

    if(!strcmp(cmd ,"MOVING_BACKWARD")){
        position_state = MOVING_BACKWARD;
    }else if( !strcmp(cmd ,"MOVING_FORWARD")){
        position_state = MOVING_FORWARD;
    }else if(!strcmp(cmd ,"ROTATE_RIGHT")){
        position_state = ROTATE_RIGHT;
    }else if(!strcmp(cmd ,"ROTATE_LEFT")){
        position_state = ROTATE_LEFT;
    }else{
        position_state = REST;
    }

    return position_state;
}

robot_position_t robot_position_state_get(){
    return position_state;
}