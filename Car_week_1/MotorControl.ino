void updateSpeed(bool _motor, bool _direction, int _speed)
{
  int a,b;
  bool dir;
  if(_motor)//Left
  {
    a = LEFT_MOTOR_SPEED_PIN;
    b = LEFT_MOTOR_DIRECTION_PIN;
    
    if(_direction)//forward
      dir = 1;
    else
      dir = 0;
  } 
  else//Right
  {
    a = RIGHT_MOTOR_SPEED_PIN;
    b = RIGHT_MOTOR_DIRECTION_PIN;
    
    if(_direction)//forward
      dir = 1;
    else
      dir = 0;
  }

  if(_speed > 255)
    _speed = 255;
  else if(_speed < 0)
    _speed = 0;
  
  analogWrite(a, _speed);//speed
  digitalWrite(b, dir);//direction
}

void stopMotors()
{
  digitalWrite(LEFT_MOTOR_SPEED_PIN, 0);//speed
  digitalWrite(RIGHT_MOTOR_SPEED_PIN, 0);//speed
}
