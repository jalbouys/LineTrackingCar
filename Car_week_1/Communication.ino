void getData()//get data from Raspberry Pi
{
  if (Serial.available()) // if received 255, stopMotors
  {
    char data_in = Serial.read();
    if(data_in == 0)//not Position command
    {
      //linePos = 100 - linePos; 
    }
    else if(data_in == 255){
      stopMotors();
      while(1){  
      }
    }
    else
    {
      linePos = data_in;
      if ((linePos >= 48)  && (linePos <= 52)){
        pidLR.SetMode(MANUAL);
        pidLR.SetMode(AUTOMATIC);
      }
      //Serial.println((int)data);
      Serial.flush();//clear buffer
      if(linePos > 50)
        digitalWrite(LED_PIN, HIGH);//turn on LED
      else
        digitalWrite(LED_PIN, LOW);//turn off LED
    }
  }
}

