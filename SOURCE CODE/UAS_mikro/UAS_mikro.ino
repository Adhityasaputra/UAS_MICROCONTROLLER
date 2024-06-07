#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHT_PIN 7           // Pin data sensor DHT22 terhubung ke pin digital 7
#define RELAY_PIN 8         // Pin relay terhubung ke pin digital 8
#define BUZZER_PIN 9        // Pin buzzer terhubung ke pin digital 9

DHT dht(DHT_PIN, DHT22);    // Inisialisasi sensor DHT22
LiquidCrystal_I2C lcd(0x27, 16, 2); // Inisialisasi LCD 16x2 dengan alamat I2C 0x27

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.init();
  lcd.backlight();
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  float temperature = dht.readTemperature(); // Baca suhu dari sensor DHT22
  float humidity = dht.readHumidity();       // Baca kelembaban dari sensor DHT22

  // Menampilkan suhu dan kelembaban di LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print(" C");

  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.print(" %");

  // Menampilkan suhu dan kelembaban di Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" C, Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Mengontrol relay dan buzzer berdasarkan suhu dan kelembaban
  if (temperature > 28 || humidity > 70) {
    activateAlarm(); // Aktifkan alarm jika suhu atau kelembaban melebihi batas
  } else {
    deactivateAlarm(); // Matikan alarm jika suhu dan kelembaban kembali normal
  }

  delay(2000); // Delay 2 detik untuk mengurangi pembacaan sensor
}

void activateAlarm() {
  Serial.println("Alert! Temperature or humidity exceeds threshold!"); // Tampilkan pesan di Serial Monitor
  digitalWrite(RELAY_PIN, HIGH); // Aktifkan relay
  digitalWrite(BUZZER_PIN, HIGH); // Aktifkan buzzer
}

void deactivateAlarm() {
  digitalWrite(RELAY_PIN, LOW); // Matikan relay
  digitalWrite(BUZZER_PIN, LOW); // Matikan buzzer
}
