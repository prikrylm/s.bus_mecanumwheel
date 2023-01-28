#ifndef SBUS2H2_h
#define SBUS2H2_h


#include <Arduino.h>

#define USB_MIN 172
#define USB_MID 996
#define USB_MAX 1810
#define USB_TRE 10 // 10 frfniku na kazdou stranu bude nula

#define H2_MAX 254
#define H2_TRE 60

class ChToH2
{

private:
    int ma;
    int mb;
    int mot1pin;
    int mot2pin;

    float kDown;
    float kUp;

    void _init(int motApin, int motBpin);

public:
    // hw piny pro ovladani motoru pres H mustek
    // jeden je 0 druhy pwm
    // pro opacny smer si vymeni role
    ChToH2(int motApin, int motBpin) {_init(motApin, motBpin);};
    void setH2(int inValue);
#ifdef dbg    
    int getMa();
    int getMb();
    float getKUp();
    float getKDn();
#endif
};

#endif
