

#define tftW            320    // screen width
#define tftH            240     // screen height
#define tftW2           160     // half screen width
#define tftH2           120    // half screen height
// game constant
#define SPEED             1
#define GRAVITY        2
#define JUMP_FORCE     .5
#define SKIP_TICKS     20.0     // 1000 / 50fps
#define MAX_FRAMESKIP     5
// bird size
#define BIRDW             8     // bird width
#define BIRDH             8     // bird height
#define BIRDW2            4     // half width
#define BIRDH2            4     // half height
// pipe size
#define PIPEW            6     // pipe width
#define GAPHEIGHT        48     // pipe gap height
// floor size
#define FLOORH           40     // floor height (from bottom of the screen)
// grass size
#define GRASSH            4     // grass height (inside floor, starts at floor y)

// background
const unsigned int BCKGRDCOL = BLUE;
// bird
const unsigned int BIRDCOL = GREENYELLOW;
// pipe
const unsigned int PIPECOL  = GREEN;
// pipe highlight
const unsigned int PIPEHIGHCOL  = WHITE;
// pipe seam
const unsigned int PIPESEAMCOL  = BLUE;
// floor
const unsigned int FLOORCOL = DARKGREEN;
// grass (col2 is the stripe color)
const unsigned int GRASSCOL  = GREEN;
const unsigned int GRASSCOL2 = WHITE;


// bird sprite
// bird sprite colors (Cx name for values to keep the array readable)
#define C0 BCKGRDCOL
#define C1 GREEN
#define C2 BIRDCOL
#define C3 DARKGREEN
#define C4 RED
#define C5 YELLOW
static unsigned int birdcol[] =
{ C0, C0, C1, C1, C1, C1, C1, C0,
  C0, C1, C2, C2, C2, C1, C3, C1,
  C0, C2, C2, C2, C2, C1, C3, C1,
  C1, C1, C1, C2, C2, C3, C1, C1,
  C1, C2, C2, C2, C2, C2, C4, C4,
  C1, C2, C2, C2, C1, C5, C4, C0,
  C0, C1, C2, C1, C5, C5, C5, C0,
  C0, C0, C1, C5, C5, C5, C0, C0
};

// bird structure
static struct BIRD {
  unsigned char x, y, old_y;
  unsigned int col;
  float vel_y;
} bird;
// pipe structure
static struct PIPE {
  char x, gap_y;
  unsigned int col;
} pipe;

// score
static short score;
// temporary x and y var
static short tmpx, tmpy;

// ---------------
// draw pixel
// ---------------
// faster drawPixel method by inlining calls and using setAddrWindow and pushColor
// using macro to force inlining
#define drawPixel(a, b, c) tft.setAddrWindow(a, b, a, b); tft.pushColor(c)


// ---------------
// main loop
// ---------------
void initLoop() {
  game_start();
  game_loop();
  game_over();
}

// ---------------
// game loop
// ---------------
void game_loop() {
  // ===============
  // prepare game variables
  // draw floor
  // ===============
  // instead of calculating the distance of the floor from the screen height each time store it in a variable
  unsigned char GAMEH = tftH - FLOORH;
  // draw the floor once, we will not overwrite on this area in-game
  // black line
  tft.drawFastHLine(0, GAMEH, tftW, BLACK);
  // grass and stripe
  tft.fillRect(0, GAMEH + 1, tftW2, GRASSH, GRASSCOL);
  tft.fillRect(tftW2, GAMEH + 1, tftW2, GRASSH, GRASSCOL2);
  // black line
  tft.drawFastHLine(0, GAMEH + GRASSH, tftW, BLACK);
  // mud
  tft.fillRect(0, GAMEH + GRASSH + 1, tftW, FLOORH - GRASSH, FLOORCOL);
  // grass x position (for stripe animation)
  char grassx = tftW;
  // game loop time variables
  double delta, old_time, next_game_tick, current_time;
  next_game_tick = current_time = millis();
  int loops;
  // passed pipe flag to count score
  bool passed_pipe = false;
  // temp var for setAddrWindow
  unsigned char px;

  while (1) {
    loops = 0;
    while ( millis() > next_game_tick && loops < MAX_FRAMESKIP) {
      // ===============
      // input
      // ===============
      //  if ( !(PIND & (1<<PD2)) ) {
      // if the bird is not too close to the top of the screen apply jump force
      //  if (bird.y > BIRDH2*0.5) bird.vel_y = -JUMP_FORCE;
      // else zero velocity
      //    else bird.vel_y = 0;
      //}



      if (digitalRead(buttonA) == HIGH) {
        if ( !(PIND & (1 << PD2)));
        if (bird.y > BIRDH2 * 0.5) bird.vel_y = JUMP_FORCE;
        else bird.vel_y = 0;
      }

      // ===============
      // update
      // ===============
      // calculate delta time
      // ---------------
      old_time = current_time;
      current_time = millis();
      delta = (current_time - old_time) / 1000;

      // bird
      // ---------------
      bird.vel_y -= GRAVITY * delta;
      bird.y -= bird.vel_y;

      // pipe
      // ---------------
      pipe.x -= SPEED;
      // if pipe reached edge of the screen reset its position and gap
      if (pipe.x < -PIPEW) {
        pipe.x = tftW-200;
        pipe.gap_y = random(10, GAMEH - (10 + GAPHEIGHT));
      }

      // ---------------
      next_game_tick += SKIP_TICKS;
      loops++;
    }

    // ===============
    // draw
    // ===============
    // pipe
    // ---------------
    // we save cycles if we avoid drawing the pipe when outside the screen
    if (pipe.x >= 0 && pipe.x < tftW) {
      // pipe color
      tft.drawFastVLine(pipe.x + 3, 0, pipe.gap_y, PIPECOL);
      tft.drawFastVLine(pipe.x + 3, pipe.gap_y + GAPHEIGHT + 1, GAMEH - (pipe.gap_y + GAPHEIGHT + 1), PIPECOL);
      // highlight
      tft.drawFastVLine(pipe.x, 0, pipe.gap_y, PIPEHIGHCOL);
      tft.drawFastVLine(pipe.x, pipe.gap_y + GAPHEIGHT + 1, GAMEH - (pipe.gap_y + GAPHEIGHT + 1), PIPEHIGHCOL);
      // bottom and top border of pipe
      drawPixel(pipe.x, pipe.gap_y, PIPESEAMCOL);
      drawPixel(pipe.x, pipe.gap_y + GAPHEIGHT, PIPESEAMCOL);
      // pipe seam
      drawPixel(pipe.x, pipe.gap_y - 6, PIPESEAMCOL);
      drawPixel(pipe.x, pipe.gap_y + GAPHEIGHT + 6, PIPESEAMCOL);
      drawPixel(pipe.x + 3, pipe.gap_y - 6, PIPESEAMCOL);
      drawPixel(pipe.x + 3, pipe.gap_y + GAPHEIGHT + 6, PIPESEAMCOL);
    }
    // erase behind pipe
    if (pipe.x <= tftW) tft.drawFastVLine(pipe.x + PIPEW, 0, GAMEH, BCKGRDCOL);

    // bird
    // ---------------
    tmpx = BIRDW - 1;
    do {
      px = bird.x + tmpx + BIRDW;
      // clear bird at previous position stored in old_y
      // we can't just erase the pixels before and after current position
      // because of the non-linear bird movement (it would leave 'dirty' pixels)
      tmpy = BIRDH - 1;
      do {
        drawPixel(px, bird.old_y + tmpy, BCKGRDCOL);
      } while (tmpy--);
      // draw bird sprite at new position
      tmpy = BIRDH - 1;
      do {
        drawPixel(px, bird.y + tmpy, birdcol[tmpx + (tmpy * BIRDW)]);
      } while (tmpy--);
    } while (tmpx--);
    // save position to erase bird on next draw
    bird.old_y = bird.y;

    // grass stripes
    // ---------------
    grassx -= SPEED;
    if (grassx < 0) grassx = tftW;
    tft.drawFastVLine( grassx    % tftW, GAMEH + 1, GRASSH - 1, GRASSCOL);
    tft.drawFastVLine((grassx + 64) % tftW, GAMEH + 1, GRASSH - 1, GRASSCOL2);

    // ===============
    // collision
    // ===============
    // if the bird hit the ground game over
    if (bird.y > GAMEH - BIRDH) break;
    // checking for bird collision with pipe
    if (bird.x + BIRDW >= pipe.x - BIRDW2 && bird.x <= pipe.x + PIPEW - BIRDW) {
      // bird entered a pipe, check for collision
      if (bird.y < pipe.gap_y || bird.y + BIRDH > pipe.gap_y + GAPHEIGHT) break;
      else passed_pipe = true;
    }
    // if bird has passed the pipe increase score
    else if (bird.x > pipe.x + PIPEW - BIRDW && passed_pipe) {
      passed_pipe = false;
      // erase score with background color
      tft.setTextColor(BCKGRDCOL);
      tft.setTextSize(2);
      tft.setCursor( tftW2, 4);
      tft.print(score);
      // set text color back to white for new score
      tft.setTextColor(WHITE);
      // increase score since we successfully passed a pipe
      score++;
    }

    // update score
    // ---------------
    tft.setCursor( tftW2, 4);
    tft.print(score);
  }

  // add a small delay to show how the player lost
  delay(1200);
}

// ---------------
// game start
// ---------------
void game_start() {
  tft.fillScreen(BLACK);
  tft.fillRect(10, tftH2 - 20, tftW - 20, 1, WHITE);
  tft.fillRect(10, tftH2 + 32, tftW - 20, 1, WHITE);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  // half width - num char * char width in pixels
  tft.setCursor( tftW2 - (6 * 9), tftH2 - 16);
  tft.println("FLAPPY");
  tft.setTextSize(3);
  tft.setCursor( tftW2 - (6 * 9), tftH2 + 8);
  tft.println("-BIRD-");
  tft.setTextSize(0);
  tft.setCursor( 10, tftH2 - 28);
  tft.println("ATMEGA328");
  tft.setCursor( tftW2 - (12 * 3) - 1, tftH2 + 34);
  tft.println("press button");
  while (1) {
    // wait for push button
    if ( !(PIND & (1 << PD2)) ) break;
  }

  // init game settings
  game_init();
}

// ---------------
// game init
// ---------------
void game_init() {
  // clear screen
  tft.fillScreen(BCKGRDCOL);
  // reset score
  tft.setTextSize(2);
  score = 0;
  // init bird
  bird.x = 20;
  bird.y = bird.old_y = tftH2 - BIRDH;
  bird.vel_y = -JUMP_FORCE;
  tmpx = tmpy = 0;
  // generate new random seed for the pipe gape
  randomSeed(analogRead(0));
  // init pipe
  pipe.x = tftW-200;
  pipe.gap_y = random(20, tftH - 60);
}

// ---------------
// game over
// ---------------
void game_over() {
  tft.fillScreen(BLACK);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  // half width - num char * char width in pixels
  tft.setCursor( tftW2 - (9 * 6), tftH2 - 4);
  tft.println("GAME OVER");
  tft.setTextSize(1);
  tft.setCursor( 10, tftH2 - 14);
  tft.print("score: ");
  tft.print(score);
  tft.setCursor( tftW2 - (12 * 3), tftH2 + 12);
  tft.println("press button");
  while (1) {
    // wait for push button
    if ( !(PIND & (1 << PD2)) ) break;
  }
}
