// Allein für diesen Zustand verantwortlich: KSMA


#include <LiquidCrystal.h>

LiquidCrystal lcd(22,23,24,25,26,27);

const int TRIGGER_PIN = 8;
const int ECHO_PIN = 9;

const int LEFT_MOTOR_PIN = 2; // must be a PWM pin
const int RIGHT_MOTOR_PIN = 3;

long duration = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Starten...");
  Serial.println("Roboter mit Ultraschall-Hinderniserkennung");
  Serial.println("Code und Konstruktion: KSMA");
  Serial.println("Version: 1.01");
  Serial.println("Hardware: Joy-it Uno, HC-SR04");


  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  delay(3000);
}

int get_distance() {
  int distance = 0;
  
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration/2) * 0.03432;          // Entfernung in Zentimeter

    return distance;
}

void loop() {

  int distance = get_distance();
  Serial.println(distance);
 
  delay(1000);
  
}



