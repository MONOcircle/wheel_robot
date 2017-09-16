#include "mbed.h"
#include "TextLCD.h"

AnalogIn left(PA_0);
AnalogIn center(PA_1);

TextLCD g_lcd(PF_1, PF_0, PB_3, PA_10, PA_12, PA_9);// RS, E, DB4, DB5, DB6, DB7

float line_center,line_left;
double left_trace,center_trace;

int main() {
    while(1) {
        left_trace = left;
        center_trace = center;
        wait(0.001);
        g_lcd.cls();wait(0.001);
        g_lcd.locate(0, 1);
        g_lcd.printf( "%.2f %.2f",center_trace,left_trace);
        wait(0.1);
    }
}