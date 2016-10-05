void getData()//get data from Raspberry Pi
{

  String readString="";
  while (Serial.available()) {
      delay(10);
      if (Serial.available() > 0) {
          char c = Serial.read(); // Gets one byte from serial buffer
          readString += c; // Makes the string readString
      }
    }

    if (readString.length() > 0) {
        Serial.println(readString); // See what was receive
        digitalWrite(LED_PIN, HIGH); // Turn the LED on (HIGH is the voltage level).
        delay(1000);             // Wait for one second.
        digitalWrite(LED_PIN, LOW);  // Turn the LED off by making the voltage LOW.
        delay(1000);  
        
    }
   
}

