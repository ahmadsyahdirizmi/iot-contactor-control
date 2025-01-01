#define BLYNK_TEMPLATE_ID "TMPL6tpG4wvsE" // Masukkan Template ID dari Blynk
#define BLYNK_TEMPLATE_NAME "Quickstart Template" // Masukkan Template Name dari Blynk
#define BLYNK_AUTH_TOKEN "R02GVIbevaC3xpZUjPCC7ipG_4QUBLdJ" // Masukkan Auth Token dari Blynk

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

#define relayNO1 14
#define relayNO2 27
#define relayNO3 26
#define relayNO4 25
#define relayNC1 19
#define relayNC2 18
#define relayNC3 17
#define relayNC4 16
#define sensor1 35 // Pin untuk detektor tegangan 1
#define sensor2 34 // Pin untuk detektor tegangan 2
#define sensor3 39 // Pin untuk detektor tegangan 3
#define sensor4 36 // Pin untuk detektor tegangan 4
#define RED_PIN 4    // Pin untuk LED warna merah
#define GREEN_PIN 5  // Pin untuk LED warna hijau
#define BLUE_PIN 23  // Pin untuk LED warna biru

BlynkTimer timer;

// Masukkan kredensial WiFi
char ssid[] = "WINDOWS-S8O1B2H 2221";
char pass[] = "11&2A7r8";

void setup() {
  Serial.begin(115200);
  
  // Inisialisasi pin relay dan sensor tegangan
  pinMode(relayNO1, OUTPUT);
  pinMode(relayNO2, OUTPUT);
  pinMode(relayNO3, OUTPUT);
  pinMode(relayNO4, OUTPUT);
  pinMode(relayNC1, OUTPUT);
  pinMode(relayNC2, OUTPUT);
  pinMode(relayNC3, OUTPUT);
  pinMode(relayNC4, OUTPUT);
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  pinMode(sensor4, INPUT);
  
  // Mulai dalam keadaan mati (relay tidak aktif)
  digitalWrite(relayNO1, LOW);
  digitalWrite(relayNO2, LOW);
  digitalWrite(relayNO3, LOW);
  digitalWrite(relayNO4, LOW);
  digitalWrite(relayNC1, LOW);
  digitalWrite(relayNC2, LOW);
  digitalWrite(relayNC3, LOW);
  digitalWrite(relayNC4, LOW);

  // Inisialisasi pin RGB LED
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  // Set warna awal ke merah
  setRGB(1, 0, 0);

  // Coba untuk terhubung ke WiFi
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Set warna ke biru setelah terkoneksi ke WiFi
  setRGB(0, 0, 1);

  // Coba untuk terhubung ke Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  
  // Cek status koneksi
  if (Blynk.connected()) {
    Serial.println("Terhubung ke Blynk");
    // Set warna ke hijau setelah terkoneksi ke Blynk
    setRGB(0, 1, 0);
  } else {
    Serial.println("Gagal terhubung ke Blynk");
  }

  // Timer untuk memantau tegangan setiap 1 detik
  timer.setInterval(1000L, cekTegangan);
}

// Fungsi untuk mengatur warna RGB
void setRGB(int red, int green, int blue) {
  digitalWrite(RED_PIN, red);
  digitalWrite(GREEN_PIN, green);
  digitalWrite(BLUE_PIN, blue);
}

// Fungsi untuk cek tegangan dari 4 detektor dan kirim data ke Blynk
void cekTegangan() {
  int state1 = digitalRead(sensor1);
  int state2 = digitalRead(sensor2);
  int state3 = digitalRead(sensor3);
  int state4 = digitalRead(sensor4);
  
  // Detektor 1
  Serial.print("Logic Sensor 1 = ");
  Serial.println(state1); 
  if (state1 == HIGH) {
    Serial.println("Status Detektor 1 = Terdeteksi Ada Tegangan");
    Blynk.virtualWrite(V9, 1); // Kirim 1 ke Blynk jika ada tegangan di detektor 1
  } else {
    Serial.println("Status Detektor 1 = Tidak Ada Tegangan");
    Blynk.virtualWrite(V9, 0); // Kirim 0 ke Blynk jika tidak ada tegangan di detektor 1
  }

  // Detektor 2
  Serial.print("Logic Sensor 2 = ");
  Serial.println(state2);
  if (state2 == HIGH) {
    Serial.println("Status Detektor 2 = Terdeteksi Ada Tegangan");
    Blynk.virtualWrite(V10, 1); // Kirim 1 ke Blynk jika ada tegangan di detektor 2
  } else {
    Serial.println("Status Detektor 2 = Tidak Ada Tegangan");
    Blynk.virtualWrite(V10, 0); // Kirim 0 ke Blynk jika tidak ada tegangan di detektor 2
  }

  // Detektor 3
  Serial.print("Logic Sensor 3 = ");
  Serial.println(state3);
  if (state3 == HIGH) {
    Serial.println("Status Detektor 3 = Terdeteksi Ada Tegangan");
    Blynk.virtualWrite(V11, 1); // Kirim 1 ke Blynk jika ada tegangan di detektor 3
  } else {
    Serial.println("Status Detektor 3 = Tidak Ada Tegangan");
    Blynk.virtualWrite(V11, 0); // Kirim 0 ke Blynk jika tidak ada tegangan di detektor 3
  }

  // Detektor 4
  Serial.print("Logic Sensor 4 = ");
  Serial.println(state4);
  if (state4 == HIGH) {
    Serial.println("Status Detektor 4 = Terdeteksi Ada Tegangan");
    Blynk.virtualWrite(V12, 1); // Kirim 1 ke Blynk jika ada tegangan di detektor 4
  } else {
    Serial.println("Status Detektor 4 = Tidak Ada Tegangan");
    Blynk.virtualWrite(V12, 0); // Kirim 0 ke Blynk jika tidak ada tegangan di detektor 4
  }

  Serial.println();
}

// Fungsi untuk menghidupkan kontaktor 1
BLYNK_WRITE(V1) {
  int buttonState = param.asInt();
  if (buttonState == 1) { // Jika tombol ditekan
    digitalWrite(relayNO1, HIGH); // Matikan relay
    Serial.println("Relay NO1 telah aktif");

    timer.setTimeout(2000L, []() {
      digitalWrite(relayNO1, LOW); // Kembalikan relay ke kondisi semula (OFF)
      Serial.println("Relay NO1 telah dimatikan setelah 2 detik");
    });
  }
}

// Fungsi untuk menghidupkan kontaktor 2
BLYNK_WRITE(V2) {
  int buttonState = param.asInt();
  if (buttonState == 1) { // Jika tombol ditekan
    digitalWrite(relayNO2, HIGH); // Matikan relay
    Serial.println("Relay NO2 telah aktif");

    timer.setTimeout(2000L, []() {
      digitalWrite(relayNO2, LOW); // Kembalikan relay ke kondisi semula (OFF)
      Serial.println("Relay NO2 telah dimatikan setelah 2 detik");
    });
  }
}

// Fungsi untuk menghidupkan kontaktor 3
BLYNK_WRITE(V3) {
  int buttonState = param.asInt();
  if (buttonState == 1) { // Jika tombol ditekan
    digitalWrite(relayNO3, HIGH); // Matikan relay
    Serial.println("Relay NO3 telah aktif");

    timer.setTimeout(2000L, []() {
      digitalWrite(relayNO3, LOW); // Kembalikan relay ke kondisi semula (OFF)
      Serial.println("Relay NO3 telah dimatikan setelah 2 detik");
    });
  }
}

// Fungsi untuk menghidupkan kontaktor 4
BLYNK_WRITE(V4) {
  int buttonState = param.asInt();
  if (buttonState == 1) { // Jika tombol ditekan
    digitalWrite(relayNO4, HIGH); // Matikan relay
    Serial.println("Relay NO4 telah aktif");

    timer.setTimeout(2000L, []() {
      digitalWrite(relayNO4, LOW); // Kembalikan relay ke kondisi semula (OFF)
      Serial.println("Relay NO4 telah dimatikan setelah 2 detik");
    });
  }
}

// Fungsi untuk mematikan kontaktor 1
BLYNK_WRITE(V5) {
  int buttonState = param.asInt();
  if (buttonState == 1) { // Jika tombol ditekan
    digitalWrite(relayNC1, HIGH); // Nyalakan relay
    Serial.println("Relay NC1 telah aktif");

    timer.setTimeout(2000L, []() {
      digitalWrite(relayNC1, LOW); // Kembalikan relay ke kondisi semula (OFF)
      Serial.println("Relay NC1 telah dimatikan setelah 2 detik");
    });
  }
}

// Fungsi untuk mematikan kontaktor 2
BLYNK_WRITE(V6) {
  int buttonState = param.asInt();
  if (buttonState == 1) { // Jika tombol ditekan
    digitalWrite(relayNC2, HIGH); // Nyalakan relay
    Serial.println("Relay NC2 telah aktif");

    timer.setTimeout(2000L, []() {
      digitalWrite(relayNC2, LOW); // Kembalikan relay ke kondisi semula (OFF)
      Serial.println("Relay NC2 telah dimatikan setelah 2 detik");
    });
  }
}

// Fungsi untuk mematikan kontaktor 3
BLYNK_WRITE(V7) {
  int buttonState = param.asInt();
  if (buttonState == 1) { // Jika tombol ditekan
    digitalWrite(relayNC3, HIGH); // Nyalakan relay
    Serial.println("Relay NC3 telah aktif");

    timer.setTimeout(2000L, []() {
      digitalWrite(relayNC3, LOW); // Kembalikan relay ke kondisi semula (OFF)
      Serial.println("Relay NC3 telah dimatikan setelah 2 detik");
    });
  }
}

// Fungsi untuk mematikan kontaktor 4
BLYNK_WRITE(V8) {
  int buttonState = param.asInt();
  if (buttonState == 1) { // Jika tombol ditekan
    digitalWrite(relayNC4, HIGH); // Nyalakan relay
    Serial.println("Relay NC4 telah aktif");

    timer.setTimeout(2000L, []() {
      digitalWrite(relayNC4, LOW); // Kembalikan relay ke kondisi semula (OFF)
      Serial.println("Relay NC4 telah dimatikan setelah 2 detik");
    });
  }
}

void loop() {
  // Pengecekan koneksi WiFi dan Blynk
  if (WiFi.status() != WL_CONNECTED) {
    // Tidak terhubung WiFi
    setRGB(1, 0, 0);
  } else if (!Blynk.connected()) {
    // Set warna ke biru setelah terkoneksi ke WiFi
    setRGB(0, 0, 1);
  } else {
    // Set warna ke hijau setelah terkoneksi ke Blynk
    setRGB(0, 1, 0);
  }
  
  Blynk.run(); // Menghandle koneksi Blynk
  timer.run(); // Menghandle fungsi timer
}
