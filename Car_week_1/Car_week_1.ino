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

  while(Serial.available() < 4)
    ;

  float p = Serial.read()/100.0;
  float i = Serial.read()/100.0;
  float d = Serial.read()/100.0;
  carSpeed = Serial.read();
  Serial.println(p);
  Serial.println(i);
  Serial.println(d);
  Serial.println(carSpeed);
  
  pidLR.SetTunings(p, i, d);
  
  Serial.flush();
  
  pidLR.SetSampleTime(70);//10ms
  pidLR.SetOutputLimits(-100, 100);
  pidLR.SetMode(AUTOMATIC);
  
  pidLR.SetTunings(p, i, d);
  
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
  leftSpeed = carSpeed + pidCorrection + offsetLR + speedCorrection;
  rightSpeed = carSpeed - pidCorrection - offsetLR - speedCorrection;
}
