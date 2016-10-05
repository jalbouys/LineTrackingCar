/*void readEncoders()
{
  wheelRotL = encL.read() - wheelRotL;
  if(wheelRotL > 512)//corrects 1023 to 0 error
    wheelRotL -= 1023;
  if(wheelRotL < -512)//corrects 0 to 1023 error
    wheelRotL += 1023;
    
  leftSpeedometer = 0.95*leftSpeedometer + (micros()-loopTime) * wheelRotL;

  
  loopTime = micros();
  Serial.println (encL.read (), DEC) ;
  Serial.println (encR.read (), DEC) ;
  
}*/

