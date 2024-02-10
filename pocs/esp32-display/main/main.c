/*
* Del tutorial: https://esp32tutorials.com/i2c-lcd-esp32-esp-idf/
*
*/

#include <driver/i2c.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdio.h>
#include "sdkconfig.h"
#include "HD44780.h"

#define DISPLAY_SDA_PIN  21
#define DISPLAY_SCL_PIN  22

#define DISPLAY_LCD_ADDR 0x27
#define DISPLAY_LCD_COLS 16
#define DISPLAY_LCD_ROWS 2

static void LCD_DemoTask(void* param){

    LCD_init(DISPLAY_LCD_ADDR, DISPLAY_SDA_PIN, DISPLAY_SCL_PIN, DISPLAY_LCD_COLS, DISPLAY_LCD_ROWS);

    char num[20];
    while (true) {
        LCD_home();
        LCD_clearScreen();
        LCD_writeStr("16x2 I2C LCD");
        vTaskDelay(3000 / portTICK_RATE_MS);
        LCD_clearScreen();
        LCD_setCursor(0,0);
        LCD_writeStr("Lets Count 0-10!");
        vTaskDelay(3000 / portTICK_RATE_MS);
        LCD_clearScreen();
        for (int i = 0; i <= 10; i++) {

            LCD_home();
            LCD_setCursor(0, 0);
            sprintf(num, "T: %.1f C", 23.5);
            LCD_writeStr(num);
            
            LCD_setCursor(8, 0);
            sprintf(num, "H: %d %%", 30);
            LCD_writeStr(num);
            
            LCD_setCursor(0, 1);
            sprintf(num, "P: %.1f hP", 23.5);
            LCD_writeStr(num);
            
            LCD_setCursor(8, 1);
            sprintf(num, "L: %d %%", 30);
            LCD_writeStr(num);
            
            vTaskDelay(1000 / portTICK_RATE_MS);
        }
    }
}

void app_main(void){
    
    xTaskCreate(LCD_DemoTask, "Demo Task", 2048, NULL, 5, NULL);
    
}

