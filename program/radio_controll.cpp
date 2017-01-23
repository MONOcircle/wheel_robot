#include "mbed.h"
#include "PS_PAD.h"
#include "TextLCD.h"

#define CON 128

Serial pc(PA_2, PA_3);
//------------------------------------
// Hyperterminal configuration
// 9600 bauds, 8-bit data, no parity
//------------------------------------

PS_PAD vsc3(PA_7, PA_6, PA_5, PA_4); 

PwmOut m1_cw(PA_11);
PwmOut m1_ccw(PA_8);
PwmOut m2_cw(PB_4);
PwmOut m2_ccw(PB_5);

AnalogIn left(PA_0);
AnalogIn center(PA_1);
AnalogIn right(PB_1);
AnalogIn psd(PB_0);

Ticker flipper;
Ticker flipper2;

TextLCD g_lcd(PF_1, PF_0, PB_3, PA_10, PA_12, PA_9);  // RS, E, DB4, DB5, DB6, DB7

float r_y = 0,l_y = 0;
float line_right,line_center,line_left;
double psd_sensor;
int start_signal =0;

//コントローラ割り込み関数
void flip() {
    vsc3.poll();
        if(vsc3.read(PS_PAD::PAD_START) == 1)start_signal = 1; 
        if(start_signal == 1){
        r_y = vsc3.read(PS_PAD::ANALOG_RY);
        l_y = vsc3.read(PS_PAD::ANALOG_LY);
        }
}

void flip2() {
        g_lcd.locate(0, 1);
        g_lcd.printf( "%8.3f", psd_sensor );
        g_lcd.locate(1, 0);
        g_lcd.printf( "PSD SENSOR");
}

int main() {
    vsc3.init();
    wait(0.001);
    g_lcd.cls(); wait(0.001);
    flipper.attach(&flip, 0.05);
    flipper2.attach(&flip2, 0.1);
    while(1) {
        
        psd_sensor = psd;
        
        //右車輪
        if(r_y < 0 && psd_sensor < 0.52){  
            m1_cw  = fabsf(r_y/CON);
            m1_ccw = 0;
        }
        else if(r_y >0){
            m1_cw  = 0;
            m1_ccw = r_y/CON;
        }
        else{//ブレーキモード
            m1_cw   = 1;
            m1_ccw  = 1;
        }
        
        //左車輪
        if(l_y < 0 && psd_sensor < 0.52){
            m2_cw  = fabsf(l_y/CON);
            m2_ccw = 0;
        }
        else if(l_y >0){
            m2_cw  = 0;
            m2_ccw = l_y/CON;
        }
        else{//ブレーキモード
            m2_cw   = 1;
            m2_ccw  = 1;
        }
        
        //デバッグ用
        //line_right = right;
        //line_center = center;
        //line_left = left;
        //psd_sensor = psd;
        //pc.printf("%f %f %d\n",r_y,l_y,start_signal);
        //pc.printf("%f %f %f\n",line_right,line_center,line_left);
        //pc.printf("%f\n",psd_sensor);
    }
}
