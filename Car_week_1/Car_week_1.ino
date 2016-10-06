#define LEFT_MOTOR_SPEED_PIN 9
#define RIGHT_MOTOR_SPEED_PIN 10
#define LEFT_MOTOR_DIRECTION_PIN 7
#define RIGHT_MOTOR_DIRECTION_PIN 8

#define CSpinL   2
#define CLKpinL  3
#define DOpinL   4
#define CSpinR   5
#define CLKpinR  6
#define DOpinR   11

#define LED_PIN 13


#define LEFT 1
#define RIGHT 0
#define FORWARD 1
#define BACK 0



#include <PID_v1.h>
#include <AS5040.h>//encoder

AS5040 encL (CLKpinL, CSpinL, DOpinL) ;
AS5040 encR (CLKpinR, CSpinR, DOpinR) ;

double centerPos = 50;
int offsetLR = 0;

double linePos = 50;//position of the line in front of robot
double pidCorrection = 0;//PID correction to set robot back on track
PID pidLR(&linePos, &pidCorrection, &centerPos, 2.5 ,0.15, 0.3, DIRECT);
//PID pidLR(&linePos, &pidCorrection, &centerPos, 1 , .5, .1, DIRECT);

float leftSpeed = 0, rightSpeed = 0;//desired motor speeds
float leftSpeedometer = 0, rightSpeedometer = 0;
int carSpeed = 95;
int wheelRotL = 0, wheelRotR = 0;
int speedCorrection = 0;

long loopTime;

int data = 0;

void setup()
{
  Serial.begin(115200);
  
  pinMode(LEFT_MOTOR_SPEED_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_SPEED_PIN, OUTPUT);
  pinMode(LEFT_MOTOR_DIRECTION_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_DIRECTION_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);//turn off LED
  delay(100);
  digitalWrite(LED_PIN, HIGH);//turn off LED
  delay(100);
  digitalWrite(LED_PIN, LOW);//turn off LED
  delay(100);
  digitalWrite(LED_PIN, HIGH);//turn off LED
  delay(100);
  digitalWrite(LED_PIN, LOW);//turn off LED
  delay(100);
  digitalWrite(LED_PIN, HIGH);//turn off LED
  delay(200);
  digitalWrite(LED_PIN, LOW);//turn off LED
  
 /* if (!encL.begin())
    digitalWrite(LED_PIN, HIGH);//turn on LED
  if (!encR.begin())
    digitalWrite(LED_PIN, HIGH);//turn on LED*/

  
  Serial.write('r');

  /*while(Serial.available() < 4)
    ;

  float p = Serial.read()/100.0;
  float i = Serial.read()/100.0;
  float d = Serial.read()/100.0;
  //carSpeed = Serial.read();
  carSpeed = Serial.read();
  Serial.println(p);
  Serial.println(i);
  Serial.println(d);
  Serial.println(carSpeed);
  
  pidLR.SetTunings(p, i, d);  
  Serial.flush();
  */
  pidLR.SetSampleTime(2);//10ms
  pidLR.SetOutputLimits(-50, 50);
  pidLR.SetMode(AUTOMATIC);
  
  
  //pidLR.SetTunings(p, i, d);
  
}

void loop()
{
  /*if(millis() > 10000)//10 seconds
    stopMotors();
  else
  {*/
    getData();//get data from Raspberry Pi
    pidCalc();
    updateSpeed(LEFT, FORWARD, leftSpeed);
    updateSpeed(RIGHT, FORWARD, rightSpeed);
  //}
}

void pidCalc()//compute PID correction and adjust left and right speeds
{
  pidLR.Compute();//compute PID output
  //pidCorrection = (linePos - centerPos)*1.0;
  leftSpeed = carSpeed + pidCorrection + offsetLR;
  rightSpeed = carSpeed - pidCorrection - offsetLR;
}
