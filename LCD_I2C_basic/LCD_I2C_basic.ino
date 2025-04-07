#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  lcd.init();
  lcd.backlight();
}

void loop()
{
  lcd.setCursor(2, 0);
  lcd.print("Ho Dang Manh");
  lcd.setCursor(0, 1);
  lcd.print("I LOVE YOU");
  delay(100);
  
}