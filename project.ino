#include <DHT.h>
#define DHTPIN A3
#define DHTTYPE DHT11
#include <Servo.h> 
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
 
Servo Servo1;
Servo Servo2; 
DHT dht(DHTPIN, DHTTYPE);

int lightSensor = A0;
int lightValue = 0;
int ledPinR = 7;
int ledPinG = 6;
int servoPin1 = 9;
int servoPin2 = 10; 
LiquidCrystal_I2C lcd(0x27, 16, 2); 

void setup() {
 
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  Servo1.attach(servoPin1);
  Servo2.attach(servoPin2); 
  pinMode(ledPinR, OUTPUT);
  pinMode(ledPinG, OUTPUT);

  dht.begin();
}
void loop() {

  delay(1000);
  float t = dht.readTemperature();
    if (isnan(t)) {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
    }
  Serial.print(F("Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));

  lightValue = analogRead(lightSensor); 
  lightValue = abs(lightValue/10-100);
  Serial.print("Light = ");
  Serial.println(lightValue);
 
  if ((lightValue>95) && (t>25)) {
    Serial.println("Red");
    digitalWrite(ledPinG, LOW);
    digitalWrite(ledPinR, HIGH);
    Servo1.write(180);
    Servo2.write(0); 
    delay(3000);
    Servo1.write(0);
    Servo2.write(180); 
  }

  if ((lightValue<=95) || (t<=25)) {
    Serial.println("Green");
    digitalWrite(ledPinR, LOW);
    digitalWrite(ledPinG, HIGH);
    lcd.setCursor(4, 0); 
    lcd.print("HELLOOO"); 
    lcd.setCursor(3, 1); 
    lcd.print("SAFE PLACE"); 
  }
}
