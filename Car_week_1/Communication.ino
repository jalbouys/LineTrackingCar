void getData()//get data from Raspberry Pi
{
  if (Serial.available())
  {
    linePos = Serial.read();
    //Serial.println((int)data);
    Serial.flush();//clear buffer
    digitalWrite(LED_PIN, HIGH);//turn off LED
  }
}

