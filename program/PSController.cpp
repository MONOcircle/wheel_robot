#include "mbed.h"
#include "PS_PAD.h"

Serial pc(PA_2, PA_3);
PS_PAD vsc3(PA_7, PA_6, PA_5, PA_4); 

float r_y = 0,l_y = 0;
int start_signal =0;

int main() {
    vsc3.init();
    while(1) {
        vsc3.poll();
        if(vsc3.read(PS_PAD::PAD_START) == 1)start_signal = 1; 
        if(start_signal == 1){
        r_y = vsc3.read(PS_PAD::ANALOG_RY);
        l_y = vsc3.read(PS_PAD::ANALOG_LY);
        }
        wait(0.05);
    pc.printf("%f %f\n",r_y,l_y);
    }
}
