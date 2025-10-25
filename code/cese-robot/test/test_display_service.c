#include "unity.h"

#include "display_service.h"

#include "commons.h"
#include "mock_HD44780.h"
#include <stdio.h>
#include "stdlib.h"

void test_display_service_init(){
    LCD_init_Expect(DISPLAY_LCD_ADDR, DISPLAY_SDA_PIN, DISPLAY_SCL_PIN, DISPLAY_LCD_COLS, DISPLAY_LCD_ROWS);
    display_service_init();
}

void test_display_service_print(){
    char * first_line = "LINE 1";
    char * second_line = "LINE 2";

    LCD_clearScreen_Expect();
    LCD_home_Expect();
    LCD_setCursor_Expect(0,0);
    LCD_writeStr_Expect(first_line);
    LCD_setCursor_Expect(0,1);
    LCD_writeStr_Expect(second_line);
    display_service_print(first_line , second_line);
}
