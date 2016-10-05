#ifndef _ROBOT_H
#define _ROBOT_H

#include "serialib.h"

#define SERIAL_PORT     "/dev/ttyUSB0"
#define SERIAL_BAUDRATE 9600

class Robot
{
    public:
        Robot();

        void sendOrder(float leftMotor, float rightMotor);
        void sendBarycenter(char position);
        void sendPID(char p, char i, char d);
    protected:
        serialib port;
};

#endif
