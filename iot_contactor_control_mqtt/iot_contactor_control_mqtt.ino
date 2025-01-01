#include <PubSubClient.h>
#include "NetworkHelpers.h"
#include <WiFiManager.h>  // Library WiFiManager

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

unsigned long previousMillis1 = 0; // Untuk Relay NO1
unsigned long previousMillis2 = 0; // Untuk Relay NO2
unsigned long previousMillis3 = 0; // Untuk Relay NO3
unsigned long previousMillis4 = 0; // Untuk Relay NO4
unsigned long previousMillis5 = 0; // Untuk Relay NC1
unsigned long previousMillis6 = 0; // Untuk Relay NC2
unsigned long previousMillis7 = 0; // Untuk Relay NC3
unsigned long previousMillis8 = 0; // Untuk Relay NC4

const long timeout = 2000;         // Timeout 2 detik

bool relayNO1Active = false;
bool relayNO2Active = false;
bool relayNO3Active = false;
bool relayNO4Active = false;
bool relayNC1Active = false;
bool relayNC2Active = false;
bool relayNC3Active = false;
bool relayNC4Active = false;

// Variabel untuk menyimpan kondisi sebelumnya
int prevState1 = 0;
int prevState2 = 0;
int prevState3 = 0;
int prevState4 = 0;

unsigned long lastWiFiCheckMillis = 0; 
unsigned long lastWiFiFailMillis = 0; 
const unsigned long wifiSetupTimeout = 10000; // Timeout WiFi di setup (10 detik)
const unsigned long wifiReconnectTimeout = 600000; // Timeout WiFi di loop (10 menit)
WiFiManager wifiManager;

// These commands are executed every time
// the device (re)connects to the Blynk Cloud
void mqtt_connected()
{
  // Publish some data
  mqtt.publish("ds/terminal", "Device connected\n");
}

// Handle incoming datastream changes
void mqtt_handler(const String& topic, const String& value)
{
  Serial.print("Got ");       Serial.print(topic);
  Serial.print(", value: ");  Serial.println(value);

  if (topic == "downlink/ds/terminal") {
    String reply = String("Your command: ") + value;
    mqtt.publish("ds/terminal", reply.c_str());
  } else if (topic == "downlink/ds/ON1") {
    Serial.println("Received data for ON1: " + value);
    if (value.toInt() == 1) { // Jika tombol ditekan
      digitalWrite(relayNO1, HIGH);
      relayNO1Active = true;
      previousMillis1 = millis(); // Catat waktu mulai
      Serial.println("Relay NO1 telah aktif");
    }
  } else if (topic == "downlink/ds/ON2") {
    Serial.println("Received data for ON2: " + value);
    if (value.toInt() == 1) { // Jika tombol ditekan
      digitalWrite(relayNO2, HIGH);
      relayNO2Active = true;
      previousMillis2 = millis(); // Catat waktu mulai
      Serial.println("Relay NO1 telah aktif");
    }
  } else if (topic == "downlink/ds/ON3") {
    Serial.println("Received data for ON3: " + value);
    if (value.toInt() == 1) { // Jika tombol ditekan
      digitalWrite(relayNO3, HIGH);
      relayNO3Active = true;
      previousMillis3 = millis(); // Catat waktu mulai
      Serial.println("Relay NO3 telah aktif");
    }
  } else if (topic == "downlink/ds/ON4") {
    Serial.println("Received data for ON4: " + value);
    if (value.toInt() == 1) { // Jika tombol ditekan
      digitalWrite(relayNO4, HIGH);
      relayNO4Active = true;
      previousMillis4 = millis(); // Catat waktu mulai
      Serial.println("Relay NO4 telah aktif");
    }
  } else if (topic == "downlink/ds/OFF1") {
    Serial.println("Received data for OFF1: " + value);
    if (value.toInt() == 1) { // Jika tombol ditekan
      digitalWrite(relayNC1, HIGH);
      relayNC1Active = true;
      previousMillis5 = millis(); // Catat waktu mulai
      Serial.println("Relay NC1 telah aktif");
    }
  } else if (topic == "downlink/ds/OFF2") {
    Serial.println("Received data for OFF2: " + value);
    if (value.toInt() == 1) { // Jika tombol ditekan
      digitalWrite(relayNC2, HIGH);
      relayNC2Active = true;
      previousMillis6 = millis(); // Catat waktu mulai
      Serial.println("Relay NC2 telah aktif");
    }
  } else if (topic == "downlink/ds/OFF3") {
    Serial.println("Received data for OFF3: " + value);
    if (value.toInt() == 1) { // Jika tombol ditekan
      digitalWrite(relayNC3, HIGH);
      relayNC3Active = true;
      previousMillis7 = millis(); // Catat waktu mulai
      Serial.println("Relay NC3 telah aktif");
    }
  } else if (topic == "downlink/ds/OFF4") {
    Serial.println("Received data for OFF4: " + value);
    if (value.toInt() == 1) { // Jika tombol ditekan
      digitalWrite(relayNC4, HIGH);
      relayNC4Active = true;
      previousMillis8 = millis(); // Catat waktu mulai
      Serial.println("Relay NC4 telah aktif");
    }
  } else if (topic == "downlink/ds/ALLON") {
    Serial.println("Received data for ALLON: " + value);
    if (value.toInt() == 1) { // Nyalakan semua relay NO
      digitalWrite(relayNO1, HIGH);
      digitalWrite(relayNO2, HIGH);
      digitalWrite(relayNO3, HIGH);
      digitalWrite(relayNO4, HIGH);
      relayNO1Active = relayNO2Active = relayNO3Active = relayNO4Active = true;
      previousMillis1 = previousMillis2 = previousMillis3 = previousMillis4 = millis();
      Serial.println("Semua relay NO telah aktif");
    }
  } else if (topic == "downlink/ds/ALLOFF") {
    Serial.println("Received data for ALLOFF: " + value);
    if (value.toInt() == 1) { // Nyalakan semua relay NC
      digitalWrite(relayNC1, HIGH);
      digitalWrite(relayNC2, HIGH);
      digitalWrite(relayNC3, HIGH);
      digitalWrite(relayNC4, HIGH);
      relayNC1Active = relayNC2Active = relayNC3Active = relayNC4Active = true;
      previousMillis5 = previousMillis6 = previousMillis7 = previousMillis8 = millis();
      Serial.println("Semua relay NC telah aktif");
    }
  }
}

void sendSensorData()
{
  EVERY_N_MILLIS(1000) {
    // Membaca kondisi saat ini
    int state1 = digitalRead(sensor1);
    int state2 = digitalRead(sensor2);
    int state3 = digitalRead(sensor3);
    int state4 = digitalRead(sensor4);

    // Periksa perubahan kondisi sensor 1
    if (state1 != prevState1) {
      mqtt.publish("ds/V9", String(state1).c_str());
      Serial.println(state1 == HIGH ? "Status Detektor 1 = Ada Tegangan" : "Status Detektor 1 = Tidak Ada Tegangan");
      prevState1 = state1; // Perbarui kondisi sebelumnya
    }

    // Periksa perubahan kondisi sensor 2
    if (state2 != prevState2) {
      mqtt.publish("ds/V10", String(state2).c_str());
      Serial.println(state2 == HIGH ? "Status Detektor 2 = Ada Tegangan" : "Status Detektor 2 = Tidak Ada Tegangan");
      prevState2 = state2; // Perbarui kondisi sebelumnya
    }

    // Periksa perubahan kondisi sensor 3
    if (state3 != prevState3) {
      mqtt.publish("ds/V11", String(state3).c_str());
      Serial.println(state3 == HIGH ? "Status Detektor 3 = Ada Tegangan" : "Status Detektor 3 = Tidak Ada Tegangan");
      prevState3 = state3; // Perbarui kondisi sebelumnya
    }

    // Periksa perubahan kondisi sensor 4
    if (state4 != prevState4) {
      mqtt.publish("ds/V12", String(state4).c_str());
      Serial.println(state4 == HIGH ? "Status Detektor 4 = Ada Tegangan" : "Status Detektor 4 = Tidak Ada Tegangan");
      prevState4 = state4; // Perbarui kondisi sebelumnya
    }
  }
}


// Function to control LED RGB color
void setLedColor(int red, int green, int blue) {
  analogWrite(RED_PIN, red);
  analogWrite(GREEN_PIN, green);
  analogWrite(BLUE_PIN, blue);
}

// Fungsi untuk menangani koneksi WiFi
void connectWiFiWithManager() {
  setLedColor(255, 128, 64); // Set LED to white
  wifiManager.setTimeout(180); // Timeout WiFiManager dalam detik
  if (!wifiManager.autoConnect("Panel Plant 1","12345678")) { // ssid dan password WiFi Manager
    Serial.println("Gagal terhubung! Restart perangkat...");
    ESP.restart();  // Restart jika tidak terkoneksi
  }
  Serial.println("Terhubung ke WiFi!");
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID()); // SSID WiFi
  Serial.print("Password: ");
  Serial.println(WiFi.psk()); // Password WiFi

  SSID = WiFi.SSID();
  PASSWORD = WiFi.psk();
}

void setup()
{
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
  setLedColor(255, 0, 0); // Set LED to red
  
  // Wait for serial monitor, up to 3 seconds
  while (!Serial && (millis() < 3000)) { delay(10); }
  delay(100);
  
  systemShowDeviceInfo();
  // Jika gagal, jalankan WiFiManager
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("\nKoneksi WiFi gagal. Masuk ke WiFiManager.");
    connectWiFiWithManager();
  }

  // Set warna ke biru setelah terkoneksi ke WiFi
  setLedColor(0, 0, 255); // Set LED to blue

}

void loop()
{
  // Cek status WiFi setiap detik
  if (millis() - lastWiFiCheckMillis >= 1000) {
    lastWiFiCheckMillis = millis();

    if (WiFi.status() != WL_CONNECTED) {
      // Jika WiFi gagal, hitung waktu gagal
      if (lastWiFiFailMillis == 0) {
        lastWiFiFailMillis = millis(); // Catat waktu gagal pertama
      } else if (millis() - lastWiFiFailMillis >= wifiReconnectTimeout) {
        // Jika gagal lebih dari 2 menit, jalankan WiFiManager
        Serial.println("Koneksi WiFi terputus terlalu lama. Masuk ke WiFiManager.");
        connectWiFiWithManager();
      }
    } else {
      lastWiFiFailMillis = 0; // Reset waktu gagal jika koneksi berhasil
    }
  }
  
  unsigned long currentMillis = millis();

  // Timer untuk Relay NO1
  if (relayNO1Active && (currentMillis - previousMillis1 >= timeout)) {
    digitalWrite(relayNO1, LOW);
    relayNO1Active = false; // Matikan status aktif
    Serial.println("Relay NO1 telah dimatikan setelah 2 detik");
  }

  // Timer untuk Relay NO2
  if (relayNO2Active && (currentMillis - previousMillis2 >= timeout)) {
    digitalWrite(relayNO2, LOW);
    relayNO2Active = false; // Matikan status aktif
    Serial.println("Relay NO2 telah dimatikan setelah 2 detik");
  }

  // Timer untuk Relay NO3
  if (relayNO3Active && (currentMillis - previousMillis3 >= timeout)) {
    digitalWrite(relayNO3, LOW);
    relayNO3Active = false; // Matikan status aktif
    Serial.println("Relay NO3 telah dimatikan setelah 2 detik");
  }

  // Timer untuk Relay NO4
  if (relayNO4Active && (currentMillis - previousMillis4 >= timeout)) {
    digitalWrite(relayNO4, LOW);
    relayNO4Active = false; // Matikan status aktif
    Serial.println("Relay NO4 telah dimatikan setelah 2 detik");
  }

  // Timer untuk Relay NC1
  if (relayNC1Active && (currentMillis - previousMillis5 >= timeout)) {
    digitalWrite(relayNC1, LOW);
    relayNC1Active = false; // Matikan status aktif
    Serial.println("Relay NC1 telah dimatikan setelah 2 detik");
  }

  // Timer untuk Relay NC2
  if (relayNC2Active && (currentMillis - previousMillis6 >= timeout)) {
    digitalWrite(relayNC2, LOW);
    relayNC2Active = false; // Matikan status aktif
    Serial.println("Relay NC2 telah dimatikan setelah 2 detik");
  }

  // Timer untuk Relay NC3
  if (relayNC3Active && (currentMillis - previousMillis7 >= timeout)) {
    digitalWrite(relayNC3, LOW);
    relayNC3Active = false; // Matikan status aktif
    Serial.println("Relay NC3 telah dimatikan setelah 2 detik");
  }

  // Timer untuk Relay NC4
  if (relayNC4Active && (currentMillis - previousMillis8 >= timeout)) {
    digitalWrite(relayNC4, LOW);
    relayNC4Active = false; // Matikan status aktif
    Serial.println("Relay NC4 telah dimatikan setelah 2 detik");
  }

  // Pastikan loop untuk MQTT tetap berjalan
  if (WiFi.status() != WL_CONNECTED) {
    // Tidak terhubung WiFi
    setLedColor(255, 0, 0); // Set LED to red
    connectWiFi();
  } else if (!mqtt.connected()) {
    // Set warna ke biru setelah terkoneksi ke WiFi
    setLedColor(0, 0, 255); // Set LED to blue
    connectMQTT();
  } else {
    // Set warna ke hijau setelah terkoneksi ke Blynk
    setLedColor(0, 255, 0); // Set LED to green
    sendSensorData();
    mqtt.loop();
  }

  delay(10); // Hindari menggunakan delay besar pada loop utama
}
