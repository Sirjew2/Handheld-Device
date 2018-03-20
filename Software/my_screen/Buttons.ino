// Handle Button Presses

int buttonA = 4;
int buttonB = 5;
int buttonC = 6;
int buttonDelay = 10;

// Initialize All Buttons
void initButtons(){
  pinMode(buttonA, INPUT);
  pinMode(buttonB, INPUT);
  pinMode(buttonC, INPUT);
}

// Check for Button Presses
int checkButtons(){
  if(digitalRead(buttonA) == HIGH){delay(buttonDelay); if(debug){Serial.println(1);}  return 1;}
  if(digitalRead(buttonB) == HIGH){delay(buttonDelay); if(debug){Serial.println(2);}  return 2;}
  if(digitalRead(buttonC) == HIGH){delay(buttonDelay); if(debug){Serial.println(3);}  return 3;}
  return 0;
}
