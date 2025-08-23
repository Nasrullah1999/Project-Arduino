#define RED_PIN 4      // Pin untuk warna merah
#define GREEN_PIN 3    // Pin untuk warna hijau
#define BLUE_PIN 2     // Pin untuk warna biru
#define BUZZER_PIN A1  // Pin untuk buzzer

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    int inputNumber = Serial.parseInt();  // Baca angka dari Serial Monitor
    // Panggil fungsi bunyi berdasarkan angka yang dibaca
    switch (inputNumber) {
      case 1:
        bunyi(1);
        break;
      case 2:
        bunyi(2);
        break;
      case 3:
        bunyi(3);
        break;
      case 4:
        bunyi(4);
        break;
      case 5:
        bunyi(5);
        break;
      case 6:
        bunyi(6);
        break;
      case 7:
        bunyi(7);
        break;
      case 8:
        bunyi(8);
        break;
      case 9:
        bunyi(9);
        break;
      case 10:
        bunyi(10);
        break;
    }
  }
}

void bunyi(int beep) {
  switch (beep) {
    case 1:  // system siap
      setRGBColor(0, 255, 0);
      tone(BUZZER_PIN, 2140);  // frekuensi : 2140, ,
      delay(1000);
      noTone(BUZZER_PIN);
      return;
    case 2:
      setRGBColor(255, 0, 0);  // pesan error
      tone(BUZZER_PIN, 2000);  // frekuensi 2000,,,,2200
      delay(1000);
      noTone(BUZZER_PIN);
      return;
    case 3:
      setRGBColor(255, 255, 0);  // menunggu
      tone(BUZZER_PIN, 4040);    //frekuensi :4040, ,
      delay(1000);
      noTone(BUZZER_PIN);
      return;
    case 4:
      setRGBColor(211, 254, 102);  // menunggu
      tone(BUZZER_PIN, 2100);      // frekuensi : 2100,1600
      delay(1000);
      noTone(BUZZER_PIN);
      return;
    case 5:
      tone(BUZZER_PIN, 1700);  //frekuensi : ,1700
      delay(1000);
      noTone(BUZZER_PIN);
      return;
    case 6:
      tone(BUZZER_PIN, 4510);  // frekuensi :,4510,4520
      delay(1000);
      noTone(BUZZER_PIN);
      return;
    case 7:
      tone(BUZZER_PIN, 4500);  // frekuensi :7400,4500,,
      delay(1000);
      noTone(BUZZER_PIN);
      return;
    case 8:
      tone(BUZZER_PIN, 3500);  // frekuensi :,3500,,
      delay(1000);
      noTone(BUZZER_PIN);
      return;
    case 9:
      tone(BUZZER_PIN, 1900);  // frekuensi :,1900,
      delay(1000);
      noTone(BUZZER_PIN);
      return;
    case 10:
      tone(BUZZER_PIN, 4100);  // frekuensi :4100,,
      delay(1000);
      noTone(BUZZER_PIN);
      return;
  }
  return;
}
void setRGBColor(int red, int green, int blue) {
  analogWrite(RED_PIN, red);
  analogWrite(GREEN_PIN, green);
  analogWrite(BLUE_PIN, blue);
}
