// Handle Button Presses
int thresh = 11;
int count = 0;
int sensorPin2 = A2;
int sensorPin3 = A3;
int sensorValue2 = 0;
int sensorValue3 = 0;

int buttonA = 7;
int buttonB = 6;
int buttonC = 5;
int buttonDelay = 100;

// Initialize All Buttons
void initButtons(){
  pinMode(buttonA, INPUT);
  pinMode(buttonB, INPUT);
  pinMode(buttonC, INPUT);
  

}

// Check for Button Presses
int checkButtons(){
  sensorValue2 = analogRead(A2);
  sensorValue3 = analogRead(A3);
  if(digitalRead(buttonA) == HIGH){delay(buttonDelay); if(debug){Serial.println(1);}  return 1;}
  if(digitalRead(buttonB) == HIGH){delay(buttonDelay); if(debug){Serial.println(2);}  return 2;}
  if(digitalRead(buttonC) == HIGH){delay(buttonDelay); if(debug){Serial.println(3);}  return 3;}
  return 0;
}
