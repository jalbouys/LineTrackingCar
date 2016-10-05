#include <string>
#include <sstream>
#include "Robot.h"
#include "serialib.h"

using namespace std;

Robot::Robot()
{
    int etat =  port.Open(SERIAL_PORT, SERIAL_BAUDRATE);
    cout << "etat: " << etat << endl;
    char c;
    while (port.Read(&c, 1) <= 0) {
        sleep(1);
    }
}

void Robot::sendOrder(float leftMotor, float rightMotor)
{
    int left = (int)(leftMotor*255);
    int right = (int)(rightMotor*255);

    ostringstream oss;
    oss << "set2 " << left << " " << right << "\r\n";

    port.WriteString(oss.str().c_str());
}

void Robot::sendBarycenter(char position){
    ostringstream oss;
    oss << position;

    port.WriteString(oss.str().c_str());
}
