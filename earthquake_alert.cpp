// กำหนดค่าคงที่สำหรับ Blynk
#define BLYNK_TEMPLATE_ID "TMPL68bSOFBnW"
#define BLYNK_TEMPLATE_NAME "earthquake alert"
#define BLYNK_AUTH_TOKEN "OJxdnK-ub-ZZ6af0c_k6atv2lZZK3Xam"

// แสดงข้อความ debug ผ่าน Serial Monitor
#define BLYNK_PRINT Serial

// เรียกใช้ไลบรารีที่จำเป็นสำหรับการเชื่อมต่อ WiFi และ Blynk
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// ข้อมูลการเชื่อมต่อ WiFi
char ssid[] = ""; //ชื่อ WiFi
char pass[] = ""; //รหัส WiFi

// ตัวแปรสำหรับจับเวลาในการทำงานซ้ำ ๆ
BlynkTimer timer;

// กำหนดขาของเซนเซอร์ตรวจจับแรงสั่นสะเทือน (ต่อที่ขา A0 บน NodeMCU)
const int vibrationPin = A0;

// กำหนดหมายเลขขาเสมือนใน Blynk (V1 สำหรับส่งค่าความสั่น)
#define VIRTUAL_PIN_VIBRATION  V1

// ค่าระดับแรงสั่นที่ถือว่า "ตรวจพบแผ่นดินไหว"
const int threshold = 500;

// ฟังก์ชันต้นแบบสำหรับตรวจสอบแรงสั่น
void checkVibration();

void setup() {
  // เริ่มต้น Serial Monitor ที่ baud rate 115200
  Serial.begin(115200);

  // เริ่มต้นการเชื่อมต่อกับ Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // ตั้งค่าขาเซนเซอร์เป็นอินพุต
  pinMode(vibrationPin, INPUT);

  // ตั้งเวลาทำงานของฟังก์ชันตรวจจับแรงสั่นทุก ๆ 1 วินาที
  timer.setInterval(1000, checkVibration);
}

void loop() {
  // ทำงานของ Blynk
  Blynk.run();

  // ทำงานของ Timer
  timer.run();
}

// ฟังก์ชันตรวจสอบแรงสั่นสะเทือน
void checkVibration() {
  // อ่านค่าจากเซนเซอร์แรงสั่น
  int vibrationValue = analogRead(vibrationPin);

  // ส่งค่าที่อ่านได้ไปยังแอป Blynk ที่ขา V1
  Blynk.virtualWrite(VIRTUAL_PIN_VIBRATION, vibrationValue);

  // ถ้ามีแรงสั่นเกินค่าที่กำหนด
  if (vibrationValue > threshold) { 
    Serial.println("Vibration detected!");  // แสดงผลทาง Serial
    Blynk.logEvent("earthquake_alert", "Earthquake Detected!"); // แจ้งเตือนผ่าน Blynk Event
    Serial.println("Sending Complete");
  }
  else {
    Serial.println("Vibration not detected!"); // กรณีไม่มีแรงสั่น
  }
}
