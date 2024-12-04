#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Keypad.h>
// LCD Pin Configuration
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Keypad Configuration
const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte colPins[COLS]={27,13,23,4};
byte rowPins [ROWS]={33,25,26,14};

// Create an instance of the Keypad class
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

float va, vb, vc, ia, ib, ic;

void calculateVoltageImbalance(float va, float vb, float vc) {
    float averageVoltage = (va + vb + vc) / 3;

    // Menghitung selisih dari rata-rata
    float diffVa = fabs(va - averageVoltage);
    float diffVb = fabs(vb - averageVoltage);
    float diffVc = fabs(vc - averageVoltage);

    // Menghitung ketidakseimbangan sebagai persentase dari rata-rata
    float maxDiff = max(diffVa, max(diffVb, diffVc)); // Selisih maksimum
    float UVpercentage = (maxDiff / averageVoltage) * 100;

    if (averageVoltage != 0) {
        lcd.clear();
        lcd.print("Ketidakseimbangan:");
        lcd.setCursor(0, 1);
        lcd.print(UVpercentage, 3);
        lcd.print("%");
    } else {
        lcd.clear(); 
        lcd.print("Rata-rata nol!");
    }
}

void calculateCurrent(float ia, float ib, float ic) {
    float averageCurrent = (ia + ib + ic) / 3;

    // Menghitung selisih dari rata-rata
    float maxIa = ia - averageCurrent;
    float maxIb = ib - averageCurrent;
    float maxIc = ic - averageCurrent;

   // Menghitung ketidakseimbangan sebagai persentase dari rata-rata
    float maxDiffCu = max(diffIa, max(diffIb, diffIc)); // Selisih maksimum
    float UIpercentage = (maxDiffCu / averageCurrent) * 100;

     if (averageCurrent != 0) {
        lcd.clear();
        lcd.print("Ketidakseimbangan:");
        lcd.setCursor(0, 1);
        lcd.print(UIpercentage, 3);
        lcd.print("%");
    } else {
        lcd.clear(); 
        lcd.print("Rata-rata nol!");
    }
}

void setup() {
    Serial.begin(115200); // Pindahkan ke sini
    Wire.begin(21, 22);
    lcd.init();
    lcd.backlight();
    lcd.setCursor(1,1);
    lcd.print("Selamat Datang!");
    delay(2000);
    lcd.clear();
    lcd.print("Silahkan pilih :");
    delay(2000);
    
}

void loop() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("1. Tegangan");
    lcd.setCursor(0, 1);
    lcd.print("2. Arus");
    delay(100); 
    char key = keypad.getKey();
    
    if (key) {
        lcd.clear(); // Bersihkan tampilan sebelum menampilkan input
        if (key == '1') { // Bandingkan dengan karakter
            lcd.print("Input Tegangan:");
            delay(1000);
            lcd.clear();

            // Input tegangan
            lcd.print("VA: ");
            va = getFloatInput();
            lcd.clear();
            lcd.print("VB: ");
            vb = getFloatInput();
            lcd.clear();
            lcd.print("VC: ");
            vc = getFloatInput();
            calculateVoltageImbalance(va, vb, vc);
            delay(3000);
            lcd.clear();
        } else if (key == '2') { // Bandingkan dengan karakter
            lcd.print("Input Arus:");
            delay(1000);
            lcd.clear();

            // Input arus
            lcd.print("IA: ");
            ia = getFloatInput();
            lcd.clear();
            lcd.print("IB: ");
            ib = getFloatInput();
            lcd.clear();
            lcd.print("IC: ");
            ic = getFloatInput();
            calculateCurrent(ia, ib, ic);
            delay(3000);
            lcd.clear();
        } else {
            lcd.clear();
            lcd.print("Menu tidak valid");
            delay(2000);
            lcd.clear();
        }
    }
}

float getFloatInput() {
    String input = "";
    char key;
    lcd.setCursor(0, 1); // Set cursor to the second line for input display

    while (true) {
        key = keypad.getKey();
        
        if (key) {
            if (key == '#') { // Tombol '#' untuk menyelesaikan input
                break; // Keluar dari loop
            } else if (key == '*') { // Tombol '*' untuk menghapus karakter terakhir
                if (input.length() > 0) {
                    input.remove(input.length() - 1); // Hapus karakter terakhir
                    lcd.clear();
                    lcd.print("Input: ");
                    lcd.print(input); // Tampilkan input yang diperbarui
                }
            } else {
                input += key; // Tambahkan karakter ke input
                lcd.clear();
                lcd.print("Input: ");
                lcd.print(input); // Tampilkan input
            }
        }
    }

    return input.toFloat(); // Kembalikan input sebagai float
}