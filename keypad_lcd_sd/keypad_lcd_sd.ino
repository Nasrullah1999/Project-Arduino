#include <Keypad.h>
#include <SPI.h>
#include <SD.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};
byte rowPins[ROWS] = { A0, A1, A2, A3 };
byte colPins[COLS] = { 5,  4,  3,  2 };
char stringAngka[17];
int indexKeypad = 0;

const int cs = 10;
File file;

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.clear();

  Serial.begin(9600);
  Serial.println("Input angka menggunakan keypad");
  Serial.println("https://www.semesin.com/project/");
  Serial.println();

  lcd.begin(16, 2);
  lcd.backlight();
  lcd.print("Input angka");

  while (!Serial) {
    ;
  }
  SPI.begin();
  if (!SD.begin(cs)) {
    Serial.println("SD card tidak terbaca!!");
  } else {
    Serial.println("SD card terbaca!!");
  }
  delay(10);
}

void loop() {
  // bool nilaiTombol = digitalRead(tombol);
  // if (nilaiTombol) {
  //   inputDataSD("Tombol ditekan");
  // }
  // delay(10);

  char key = keypad.getKey();

  if (key) {
    Serial.println(key);
    switch (key) {
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
        if (!indexKeypad) {
          lcd.clear();
        }
        stringAngka[indexKeypad++] = key;
        lcd.print(key);
        break;
      case '*':  //reset
        lcd.clear();
        indexKeypad = 0;
        break;
      case '#':
        stringAngka[indexKeypad] = 0;
        lcd.setCursor(0, 1);

        int nilaiAngka = atoi(stringAngka);
        lcd.print(nilaiAngka);

        indexKeypad = 0;
        break;
    }
  }
}

void inputDataSD(String data) {
  file = SD.open("data.txt", FILE_WRITE);
  if (file) {
    file.println(data);
    Serial.println("Berhasil menyimpan data!!");
    file.close();
  } else {
    Serial.println("Gagal membuka file!!");
  }

  file = SD.open("data.txt");
  if (file) {
    while (file.available()) {
      Serial.write(file.read());
    }
    file.close();
  } else {
    Serial.println("Gagal membuka file!!");
  }
}
