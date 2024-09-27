#include <LiquidCrystal_I2C.h>
#define NUM_LEDS 6
int ledPins[NUM_LEDS] = {7, 6, 5, 4, 3, 2};

const int trigPin = 9; 
const int echoPin = 8;
int diameter = 17;
float duration, volume, distance, tinggi;
int levelPercent, radian;
int phi = 3.14;
int buzzer = 10;

LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(ledPins[i], OUTPUT);}
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
}

void loop() {
  //pembacaan sensor ultrasonic
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = 16-((duration * 0.0343) / 2); // rumus jarak ketika titik awal 16 cm
  levelPercent = map(distance, 0, 13, 0, 100); //0 tinggi awal wadah 13 tinggi akhir wadah. 0, 100 nilai percentase
  //Kondisi nilai percent tidak melebihi 100%
  if (levelPercent > 100) {
    levelPercent = 100;
  }
  radian = diameter / 2;
  tinggi = distance;
  volume = (phi * radian * radian * tinggi)/1000; //dalam satuan liter
  //menampilkan hasil pada serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println("cm");
  Serial.print("level bensin: ");
  Serial.print(levelPercent);
  Serial.println("%");
  Serial.print("volume: ");
  Serial.print(volume);
  Serial.println("L");
  //menampilkan hasil di LCD
  lcd.setCursor(0, 0);
  lcd.print("Lvl Bensin:");
  lcd.setCursor(12, 0);
  lcd.print(levelPercent);
  lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print("Vol Bensin:");
  lcd.setCursor(11, 1);
  lcd.print(volume);
  lcd.print("L");

  int num_leds_on = map(levelPercent, 0, 90, 1, 6);
    
    // Nyalakan LED sesuai dengan jumlah yang ditentukan
    for (int i = 0; i < 6; i++) {
      if (i < num_leds_on) {
        digitalWrite(ledPins[i], HIGH);
      } else {
        digitalWrite(ledPins[i], LOW);
      }
    }
  //kondisi ketika tangki di bawah 15% Buzzer menyala
  if (levelPercent <= 15){
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
  }
  else{
    digitalWrite(buzzer, LOW);
  }
  delay(500);
  lcd.clear();
}