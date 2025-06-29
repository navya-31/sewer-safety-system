#include <LiquidCrystal.h>
#include "DFRobotDFPlayerMini.h"
#include <SoftwareSerial.h>

// LCD pin setup
const int rs = 8, en = 9, d4 = 10, d5 = 11, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// DFPlayer setup
DFRobotDFPlayerMini player;
SoftwareSerial mySerial(2, 3); // DFPlayer connected to pins 2 and 3

int ir = 7; // IR sensor pin
int sts = 0; // Status indicator

void setup() {
  lcd.begin(16, 2); // Initialize LCD
  lcd.print("WELCOME");
  
  pinMode(ir, INPUT);
  
  mySerial.begin(9600);
  delay(1000);
  
  player.begin(mySerial);
  delay(200);
  player.volume(30); // Set volume level
  player.playMp3Folder(1); // Welcome audio
}

void loop() {
  int gval = analogRead(A0) / 10.23; // Read gas sensor value and convert to PPM
  lcd.clear();
  lcd.print("GAS: " + String(gval) + " Ppm");

  if (gval < 20) {
    lcd.setCursor(0, 1);
    lcd.print("Safe");
    sts = 0;
  }
  else if (gval < 30) {
    lcd.setCursor(0, 1);
    lcd.print("UnSafe -5min");
    sts = 1;
  }
  else if (gval < 40) {
    lcd.setCursor(0, 1);
    lcd.print("UnSafe -10min");
    sts = 2;
  }
  else if (gval < 50) {
    lcd.setCursor(0, 1);
    lcd.print("UnSafe -15min");
    sts = 3;
  }
  else if (gval < 60) {
    lcd.setCursor(0, 1);
    lcd.print("UnSafe -20min");
    sts = 4;
  }
  else if (gval < 70) {
    lcd.setCursor(0, 1);
    lcd.print("UnSafe -25min");
    sts = 5;
  }
  else if (gval < 80) {
    lcd.setCursor(0, 1);
    lcd.print("UnSafe -30min");
    sts = 6;
  }
  else {
    lcd.setCursor(0, 1);
    lcd.print("Danger - *");
    sts = 7;
  }

  delay(5000); // Display update delay

  // Play voice alert based on gas level if IR sensor detects presence
  if (digitalRead(ir) == 0) {
    player.playMp3Folder(sts + 1); // Play corresponding MP3 file
    delay(500);
  }
}
