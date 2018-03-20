// Load Current Mode
void loadMode() {
  // Clear Screen if Mode Changes
  if (lastMode != mode) {
    lastMode = mode;
    tft.fillScreen(BLUE);
    tft.setRotation(1);
  }

  switch (mode) {
    case 0: mainMenu(); break;
    case 1: pong(); break;
    case 2: flappy(); break;
    case 3: snake(); break;
    case 4: help(); break;
    case 5: about(); break;
  }


}

////////////////////////////////////////////////////////////////////////////////////////////////
// BATTERY MONITOR //
////////////////////////////////////////////////////////////////////////////////////////////////
int checkBattery() {
  return analogRead(1);
}

static const unsigned char PROGMEM batt[] =
{ B00111111, B11111000,
  B01000000, B00000100,
  B01011000, B00000110,
  B01011000, B00000110,
  B01011000, B00000110,
  B01011000, B00000110,
  B01000000, B00000100,
  B00111111, B11111000,
};

////////////////////////////////////////////////////////////////////////////////////////////////
// MAIN MENU //
////////////////////////////////////////////////////////////////////////////////////////////////

int curSelection = 0;

void mainMenu() {
  // Button Input
  int b = checkButtons();
  if (b == 1) {
    curSelection = max(0, curSelection - 1);
  }
  if (b == 2) {
    curSelection = min(4, curSelection + 1);
  }
  if (b == 3) {
    mode = curSelection + 1;
  }

    tft.setTextSize(3);
    tft.setTextColor(YELLOW, BLUE);
    tft.setCursor(0, 0);

    tft.println("MGM Main Menu");

    tft.println("");
    tft.println("Game Select:");

    tft.println("");
    tft.println("");
    tft.println("");
    tft.println("");
    tft.println("Other:");


  if (checkBattery < 100 || debug) {
    tft.drawBitmap(295, 2, batt, 16, 8, YELLOW);
  }

  // Pong
  tft.setTextSize(2); tft.setCursor(0, 80);
  if (curSelection == 0) {
    tft.setTextColor(BLUE, YELLOW);
  }
  else {
    tft.setTextColor(YELLOW, BLUE);
  }
  tft.println("-> Pong");

  // Flappy Bird
  tft.setTextSize(2); tft.setCursor(0, 100);
  if (curSelection == 1) {
    //  tft.fillRect(0, 99, 320, 20, YELLOW);
    tft.setTextColor(BLUE, YELLOW);
  }
  else {
    tft.setTextColor(YELLOW, BLUE);
  }
  tft.println("-> Flappy Bird");

  // Snake
  tft.setTextSize(2); tft.setCursor(0, 120);
  if (curSelection == 2) {
    tft.setTextColor(BLUE, YELLOW);
  }
  else {
    tft.setTextColor(YELLOW, BLUE);
  }
  tft.println("-> Snake");

  // Help
  tft.setTextSize(2); tft.setCursor(0, 200);
  if (curSelection == 3) {
    tft.setTextColor(BLUE, YELLOW);
  }
  else {
    tft.setTextColor(YELLOW, BLUE);
  }
  tft.println("-> Help");

  // About
  tft.setTextSize(2); tft.setCursor(0, 220);
  if (curSelection == 4) {
    tft.setTextColor(BLUE, YELLOW);
  }
  else {
    tft.setTextColor(YELLOW, BLUE);
  }
  tft.println("-> About");


}


////////////////////////////////////////////////////////////////////////////////////////////////
// PONG //
////////////////////////////////////////////////////////////////////////////////////////////////


void pong() {
  int b = checkButtons();
  if (b == 1) {} // Do nothing
  if (b == 2) {} // Do nothing
  if (b == 3) {
    mode = 0; // Return to Main Screen
  }
  initPong();
}

////////////////////////////////////////////////////////////////////////////////////////////////
// FLAPPY BIRD //
////////////////////////////////////////////////////////////////////////////////////////////////

void flappy() {
  // Button Input
  int b = checkButtons();
  if (b == 1) {} // Do nothing
  if (b == 2) {} // Do nothing
  if (b == 3) {
    mode = 0; // Return to Main Screen
  }
  initLoop();
}


////////////////////////////////////////////////////////////////////////////////////////////////
// SNAKE //
////////////////////////////////////////////////////////////////////////////////////////////////

void snake() {
  // Button Input
  int b = checkButtons();
  if (b == 1) {} // Do nothing
  if (b == 2) {} // Do nothing
  if (b == 3) {
    mode = 0; // Return to Main Screen
  }
  initSnake();
}

////////////////////////////////////////////////////////////////////////////////////////////////
// HELP //
////////////////////////////////////////////////////////////////////////////////////////////////

void help() {
  // Button Input
  int b = checkButtons();
  if (b == 1) {} // Do nothing
  if (b == 2) {} // Do nothing
  if (b == 3) {
    mode = 0; // Return to Main Screen
  }
  tft.setTextSize(3);
  tft.setTextColor(YELLOW, BLUE);
  tft.setCursor(0, 0);
  tft.println("  Muscle Gaming");
  tft.println("    MACHINE");
  tft.println("      Help:");
  tft.println("");
  tft.setTextSize(2);
  tft.println("Attach the color-indicated");
  tft.println("MGM muscle sensors to");
  tft.println("which ever muscle you");
  tft.println("prefer.Flex that muscle");
  tft.println("to activate the game");
  tft.println("controls!");


}

////////////////////////////////////////////////////////////////////////////////////////////////
// About //
////////////////////////////////////////////////////////////////////////////////////////////////

void about() {
  // Button Input
  int b = checkButtons();
  if (b == 1) {} // Do nothing
  if (b == 2) {} // Do nothing
  if (b == 3) {
    mode = 0; // Return to Main Screen
  }
  tft.setTextSize(3);
  tft.setTextColor(YELLOW, BLUE);
  tft.setCursor(0, 0);
  tft.println("About MGM");
  tft.println("");
  tft.setTextSize(2);
  tft.println("By Nathan Hirsh");
  tft.println("");
  tft.println("Created for CRT 420");
  tft.println("Advanced Prototyping");
  tft.println("Spring 2018");
  tft.println("for your enjoyment!!");


}

