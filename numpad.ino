#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

#define ROW_NUM 4 // empat baris
#define COLUMN_NUM 4 // empat kolom

char keys[ROW_NUM][COLUMN_NUM] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

byte pin_rows[ROW_NUM] = {19, 18, 5, 17}; // GPIO19, GPIO18, GPIO5, GPIO17 terhubung ke pin baris
byte pin_column[COLUMN_NUM] = {16, 4, 0, 2}; // GPIO16, GPIO4, GPIO0, GPIO2 terhubung ke pin kolom

Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);
LiquidCrystal_I2C lcd(0x27, 16, 2); // alamat I2C 0x27, 16 kolom dan 2 baris

int cursorColumn = 0;

void setup() {
    lcd.init(); // inisialisasi LCD
    lcd.backlight(); // nyalakan lampu latar
}

void loop() {
    char key = keypad.getKey();

    if (key) {
        lcd.setCursor(cursorColumn, 0); // pindahkan kursor ke posisi (cursorColumn, 0)
        lcd.print(key); // cetak tombol yang ditekan di posisi (cursorColumn, 0)
        
        cursorColumn++; // pindahkan kursor ke posisi berikutnya

        // jika mencapai batas, hapus layar LCD
        if (cursorColumn == 16) {
            lcd.clear();
            cursorColumn = 0;
        }
    }
}
