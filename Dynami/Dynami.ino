#include <SPI.h>
#include <Wire.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH 16

static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000
};

const int PAUSE = 200;
const int MIN_PULSES = 30;
volatile long pulses = 0;
volatile unsigned long pulseTime = 0;
volatile unsigned long firstTime = 0;
int value = 0;
int rotation = 0;
boolean up = true;
float velocidad;
float subida;

void setup() {
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("DYNAMI");
  display.setTextSize(1);
  display.println(" ");
  display.println("SE TU MEJOR VERSION");
  display.display();
}
void printValues() {
  if (pulseTime != 0 && millis() - pulseTime > PAUSE) {
    if (pulses > MIN_PULSES) {

      if (up) {
        display.clearDisplay();
        Serial.print("Up: ");
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0, 0);
        display.println("Velocidad: ");

      } else {
        Serial.print("Down: "); .
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0, 0);
        display.println("Velocidad: ");
      }

      velocidad = (float) (pulses / 2) * 0.00124579518308312 / ((float)(pulseTime - firstTime) / 1000);
      Serial.print(velocidad);
      Serial.println(" m/s");

      if (up) {
        subida = velocidad;
        display.setTextSize(2);
        display.print(" ");
        display.print(subida);
        display.println(" m/s");
        display.setTextSize(1);
        display.print(" OK");
      }
      else {
        display.setTextSize(2);
        display.print(" ");
        display.print(subida);
        display.println(" m/s");
        display.setTextSize(1);
        display.print(" GO");
      }
      up = !up;
      display.display();
      display.clearDisplay();
    }
    pulseTime = 0;
    pulses = 0;
  }
}

void loop() {
  value = digitalRead(2);
  if (value != rotation) {
    if (digitalRead(3) != value) {
      pulses++;
      if (pulseTime == 0) {
        firstTime = millis();
      }
      pulseTime = millis();
    } else {
    }
    rotation = value;
  }
  printValues();
}
