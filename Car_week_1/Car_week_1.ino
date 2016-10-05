#define LEFT_MOTOR_SPEED_PIN 9
#define RIGHT_MOTOR_SPEED_PIN 10
#define LEFT_MOTOR_DIRECTION_PIN 7
#define RIGHT_MOTOR_DIRECTION_PIN 8
#define LED_PIN 13

#define LEFT 1
#define RIGHT 0
#define FORWARD 1
#define BACK 0

#include <PID_v1.h>

double centerPos = 50;

double linePos;//position of the red line in front of robot
double pidCorrection;//PID correction to set robot back on track
PID pidLR(&linePos, &pidCorrection, &centerPos, .75 , 1.0, .075, DIRECT);

float leftSpeed, rightSpeed;//desired motor speeds
float carSpeed = 200;

long loopTime;

void setup()
{
  Serial.begin(9600);    // start sending data to Xbee
  pinMode(LEFT_MOTOR_SPEED_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_SPEED_PIN, OUTPUT);
  pinMode(LEFT_MOTOR_DIRECTION_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_DIRECTION_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  pidLR.SetSampleTime(10);
  pidLR.SetOutputLimits(-20, 20);
  pidLR.SetMode(AUTOMATIC);
}

void loop()
{
  loopTime = micros();
  getData();//get data from Raspberry Pi
  //stopMotors();
  //pidCalc();
  
}

void pidCalc()//compute PID correction and adjust left and right speeds
{
  pidLR.Compute();//compute PID output
  leftSpeed = carSpeed + pidCorrection;
  rightSpeed = carSpeed - pidCorrection;
}
