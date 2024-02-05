
#ifndef ROBOT_POSITION_STATE2_H
#define ROBOT_POSITION_STATE2_H

typedef enum{

    MOVING_FORWARD,
    MOVING_BACKWARD,
    ROTATE_RIGHT,
    ROTATE_LEFT,
    REST

} robot_position_t;


robot_position_t robot_position_state_update(char * cmd);

robot_position_t robot_position_state_get();

#endif