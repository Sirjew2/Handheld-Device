int snakeX[] = {120, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int snakeY[] = {160, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int snakeDir = 0;

int size = 6;
int snakeS = 10;
long timer = 0;
long interval = 300;
int appleX = (random(0, 32) * 10);
int appleY = (random(0, 24) * 10);
int bDelay = 500;
int maxSnake = 16;

void initSnake() {
  Serial.println(size);
  snakeInput();
  if (millis() - timer > interval) {
    snakeDraw();
    snakeMove();

    appleDraw();
    snakeGrow();
    timer = millis();
    snakeScore();
  }
}

void snakeMove() {
  for (int i = maxSnake; i >= 0; i--) {
    snakeX[i + 1] = snakeX[i];
  }
  for (int i = maxSnake; i >= 0; i--) {
    snakeY[i + 1] = snakeY[i];
  }
  if (snakeDir == 0) {
    snakeX[0] = (snakeX[0] + 10) % 320;
  }
  if (snakeDir == 1) {
    snakeX[0] = snakeX[0] - 10;
    if (snakeX[0] <= 0) {
      snakeX[0] = 320;
    }
  }
  if (snakeDir == 3) {
    snakeY[0] = (snakeY[0] + 10) % 240;
  }
  if (snakeDir == 2) {
    snakeY[0] = snakeY[0] - 10;
    if (snakeY[0] <= 0) {
      snakeY[0] = 240;
    }
  }
}

void snakeDraw() {
  for (int i = 0; i < size + 1; i++) {
    tft.fillRect(snakeX[i], snakeY[i], 10, 10, GREEN);
  }
  tft.fillRect(snakeX[size + 1], snakeY[size + 1], 10, 10, BLUE);
}

void snakeInput() {
  sensorValue2 = analogRead(A2);
  sensorValue3 = analogRead(A3);

  if ((digitalRead(buttonA) == HIGH && snakeDir == 3) || (sensorValue2 > thresh && snakeDir == 3)) {
    snakeDir = 0;
    delay(bDelay);
  }
  else if ((digitalRead(buttonA) == HIGH && snakeDir == 0) || (sensorValue2 > thresh && snakeDir == 0)) {
    snakeDir = 2;
    delay(bDelay);
  }
  else if ((digitalRead(buttonA) == HIGH && snakeDir == 2) || (sensorValue2 > thresh && snakeDir == 2)) {
    snakeDir = 1;
    delay(bDelay);
  }
  else if ((digitalRead(buttonA) == HIGH && snakeDir == 1) || (sensorValue2 > thresh && snakeDir == 1)) {
    snakeDir = 3;
    delay(bDelay);
  }
  else if ((digitalRead(buttonB) == HIGH && snakeDir == 0) || (sensorValue3 > thresh && snakeDir == 0)) {
    snakeDir = 3;
    delay(bDelay);
  }
  else if ((digitalRead(buttonB) == HIGH && snakeDir == 3) || (sensorValue3 > thresh && snakeDir == 3)) {
    snakeDir = 1;
    delay(bDelay);
  }
  else if ((digitalRead(buttonB) == HIGH && snakeDir == 1) || (sensorValue3 > thresh && snakeDir == 1)) {
    snakeDir = 2;
    delay(bDelay);
  }   else if ((digitalRead(buttonB) == HIGH && snakeDir == 2) || (sensorValue3 > thresh && snakeDir == 2)) {
    snakeDir = 0 ;
    delay(bDelay);
  }
}

void appleDraw() {
  tft.fillRect(appleX, appleY, 10, 10, RED);
}

void snakeScore() {
  tft.setTextSize(2); tft.setCursor(295, 10);
  tft.println(snakeS);
}

void snakeGrow() {
  if (snakeX[0] == appleX && snakeY[0] == appleY) {
    size = size + 1;
    snakeS = snakeS + 1;
    appleX = (random(0, 32) * 10);
    appleY = (random(0, 24) * 10);
  }
}


