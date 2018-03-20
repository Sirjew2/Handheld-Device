int snakeX[] = {120, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int snakeY[] = {160, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int snakeDir = 0;

int size = 5;
long timer = 0;
long interval = 300;
int appleX = random(0, 320);
int appleY = random(0, 240);

void initSnake(){
  snakeInput();
  if(millis() - timer > interval){
  snakeMove();
  snakeDraw();
  appleDraw();
  snakeGrow();
  timer = millis();
  }
}

void snakeMove(){
  for(int i=8; i>=0; i--){
    snakeX[i+1] = snakeX[i];
  }
    for(int i=8; i>=0; i--){
    snakeY[i+1] = snakeY[i];
  }
  if(snakeDir == 0){snakeX[0] = (snakeX[0] + 10) % 320;}
  if(snakeDir == 1){snakeX[0] = snakeX[0] - 10; if(snakeX <= 0){snakeX[0] = 320;}}
  if(snakeDir == 3){snakeY[0] = (snakeY[0] + 10) % 240;}
  if(snakeDir == 2){snakeY[0] = snakeY[0] - 10; if(snakeY <= 0){snakeY[0] = 240;}}
}

void snakeDraw(){
  
  for(int i=0; i<size + 1; i++){
    tft.fillRect(snakeX[i], snakeY[i], 10, 10, GREEN);
    //tft.drawPixel((snakeX[i], snakeY[i], GREEN);
  }
  tft.fillRect(snakeX[size+1], snakeY[size+1], 10, 10, BLACK);
}

void snakeInput(){
    if (digitalRead(buttonA) == HIGH) {
    snakeDir = 0;
  } else if (digitalRead(buttonB) == HIGH) {
    snakeDir = 3;
  }
    else if (digitalRead(buttonB) == HIGH) {
    snakeDir = 4;
  }
}

void appleDraw(){
  tft.fillRect(appleX, appleY, 10, 10, RED);
}

void eatApple(){
}

void snakeGrow(){
  if(snakeX[0] == appleX && snakeY[0] == appleY){
    size = size + 1;
  }
}


