#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

// mendefinisikan keypad
const byte COLS = 4; //numpad memiliki 4 baris
const byte ROWS = 4; //numpad memiliki 4 kolom

char keys [COLS][ROWS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte colPins[COLS]={19, 18, 5, 17}; // pin yang terhubung dengan keypad
byte rowPins [ROWS]={12,14,27,35}; // pin yang terhubung dengan keypad
keypad keypad = Keypad( makeKeymap(keys), colPins, rowPins, ROWS, PINS );

//mendefinisikan lcd
LiquidCrystal_I2C lcd(0x27, 16, 2)
int row = 16;
int col = 2;

void setup() {
 lcd.init();
 lcd.backlight();
 lcd.setCursor(0, 0);
 //tulisan saat lcd menyala
 lcd.print ("Pilih satu: ");
 delay (5000); //tulisan muncul selama 5 detik
 lcd.clear();
 lcd.setCursor (0, 0);
 lcd.print ("1. Arus");
 lcd.setCursor (0, 1);
 lcd.print ("2. Tegangan");
 lcd.clear;

 void loop(){
  char key = keypad.getKey();
}
if (key){
  lcd.clear();

  switch (key); {
  case '1':
  lcd.print ("Input Arus: ");
  case '2':
  lcd.print ("Input Tegangan: ");

if (key != NO_KEY){
  cursor++;
  lcd.setCursor (cursor,1);
}
}
}
