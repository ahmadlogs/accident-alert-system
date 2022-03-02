#include<LiquidCrystal_I2C.h>

#include<Wire.h>

//initialize the liquid crystal library
//the first parameter is the I2C address
//the second parameter is how many rows are on your screen
//the third parameter is how many columns are on your screen
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  
  //initialize lcd screen
  lcd.begin();
  // turn on the backlight
  lcd.backlight();
  lcd.clear();
  //wait for a second
  delay(1000);
  // tell the screen to write on the top row
  lcd.setCursor(0,0);
  // tell the screen to write “hello, from” on the top row
  lcd.print("abc");
  
}
void loop() {

  
}
