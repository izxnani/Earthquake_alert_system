#define BLYNK_TEMPLATE_ID "TMPL68bSOFBnW"
#define BLYNK_TEMPLATE_NAME "earthquake alert"
#define BLYNK_AUTH_TOKEN "OJxdnK-ub-ZZ6af0c_k6atv2lZZK3Xam"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "Titipus_2Ghz";
char pass[] = "Thitipat_Kab";

BlynkTimer timer;

// Vibration sensor settings (Digital)
const int vibrationPin = A0; // D3 (GPIO0) บน NodeMCU/ESP8266

// Blynk Virtual Pins
#define VIRTUAL_PIN_VIBRATION  V1 
const int threshold = 500;

void checkVibration(); 

void setup() {
  Serial.begin(115200);


  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  pinMode(vibrationPin, INPUT);

  timer.setInterval(1000, checkVibration);
}

void loop() {
  Blynk.run();
  timer.run();
}

void checkVibration() {
  int vibrationValue = analogRead(vibrationPin);

  Blynk.virtualWrite(VIRTUAL_PIN_VIBRATION, vibrationValue);

  if (vibrationValue > threshold) { 
    Serial.println("Vibration detected!");
    Serial.println("wiwi");


    Blynk.logEvent("earthquake_alert", "Earthquake Detected!");
  }
  else{
    Serial.println("hiiiii");
  }
}
