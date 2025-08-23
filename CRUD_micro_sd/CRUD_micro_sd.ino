#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int chipSelect = 10;

struct Data {
  int id;
  char name[20];
  char address[50];
};

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Mengakses SD...");
  delay(1000);
  lcd.clear();
  SD.begin(chipSelect);
  createData(1, "John", "Jl. Raya No. 123");
  createData(2, "Jane", "Jl. Raya No. 456");
  createData(3, "Bob", "Jl. Raya No. 789");
  readData(1);
  updateData(2, "Jane Doe", "Jl. Raya No. 789");
  readData(2);
  deleteData(3);
  displayData();
}

void loop() {
  // tidak ada yang dilakukan pada loop
}

void createData(int id, char* name, char* address) {
  File file = SD.open("data.txt", FILE_WRITE);
  if (file) {
    Data data;
    data.id = id;
    strcpy(data.name, name);
    strcpy(data.address, address);
    file.write((uint8_t*)&data, sizeof(Data));
    file.close();
  }
}

void readData(int id) {
  File file = SD.open("data.txt", FILE_READ);
  if (file) {
    while (file.available()) {
      Data data;
      file.read((uint8_t*)&data, sizeof(Data));
      if (data.id == id) {
        lcd.setCursor(0, 0);
        lcd.print("ID: ");
        lcd.print(data.id);
        lcd.setCursor(0, 1);
        lcd.print("Nama: ");
        lcd.print(data.name);
        lcd.setCursor(0, 2);
        lcd.print("Alamat: ");
        lcd.print(data.address);
        delay(3000);
        lcd.clear();
        break;
      }
    }
    file.close();
  }
}

void updateData(int id, char* name, char* address) {
  File file = SD.open("data.txt", FILE_READ);
  if (file) {
    File newFile = SD.open("temp.txt", FILE_WRITE);
    while (file.available()) {
      Data data;
      file.read((uint8_t*)&data, sizeof(Data));
      if (data.id == id) {
        strcpy(data.name, name);
        strcpy(data.address, address);
      }
      newFile.write((uint8_t*)&data, sizeof(Data));
    }
    file.close();
    newFile.close();
    SD.remove("data.txt");
    SD.rename("temp.txt", "data.txt");
  }
}

void deleteData(int id) {
  File file = SD.open("data.txt", FILE_READ);
  if (file) {
    File newFile = SD.open("temp.txt", FILE_WRITE);
    while (file.available()) {
      Data data;
      file.read((uint8_t*)&data, sizeof(Data));
      if (data.id != id) {
        newFile.write((uint8_t*)&data, sizeof(Data));
      }
    }
    file.close();
    newFile.close();
    SD.remove("data.txt");
    SD.rename("temp.txt", "data.txt");
  }
}

void displayData() {
  File file = SD.open("data.txt", FILE_READ);
  if (file) {
    lcd.setCursor(0, 0);
    lcd.print("ID   Nama           ");
    lcd.setCursor(0, 1);
    lcd.print("------------------");
    int row = 2;
    while (file.available()) {
      Data data;
      file.read((uint8_t*)&data, sizeof(Data));
      lcd.setCursor(0, row);
      lcd.print(data.id);
      lcd.setCursor(4, row);
      lcd.print(data.name);
      row++;
      delay(1000);
    }
    file.close();
  }
}