#include "mbed.h"

PwmOut m1_cw(PA_11);
PwmOut m1_ccw(PA_8);
PwmOut m2_cw(PB_4);
PwmOut m2_ccw(PB_5);

int main() {
    while(1) {
         //右車輪
         m1_cw  = 1;// 0~1(プログラム数値) ＝ 0V~3.3V(マイコン電圧) = 0V~6V(モータ電圧)
         m1_ccw = 0;
         //左車輪
         m2_cw  = 1;//
         m2_ccw = 0;
         
         //pc.printf("%f\n",psd_sensor);
    }
}
