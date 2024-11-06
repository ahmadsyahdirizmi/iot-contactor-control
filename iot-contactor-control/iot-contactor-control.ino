#define BLYNK_TEMPLATE_ID "" // Masukkan Template ID dari Blynk
#define BLYNK_TEMPLATE_NAME "" // Masukkan Template Name dari Blynk
#define BLYNK_AUTH_TOKEN "" // Masukkan Auth Token dari Blynk

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

#define relay 2 // Pin untuk permisalan relay start dan stop dengan led D2
BlynkTimer timer;

// Masukkan kredensial WiFi
char ssid[] = "";
char pass[] = "";

void setup() {
  Serial.begin(115200);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, LOW); // Mulai dalam keadaan mati (HIGH berarti relay tidak aktif)

  // Coba untuk terhubung ke Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  
  // Cek status koneksi
  if (Blynk.connected()) {
    Serial.println("Terhubung ke Blynk");
  } else {
    Serial.println("Gagal terhubung ke Blynk");
  }
}

// Fungsi untuk mematikan kontaktor seperti button stop
BLYNK_WRITE(V3) {
  int buttonState = param.asInt();
  if (buttonState == 1) { // Jika tombol ditekan
    digitalWrite(relay, HIGH); // Nyalakan relay
    Blynk.virtualWrite(V0, 0); // Permisalan kontaktor nonaktif
    Serial.println("Relay Stop telah aktif");

    timer.setTimeout(2000L, []() {
      digitalWrite(relay, LOW); // Kembalikan relay ke kondisi semula (OFF)
      Serial.println("Relay Stop telah dimatikan setelah 2 detik");
    });
  }
}

// Fungsi untuk menghidupkan kontaktor seperti button start
BLYNK_WRITE(V4) {
  int buttonState = param.asInt();
  if (buttonState == 1) { // Jika tombol ditekan
    digitalWrite(relay, HIGH); // Matikan relay
    Blynk.virtualWrite(V0, 1); // Permisalan kontaktor aktif
    Serial.println("Relay Start telah aktif");

    timer.setTimeout(2000L, []() {
      digitalWrite(relay, LOW); // Kembalikan relay ke kondisi semula (OFF)
      Serial.println("Relay Start telah dimatikan setelah 2 detik");
    });
  }
}

void loop() {
  Blynk.run(); // Menghandle koneksi Blynk
  timer.run(); // Menghandle fungsi timer
}