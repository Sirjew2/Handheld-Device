#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9340.h"

#if defined(__SAM3X8E__)
#undef __FlashStringHelper::F(string_literal)
#define F(string_literal) string_literal
#endif

const int buttonPin = 4;

// These are the pins used for the UNO
#define _sclk 13
#define _miso 12
#define _mosi 11
#define _cs 10
#define _dc 9
#define _rst 8

// Color definitions
#define BLACK    0x0000
#define BLUE     0x001F
#define RED      0xF800
#define GREEN    0x07E0
#define CYAN     0x07FF
#define MAGENTA  0xF81F
#define YELLOW   0xFFE0
#define WHITE    0xFFFF
#define DARKGREEN   0x03E0
#define LIGHTGREY   0xC618
#define DARKGREY    0x7BEF
#define GREENYELLOW 0xAFE5

Adafruit_ILI9340 tft = Adafruit_ILI9340(_cs, _dc, _rst);

int mode = 0;   // Current Mode
int modes = 4;  // Total Modes
int lastMode = -1; // Last Mode
int buttonState = 0;
boolean debug = true;
boolean alreadyRun = false;


void setup() {
  Serial.begin(9600);
  initDisplay();
  pinMode(buttonPin, INPUT);


}

void loop() {
  loadMode();
}
