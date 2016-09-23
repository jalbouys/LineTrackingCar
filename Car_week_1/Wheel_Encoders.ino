/*void readEncoders()
{
  int wheelPosL = encL.read() - wheelPosL;
  if(wheelPosL>511)//corrects 512 to 0 error
    wheelPosL -= 512;
    
  leftSpeedometer = 0.95*leftSpeedometer + (micros()-loopTime) * wheelPosL;
  loopTime = micros();
  Serial.println (encL.read (), DEC) ;
  Serial.println (encR.read (), DEC) ;
  
}*/

