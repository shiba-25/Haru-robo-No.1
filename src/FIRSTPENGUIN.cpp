#include "FIRSTPENGUIN.hpp"

bool FirstPenguin::send()
{
    return can.write(CANMessage{send_id, reinterpret_cast<const uint8_t *>(pwm), 8});
}

void FirstPenguin::read(const CANMessage &msg)
{
    if (msg.format == CANStandard && msg.type == CANData && msg.len == sizeof(receive[0]) && send_id < msg.id && msg.id <= send_id + 5)
    {
        receive[msg.id - send_id - 1].set(msg.data);
    }
}

void FirstPenguin::front_move()
{
    int wheel_motor[4] = {-1, -1, 1, 1};
    for (int i = 0; i < 4; i++)
    {
        pwm[i] = wheel_power * wheel_motor[i];
    }
    printf("success");
    send();
}

void FirstPenguin::back_move()
{
    int wheel_motor[4] = {1, 1, -1, -1};
    for (int i = 0; i < 4; i++)
    {
        pwm[i] = wheel_power * wheel_motor[i];
    }
    send();
}

void FirstPenguin::right_move()
{
    int wheel_motor[4] = {-1, 1, 1, -1};
    for (int i = 0; i < 4; i++)
    {
        pwm[i] = wheel_power * wheel_motor[i];
    }
    send();
}

void FirstPenguin::left_move()
{
    int wheel_motor[4] = {1, -1, -1, 1};
    for (int i = 0; i < 4; i++)
    {
        pwm[i] = wheel_power * wheel_motor[i];
    }
    send();
}

void FirstPenguin::stop_move()
{
    for (int i = 0; i < 4; i++)
    {
        pwm[i] = 0;
    }
    send();
}