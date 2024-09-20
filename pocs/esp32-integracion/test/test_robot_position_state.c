#include "unity.h"

#include "robot_position_state.h"
#include "joystick_service.h"
#include "mock_adc_service.h"
#include "commons.h"



void test_robot_position_state_get_action_by_name_MOVING_BACKWARD(){
    robot_position_t position = robot_position_state_get_action_by_name("MOVING_BACKWARD");
    TEST_ASSERT_EQUAL(position,MOVING_BACKWARD);
}
void test_robot_position_state_get_action_by_name_MOVING_FORWARD(){
    robot_position_t position = robot_position_state_get_action_by_name("MOVING_FORWARD");
    TEST_ASSERT_EQUAL(position,MOVING_FORWARD);
}
void test_robot_position_state_get_action_by_name_ROTATE_LEFT(){
    robot_position_t position = robot_position_state_get_action_by_name("ROTATE_LEFT");
    TEST_ASSERT_EQUAL(position,ROTATE_LEFT);
}
void test_robot_position_state_get_action_by_name_ROTATE_RIGHT(){
    robot_position_t position = robot_position_state_get_action_by_name("ROTATE_RIGHT");
    TEST_ASSERT_EQUAL(position,ROTATE_RIGHT);
}
void test_robot_position_state_get_action_by_name_REST(){
    robot_position_t position = robot_position_state_get_action_by_name("REST");
    TEST_ASSERT_EQUAL(position,REST);
}

void test_robot_position_state_get_action_by_coordinates_MOVING_BACKWARD(){
    robot_position_t action = robot_position_state_get_action_by_coordinates(JOYSTICK_READING_MAX , JOYSTICK_READING_NEUTRAL);
    TEST_ASSERT_EQUAL(action,MOVING_BACKWARD);
}
void test_robot_position_state_get_action_by_coordinates_MOVING_FORWARD(){
    robot_position_t action = robot_position_state_get_action_by_coordinates(JOYSTICK_READING_MIN , JOYSTICK_READING_NEUTRAL);
    TEST_ASSERT_EQUAL(action,MOVING_FORWARD);
}
void test_robot_position_state_get_action_by_coordinates_ROTATE_LEFT(){
    robot_position_t action = robot_position_state_get_action_by_coordinates(JOYSTICK_READING_NEUTRAL , JOYSTICK_READING_MAX);
    TEST_ASSERT_EQUAL(action,ROTATE_LEFT);
}
void test_robot_position_state_get_action_by_coordinates_ROTATE_RIGHT(){
    robot_position_t action = robot_position_state_get_action_by_coordinates(JOYSTICK_READING_NEUTRAL , JOYSTICK_READING_MIN);
    TEST_ASSERT_EQUAL(action,ROTATE_RIGHT);
}
void test_robot_position_state_get_action_by_coordinates_REST(){
    robot_position_t action = robot_position_state_get_action_by_coordinates(123 , 234);
    TEST_ASSERT_EQUAL(action,REST);
}
