#include <SPI.h>
#include <SD.h>
#include <MFRC522.h>

#define RST 6 
#define SS 7
#define relay A5

MFRC522 rc522(SS, RST);
File file;

void setup() {
  pinMode(relay, OUTPUT);
  Serial.begin(9600);
  while (!Serial)
    ;
  SPI.begin();

  digitalWrite(relay, HIGH);
  if (!SD.begin(A4)) {
    Serial.println("initialization failed!");
  }
  delay(10);
  Serial.println("initialization failed!");
  digitalWrite(relay, LOW);
  delay(100);

  rc522.PCD_Init();
  Serial.println();
}

void loop() {
  MFRC522::MIFARE_Key key;
  if (rc522.PICC_IsNewCardPresent() && rc522.PICC_ReadCardSerial()) {
    Serial.print(F("Card UID:"));
    dump_byte_array(rc522.uid.uidByte, rc522.uid.size);
  }
  delay(80);
}

void dump_byte_array(byte *buffer, byte bufferSize) {
  String buf;
  buf = "";
  for (byte i = 0; i < bufferSize; i++) {
    buf.concat(String(buffer[i] < 0x10 ? " 0" : " "));
    buf.concat(String(buffer[i], HEX));
  }
  rc522.PICC_HaltA();       // Halt PICC
  rc522.PCD_StopCrypto1();  // Stop encryption on PCD
  delay(500);
  wSD(buf);
}

void wSD(String incs) {
  digitalWrite(relay, HIGH);
  delay(500);
  if (!SD.begin(A4)) { Serial.println("initialization failed!"); }

  file = SD.open("absensi.txt", FILE_WRITE);
  if (file) {
    file.println(incs);
    Serial.println(incs);
    Serial.println("Data berhasil ditambahkan");
    // while (file.available()) { Serial.write(file.read()); }
    file.close();
  } else {
    Serial.println("error opening test.txt");
  }
  incs = "";
  digitalWrite(relay, LOW);
  delay(500);
}
