#include<Wire.h>
#include<LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x20,16,2);


void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
    lcd.print("Hola :)");
  lcd.setCursor(0,1);
  delay(10000);
  lcd.clear();

}

void loop() {
  lcd.display();
  delay(500);
  lcd.nodisplay();
  delay(500);

}
