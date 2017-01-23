#include "mbed.h"
#include "TextLCD.h"

TextLCD g_lcd(PF_1, PF_0, PB_3, PA_10, PA_12, PA_9);  // RS, E, DB4, DB5, DB6, DB7

int main() {

    while(1) {
        
        g_lcd.locate(0, 1);
        g_lcd.printf( "hello");
    }
}