#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); 

#include "Adafruit_Keypad.h"

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};


byte rowPins[ROWS] = { 2, 3, 4, 5 };

byte colPins[COLS] = { 8, 9, 10, 11 };

Adafruit_Keypad myKeypad = Adafruit_Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  lcd.init();       
  lcd.clear();  
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Warte auf");
  lcd.setCursor(0, 1);
  lcd.print("Eingabe");

  myKeypad.begin();
  Serial.begin(9600);
}

void loop() {
  myKeypad.tick();

  while (myKeypad.available()) {
    keypadEvent e = myKeypad.read();
    Serial.print((char)e.bit.KEY);
    if((char)e.bit.KEY == '1') {
      lcd.clear();
      lcd.print("Richtig");
      return;
    } else if (e.bit.EVENT == KEY_JUST_PRESSED) { 
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print((char)e.bit.KEY);
    lcd.print(" pressed");
    } else if (e.bit.EVENT == KEY_JUST_RELEASED){ 
    lcd.clear();
    Serial.println(" released");
    lcd.setCursor(0, 0);
    lcd.print((char)e.bit.KEY);
    lcd.print(" released");
  }

  delay(10);
}

}