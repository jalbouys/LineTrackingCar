#ifndef _ROBOT_H
#define _ROBOT_H

#include "serialib.h"

#define SERIAL_PORT     "/dev/ttyUSB2"
#define SERIAL_BAUDRATE 9600

class Robot
{
    public:
        Robot();

        void sendOrder(float leftMotor, float rightMotor);
        void sendBarycenter(char position);
    protected:
        serialib port;
};

#endif
