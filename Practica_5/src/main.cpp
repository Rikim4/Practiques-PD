#include <LiquidCrystal_I2C.h>

// set the LCD number of columns and rows
int lcdColumns = 16;
int lcdRows = 3;

// set LCD address, number of columns and rows
// if you don't know your display address, run an I2C scanner sketch
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  

void setup(){
  // initialize LCD
  lcd.init();
  // turn on LCD backlight                      
  lcd.backlight();
}

void loop(){
  // set cursor to first column, first row
  lcd.setCursor(0, 0);
  // print message
  lcd.print("HOLA MUNDO");
  delay(1000);
  // clears the display to print new message
  lcd.clear();
  // set cursor to first column, second row
  lcd.setCursor(0,1);
  lcd.print("ESTOY ");
  delay(1000);
  lcd.clear();

  lcd.setCursor(0,2);
  lcd.print("EN");
  delay(1000);
  lcd.clear();

  lcd.setCursor(0,3);
  lcd.print("CLASE");
  delay(1000);
  lcd.clear();
}