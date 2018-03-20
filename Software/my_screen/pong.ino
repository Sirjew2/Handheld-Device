float BPX = 15;  // Ball Position X
float BPY = 15;  // Ball Position Y
int byx = 15;
int bx = 1;
int A = 1;      // Ball Direction (1 = left to right, -1 = right to left)
int by = 1;
int playerScore = 0;    // These variables hold the player & computer score.
int computerScore = 0;
#define WINSCORE 5  // When you reach this value you win - suggest you keep <=9 for display alignment, increase > 9 if you tweek

int R, L, D, U;     // These values adjust the paddles L & R from player buttons, U & D from computer algorithm
int playerPaddle = 120;   // Player Paddle Position
int computerPaddle = 120; // Computer's Paddle Position
int Random;





void initPong() {
  DisplayScore(playerScore, computerScore);
  if ((BPY == 80) || (BPY == 20)) { //This is how i made the computer/the probability of the computer making an error
    Random = random(1, 10);
  }
  if (Random <= 8) {

    if (( A == 1) || ((BPY > 100) && ( A == -1))) {
      if ((bx == -1) && (BPX < (computerPaddle + 16))) {
        U = 1;
        D = 0;
      }    //Computer simulation
      if ((bx == 1) && (BPX > (computerPaddle + 16))) {
        D = 1;
        U = 0;
      }
    }
    else {
      D = 0;
      U = 0;
    }
  }

  if ((Random > 8) && (Random <= 9)) {
    if (( A == 1) || ((BPY > 100) && ( A == -1))) {
      if ((bx == -1) && (BPX < (computerPaddle + 16))) {
        U = 0;
        D = 1;
      }    //Computer simulation
      if ((bx == 1) && (BPX > (computerPaddle + 16))) {
        D = 0;
        U = 1;
      }
    }
    else {
      D = 0;
      U = 0;
    }
  }

  if (Random > 9) {

    if (( A == 1) || ((BPY > 100) && ( A == -1))) {
      if ((bx == -1) && (BPX < (computerPaddle - 16))) {
        U = 1;
        D = 0;
      }    //Computer simulation
      if ((bx == 1) && (BPX > (computerPaddle - 16))) {
        D = 1;
        U = 0;
      }
    }
    else {
      D = 0;
      U = 0;
    }
  }

  DrawCourt(0);  // Draw court line(s)

  R = 5;
  L = 5;



  if (digitalRead(buttonA) == HIGH) {
    playerPaddle = playerPaddle + 3;
  } else if (digitalRead(buttonB) == HIGH) {
    playerPaddle = playerPaddle - 3;
  }

  //These equations are for the movement of the paddle, R, L, D, and U are all boolean.  paddles initially equal 48. This is so

  //at startup the paddles are at center.

  computerPaddle = computerPaddle + D; //I used D and U because i use the buttons for other applications but they can be defined as player2 R and L
  computerPaddle = computerPaddle - U;

  tft.fillRect(playerPaddle - 4, 3, 4, 3, BLUE); //These two parts are so the paddle erase themselves as they move, they could have been BLUE pixels but i just used
  tft.fillRect(playerPaddle + 33, 3, 4, 3, BLUE);
  tft.fillRect(playerPaddle, 3, 32, 3, GREEN);   //This is the paddle for one player

  if (playerPaddle <= 1) // This is so the paddle does not move off the screen on the bottom side of the screen
    playerPaddle = 2;
  if (playerPaddle >= 183) // This is so the paddle does not move off the screen on the top side of the screen
    playerPaddle = 182;

  tft.fillRect(computerPaddle, 312, 32, 3, GREEN);
  tft.fillRect(computerPaddle - 1, 312, 2, 3, BLUE);
  tft.fillRect(computerPaddle + 33, 312, 2, 3, BLUE);

  if (computerPaddle <= 1)
    computerPaddle = 2;
  if (computerPaddle >= 183)
    (computerPaddle = 182);

  byx = (A + byx);
  BPY = ((byx));
  BPX = (bx + BPX);

  if ((BPX >= 210) || (BPX <= 2)) {
    (bx = (-1 * bx));
  }
  else {
  };
  if ((BPX <= (computerPaddle + 38)) && (BPX >= (computerPaddle - 6)) && (BPY == 309)) {
    (A = (-1 * A));
  }
  else {
  };
  if ((BPX <= (playerPaddle + 38) && (BPX >= (playerPaddle - 6)) && (BPY == 11))) {
    (A = (-1 * A));
  }
  else {
  };

  if (BPY >= 320 || BPY <= 0) { // someone scored!
    if (BPY >= 320)
      playerScore = playerScore + 1;
    else
      computerScore = computerScore + 1;
    // Reset:                                   // reset court after score
    DisplayScore(playerScore, computerScore);
    DrawCourt(0);
    tft.fillCircle(BPX, BPY, 7, BLUE);  // erase ball in last known location
    BPX = 64;                                   // set ball to center of screen
    BPY = 80;
    tft.fillCircle(BPX, BPY, 4, GREEN);  // draw ball  in center
    delay(3000);                                // delay 3 seconds
    tft.fillCircle(BPX, BPY, 7, BLUE);
    byx = 80;
  }

  DisplayScore(playerScore, computerScore);

  if (playerScore == WINSCORE || computerScore == WINSCORE) { // if someone hit the winning score then game over - print who one and reset game
    tft.setRotation(1);
    tft.setTextColor(WHITE, BLUE);
    tft.setCursor(30, 50);
    tft.setTextSize(3);

    if (playerScore == WINSCORE) { // player wins
      tft.print("Player 1 WINS!");
    }
    else {
      tft.print("Player 2 WINS!");   // computer wins
    }
    delay(2000);

    //NEWGAME:           //Resets the screen for a new game

    tft.setTextSize(2);
    tft.setTextColor(YELLOW, BLUE);
    tft.setCursor(8, 90);
   // tft.println("Press SELECT to Return to Main Menu");
   // tft.println("Press UP to Start New Game");
    //while (digitalRead(buttonA) == HIGH);                                            // New game when swtich 4 is pressed
    tft.setRotation(0);
    tft.fillScreen(BLUE);
    tft.fillCircle(BPX, BPY, 7, BLUE);
    BPX = 15;
    BPY = 15;
    byx = 15;
    bx = 1;
    A = 1;
    tft.fillCircle(BPX, BPY, 4, GREEN);
    tft.fillCircle(BPX, BPY, 7, BLUE);
    tft.fillCircle(BPX, BPY, 4, GREEN);
    tft.fillCircle(BPX, BPY, 7, BLUE);
    computerScore = 0;
    playerScore = 0;
    DrawCourt(0);
    DisplayScore(playerScore, computerScore);

   // delay(2000);     // wait 4 seconds to start new game
  }
  //If you want, uncomment to use the new scoring method/output using bars
  //////////////////////////////////////////////
  // DisplayScoreTicks(playerScore, computerScore);
  ////////////////////////////////////////////

  tft.fillCircle(BPX, BPY, 6, BLUE);  //BLUE sudo ball to errase itself
  // if little green pixels start to light up due to the ball, change the 6 to a 7
  tft.fillCircle(BPX, BPY, 4, GREEN);  //This is the actual ball

}

void DrawCourt(boolean onlycenter) // Draw the play court lines (pass 1 to onlu have the center line drawn for speed)
{
  if (!onlycenter) {
    tft.drawFastVLine(0, 0, 320, GREEN);
    tft.drawFastVLine(215, 0, 320, GREEN);
  }
  tft.drawFastHLine(0, 160, 215, GREEN);  // Center Line
}

void DisplayScore(int playerScore, int computerScore)  // display score with numbers.  Tested for WINSCORE <= 9 (ot greater # digits than 1)
{
  tft.setRotation(1);
  tft.setTextColor(GREEN, BLUE);
  tft.setCursor(140, 5);
  tft.setTextSize(2);
  tft.print(playerScore);
  tft.setCursor(170, 5);
  tft.print(computerScore);
  tft.setRotation(0);
}

// You can use this code to keep score with tick marks up to a winning score of 5.  If you change WINGAME > 5 then this will not work
// This code is not currently used as numbers are used.  But kept for compatibility with David's original game
void DisplayScoreTicks(int playerScore, int computerScore)  // display score with tick marks
{
  switch (playerScore) {
    case 1:
      tft.fillRect(120, 64, 4, 1, WHITE);
      break;
    case 2:
      tft.fillRect(120, 68, 4, 1, WHITE);
      break;
    case 3:
      tft.fillRect(120, 72, 4, 1, WHITE);
      break;
    case 4:
      tft.fillRect(120, 76, 4, 1, WHITE);
      break;
  }  // end switch

  switch (computerScore) {
    case 1:
      tft.fillRect(120, 84, 4, 1, GREEN);
      break;
    case 2:
      tft.fillRect(120, 88, 4, 1, GREEN);
      break;
    case 3:
      tft.fillRect(120, 92, 4, 1, GREEN);
      break;
    case 4:
      tft.fillRect(120, 96, 4, 1, GREEN);
      break;
  }  // end switch
}
