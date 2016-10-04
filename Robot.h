#ifndef _ROBOT_H
#define _ROBOT_H

#include "serialib.h"

#define SERIAL_PORT     "/dev/ttyUSB0"
#define SERIAL_BAUDRATE 500000

class Robot
{
    public:
        Robot();

        void sendOrder(float leftMotor, float rightMotor);

    protected:
        serialib port;
};

#endif
