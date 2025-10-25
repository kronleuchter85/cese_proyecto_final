#include "unity.h"

#include "joystick_service.h"
#include "mock_adc_service.h"
#include "commons.h"



void test_joystick_initialize(){

}

void test_joystick_get_reading_Neutral_Neutral(){

    int readx = 0, ready = 0;
    int x = 900, y = 900;

    adc_service_joystick_read_Expect(&readx , &readx);
    adc_service_joystick_read_ReturnThruPtr_adc_reading_x(&x);
    adc_service_joystick_read_ReturnThruPtr_adc_reading_y(&y);

    // joystick_transform(1 , 1);

    joystick_get_reading(&readx , &ready);
    TEST_ASSERT_EQUAL(JOYSTICK_READING_NEUTRAL , readx);
    TEST_ASSERT_EQUAL(JOYSTICK_READING_NEUTRAL , ready);

}


void test_joystick_get_reading_Max_Neutral(){

    int readx = 0, ready = 0;
    int x = 1800, y = 900;

    adc_service_joystick_read_Expect(&readx , &readx);
    adc_service_joystick_read_ReturnThruPtr_adc_reading_x(&x);
    adc_service_joystick_read_ReturnThruPtr_adc_reading_y(&y);

    // joystick_transform(1 , 1);

    joystick_get_reading(&readx , &ready);
    TEST_ASSERT_EQUAL(JOYSTICK_READING_MAX , readx);
    TEST_ASSERT_EQUAL(JOYSTICK_READING_NEUTRAL , ready);

}

void test_joystick_get_reading_Min_Neutral(){

    int readx = 0, ready = 0;
    int x = 0, y = 900;

    adc_service_joystick_read_Expect(&readx , &readx);
    adc_service_joystick_read_ReturnThruPtr_adc_reading_x(&x);
    adc_service_joystick_read_ReturnThruPtr_adc_reading_y(&y);

    // joystick_transform(1 , 1);

    joystick_get_reading(&readx , &ready);
    TEST_ASSERT_EQUAL(JOYSTICK_READING_MIN , readx);
    TEST_ASSERT_EQUAL(JOYSTICK_READING_NEUTRAL , ready);

}

void test_joystick_transform_2_0(){
    int  x = 2 , y = 0;
    joystick_transform(&x,&y);
    TEST_ASSERT_EQUAL(x , JOYSTICK_READING_MAX);
    TEST_ASSERT_EQUAL(y , JOYSTICK_READING_MIN);
}
void test_joystick_transform_1_0(){
    int  x = 1 , y = 0;
    joystick_transform(&x,&y);
    TEST_ASSERT_EQUAL(x , JOYSTICK_READING_NEUTRAL);
    TEST_ASSERT_EQUAL(y , JOYSTICK_READING_MIN);
}
void test_joystick_transform_0_0(){
    int  x = 0 , y = 0;
    joystick_transform(&x,&y);
    TEST_ASSERT_EQUAL(x , JOYSTICK_READING_MIN);
    TEST_ASSERT_EQUAL(y , JOYSTICK_READING_MIN);
}
void test_joystick_transform_0_1(){
    int  x = 0 , y = 1;
    joystick_transform(&x,&y);
    TEST_ASSERT_EQUAL(x , JOYSTICK_READING_MIN);
    TEST_ASSERT_EQUAL(y , JOYSTICK_READING_NEUTRAL);
}
void test_joystick_transform_0_2(){
    int  x = 0 , y = 2;
    joystick_transform(&x,&y);
    TEST_ASSERT_EQUAL(x , JOYSTICK_READING_MIN);
    TEST_ASSERT_EQUAL(y , JOYSTICK_READING_MAX);
}
