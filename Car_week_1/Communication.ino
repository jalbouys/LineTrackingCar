void getData()//get data from Raspberry Pi
{
  if (Serial.available())
  {
    char data_in = Serial.read();
    if(data_in == 0)//not Position command
    {
      linePos = 100 - linePos; 
    }
    else
    {
      linePos = data_in;
      //Serial.println((int)data);
      Serial.flush();//clear buffer
      digitalWrite(LED_PIN, HIGH);//turn off LED
    }
  }
}

