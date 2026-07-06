#define BUZZER 5

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <TinyGPS++.h>
#include <HardwareSerial.h>
#include <Wire.h>
#include <math.h>

// ================= WIFI =================
const char* ssid = "YOUR_WIFI";
const char* password = "YOUR_PASSWORD";

// ============== TELEGRAM ================
#define BOT_TOKEN "YOUR_BOT_TOKEN"
#define CHAT_ID "YOUR_CHAT_ID"

WiFiClientSecure client;
UniversalTelegramBot bot(BOT_TOKEN, client);

// ================= GPS ==================
TinyGPSPlus gps;
HardwareSerial gpsSerial(2);

// ================= MPU ==================
#define MPU_ADDR 0x68

int16_t ax, ay, az;
float totalAcc;

// Accident threshold
#define ACC_THRESHOLD 2.5

// Prevent repeated alerts
bool accidentSent = false;

void setup() {

  Serial.begin(115200);
  delay(1000);

  // ================= BUZZER =================
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, LOW);

  Serial.println("🚀 System Starting...");

  // ================= WIFI =================
  WiFi.mode(WIFI_STA);

  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");

  int attempts = 0;

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    attempts++;

    if (attempts > 20) {
      Serial.println("\n❌ Failed to connect!");
      break;
    }
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n✅ Connected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  }

  // Telegram HTTPS fix
  client.setInsecure();

  // ================= MPU9250 INIT =================
  Wire.begin(21, 22);

  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  Serial.println("✅ MPU9250 Initialized");

  // ================= GPS INIT =================
  gpsSerial.begin(9600, SERIAL_8N1, 16, 17);

  Serial.println("✅ GPS Started");
}

void loop() {

  // ============== READ GPS ==============
  while (gpsSerial.available()) {
    gps.encode(gpsSerial.read());
  }

  // ============== READ MPU9250 ==============
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 6, true);

  ax = Wire.read() << 8 | Wire.read();
  ay = Wire.read() << 8 | Wire.read();
  az = Wire.read() << 8 | Wire.read();

  // Convert raw values into g-force
  float accX = ax / 16384.0;
  float accY = ay / 16384.0;
  float accZ = az / 16384.0;

  totalAcc = sqrt(accX * accX + accY * accY + accZ * accZ);

  // Print acceleration
  Serial.print("Total Acceleration: ");
  Serial.println(totalAcc);

  // ============== ACCIDENT DETECTION ==============
  if (totalAcc > ACC_THRESHOLD && !accidentSent) {

    Serial.println("🚨 Accident Detected!");

    // ================= BUZZER ALERT =================
    for (int i = 0; i < 5; i++) {
      digitalWrite(BUZZER, HIGH);
      delay(300);

      digitalWrite(BUZZER, LOW);
      delay(300);
    }

    // ============== GPS CHECK ==============
    if (gps.location.isValid()) {

      float lat = gps.location.lat();
      float lon = gps.location.lng();

      Serial.println("📍 GPS Location Found");

      Serial.print("Latitude: ");
      Serial.println(lat, 6);

      Serial.print("Longitude: ");
      Serial.println(lon, 6);

      // ============== TELEGRAM MESSAGE ==============
      String msg = "🚨 ACCIDENT DETECTED!\n\n";

      msg += "📍 Location:\n";
      msg += "https://maps.google.com/?q=";
      msg += String(lat, 6);
      msg += ",";
      msg += String(lon, 6);

      bool sent = bot.sendMessage(CHAT_ID, msg, "");

      if (sent) {
        Serial.println("✅ Telegram Message Sent!");
      } else {
        Serial.println("❌ Telegram Message Failed!");
      }

    } else {

      Serial.println("❌ GPS Location Not Available");
    }

    accidentSent = true;
  }

  // Reset alert when device becomes stable again
  if (totalAcc < 1.5) {
    accidentSent = false;
  }

  delay(500);
}
