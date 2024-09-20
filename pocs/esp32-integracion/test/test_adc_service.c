#include "unity.h"

#include "adc_service.h"
#include "mock_adc.h"

#include "commons.h"



void test_adc_service_initialize(){

    adc_unit_t unit_x = ADC_UNIT_1;               
    esp_adc_cal_characteristics_t adc1_chars_x;

    adc_bits_width_t WIDTH = ADC_WIDTH_BIT_11;
    adc_channel_t channel_x =  ADC1_CHANNEL_6;
    adc_atten_t atten_x = ADC_ATTEN_DB_11;        

    adc_channel_t channel_y = ADC1_CHANNEL_7;      
    adc_atten_t atten_y = ADC_ATTEN_DB_11;        

    adc_channel_t channel = ADC_CHANNEL_0;      
    adc_atten_t atten = ADC_ATTEN_DB_11;        

    adc1_config_width_ExpectAndReturn(WIDTH , ESP_OK);
    adc1_config_channel_atten_ExpectAndReturn(channel_x,atten_x,ESP_OK);
    ESP_ERROR_CHECK_Expect(ESP_OK);
    esp_adc_cal_characterize_IgnoreAndReturn( ESP_OK);

    adc1_config_channel_atten_ExpectAndReturn(channel_y,atten_y,ESP_OK);
    ESP_ERROR_CHECK_Expect(ESP_OK);
    esp_adc_cal_characterize_IgnoreAndReturn( ESP_OK);

    adc1_config_channel_atten_ExpectAndReturn(channel,atten,ESP_OK);
    esp_adc_cal_characterize_IgnoreAndReturn( ESP_OK);
    adc_service_initialize();
}

void test_adc_service_joystick_read(){
    adc_channel_t channel_x =  ADC1_CHANNEL_6;      
    adc_channel_t channel_y =  ADC1_CHANNEL_7;      

    int adc_reading_x = 0;
    int adc_reading_y = 0;
    adc1_get_raw_ExpectAndReturn(channel_x , 1);
    adc1_get_raw_ExpectAndReturn(channel_y , 1);
    adc_service_joystick_read(&adc_reading_x,&adc_reading_y);
    TEST_ASSERT_EQUAL(adc_reading_x , 1);
    TEST_ASSERT_EQUAL(adc_reading_y , 1);

}

void test_adc_service_light_read(){
}
