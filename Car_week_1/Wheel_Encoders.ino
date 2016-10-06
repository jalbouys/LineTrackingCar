/*void readEncoders()
{
  wheelRotL = encL.read() - wheelRotL;
  if(wheelRotL > 512)//corrects 1023 to 0 error
    wheelRotL -= 1023;
  if(wheelRotL < -512)//corrects 0 to 1023 error
    wheelRotL += 1023;
    
  leftSpeedometer = 0.95*leftSpeedometer + (micros()-loopTime) * wheelRotL;

  
  wheelRotR = encL.read() - wheelRotR;
  if(wheelRotR > 512)//corrects 1023 to 0 error
    wheelRotR -= 1023;
  if(wheelRotR < -512)//corrects 0 to 1023 error
    wheelRotR += 1023;
    
  rightSpeedometer = 0.95*rightSpeedometer + (micros()-loopTime) * wheelRotR;

  
  loopTime = micros();
  Serial.println (encL.read (), DEC) ;
  Serial.println (encR.read (), DEC) ;
  
}*/

