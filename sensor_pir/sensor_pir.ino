#define Buzzer_PIN A0 
#define pirPin 8  // Pin sensor PIR terhubung ke pin digital 2 pada Arduino
#define RED_PIN 4      // Pin untuk warna merah
#define GREEN_PIN 3    // Pin untuk warna hijau
#define BLUE_PIN 2     // Pin untuk warna biru

unsigned long motionStartTime = 0; // Variabel untuk menyimpan waktu mulai gerakan

void setup() {
  Serial.begin(9600);
  pinMode(pirPin, INPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(Buzzer_PIN, OUTPUT);
  delay(100);
}

void loop() {
  int loopDelay = 1000;
  int motionDetected = digitalRead(pirPin);

  if (motionDetected == HIGH) {
    if (motionStartTime == 0) {
      // Catat waktu mulai gerakan
      motionStartTime = millis();
    }

    unsigned long motionDuration = millis() - motionStartTime;

    delay(4000);
    loopDelay = loopDelay + 4000;
    Serial.println("Gerakan terdeteksi!");
    setRGBColor(255, 0, 0);  // Merah

    if (motionDuration >= 2000) {
      loopDelay = loopDelay + 5000;
      // Durasi gerakan lebih dari 2 detik, bunyikan suara selama 2 detik
      tone(Buzzer_PIN, 4500);
      delay(2000);
      noTone(Buzzer_PIN);
      delay(3000);
    } else {
      // Durasi gerakan kurang dari 2 detik, teruskan bunyikan suara
      tone(Buzzer_PIN, 4500);
      delay(10000);
    }
  } else {
    // Tidak ada gerakan, atur ulang waktu mulai gerakan
    motionStartTime = 0;
    loopDelay = 100;
    noTone(Buzzer_PIN);
    setRGBColor(0, 0, 255);  // Biru
    Serial.println("Tidak ada gerakan.");
  }
  delay(loopDelay);  // Tunggu 1 detik sebelum membaca kembali
}

void setRGBColor(int red, int green, int blue) {
  analogWrite(RED_PIN, red);
  analogWrite(GREEN_PIN, green);
  analogWrite(BLUE_PIN, blue);
}
