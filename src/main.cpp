#include "FIRSTPENGUIN.hpp"
#include "mbed.h"

constexpr uint32_t fp_can_id = 35;
constexpr int mech_can_id = 2;

int automatic = 0;

BufferedSerial pc(USBTX, USBRX, 115200);
CAN can(PA_11, PA_12, (int)1e6);
CANMessage msg;

FirstPenguin penguin(fp_can_id, can);
DigitalIn front_limit(PA_3, PullUp); // PA_3,PA_2,PA_10,PB_3
DigitalIn back_limit(PA_2, PullUp);
DigitalIn right_limit(PA_10, PullUp);
DigitalIn left_limit(PB_3, PullUp);

int main()
{
    while (true)
    {
        switch (automatic)
        {
        case 0:
            penguin.front_move();
            break;
        default:
            penguin.stop_move();
            break;
        }
        // CANMessage msg(mech_can_id,(const uint8_t *)mc.motor_pwm, 8);
        // can.write(msg);
    }
}