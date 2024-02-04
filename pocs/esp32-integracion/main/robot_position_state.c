
#include "joystick_service.h"
#include "robot_position_state.h"

robot_position_t position_state;

robot_position_t robot_position_state_update(float command_x , float command_y){

    if(command_x == JOYSTICK_READING_MAX && command_y == JOYSTICK_READING_NEUTRAL){
        position_state = MOVING_BACKWARD;
    }else if( command_x == JOYSTICK_READING_MIN && command_y == JOYSTICK_READING_NEUTRAL){
        position_state = MOVING_FORWARD;
    }else if(command_x == JOYSTICK_READING_NEUTRAL && command_y == JOYSTICK_READING_MAX){
        position_state = ROTATE_RIGHT;
    }else if(command_x == JOYSTICK_READING_NEUTRAL && command_y == JOYSTICK_READING_MIN){
        position_state = ROTATE_LEFT;
    }else{
        position_state = REST;
    }

    return position_state;
}

robot_position_t robot_position_state_get(){
    return position_state;
}