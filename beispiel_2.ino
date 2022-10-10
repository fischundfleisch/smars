// Allein für diesen Zustand verantwortlich: KSMA

const int TRIGGER_PIN = 8;
const int ECHO_PIN = 9;

const int LEFT_MOTOR_F_PIN = 2; // must be a PWM pin, F = forward
const int LEFT_MOTOR_R_PIN = 3; // r = reverse, the motor shield must be a h bridge

const int RIGHT_MOTOR_F_PIN = 4;
const int RIGHT_MOTOR_R_PIN = 5;

const int LEFT_MOTOR_SPEED_PIN = 10;     // Pin for speed, off and on
const int RIGHT_MOTOR_SPEED_PIN = 11;

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
  
  pinMode(LEFT_MOTOR_F_PIN, OUTPUT);
  pinMode(LEFT_MOTOR_R_PIN, OUTPUT);
  pinMode(LEFT_MOTOR_SPEED_PIN, OUTPUT);
  
  pinMode(RIGHT_MOTOR_SPEED_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_F_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_R_PIN, OUTPUT);
  
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

void forward(int speed) {                           // mit forward(100) in der loop übergeben wir dieser Funktion den Parameter speed. 
  analogWrite(LEFT_MOTOR_SPEED_PIN, speed);         
  analogWrite(RIGHT_MOTOR_SPEED_PIN, speed);

  digitalWrite(LEFT_MOTOR_F_PIN, HIGH);             // hier definieren wir die Fahrtrichtung: forwards high, reverse low = vorwärts
  digitalWrite(LEFT_MOTOR_R_PIN, LOW);

  digitalWrite(RIGHT_MOTOR_F_PIN, HIGH);
  digitalWrite(RIGHT_MOTOR_R_PIN, LOW);
  Serial.println(speed);
}

void total_stop() {   //hier müssen wir keine flexiblen Parameter übergeben, hier wird der Motor ganz angehalten
  digitalWrite(LEFT_MOTOR_SPEED_PIN, LOW);
  digitalWrite(RIGHT_MOTOR_SPEED_PIN, LOW);

  digitalWrite(LEFT_MOTOR_F_PIN, LOW);      // alles vom linken Motor ausschalten
  digitalWrite(LEFT_MOTOR_R_PIN, LOW);

  digitalWrite(RIGHT_MOTOR_F_PIN, LOW);     // alles vom rechten Motor ausschalten
  digitalWrite(RIGHT_MOTOR_R_PIN, LOW);
}

void turn_right(int speed) {   // wenn ich nach rechts will, muss der LINKE Motor vorwärts drehen. zusätzlich kann man den rechten Motor rückwärts drehen lassen, muss man aber nicht
  analogWrite(LEFT_MOTOR_SPEED_PIN, speed);
  digitalWrite(RIGHT_MOTOR_SPEED_PIN, LOW);

  digitalWrite(LEFT_MOTOR_F_PIN, HIGH);
  digitalWrite(LEFT_MOTOR_R_PIN, LOW);

  digitalWrite(RIGHT_MOTOR_F_PIN, LOW);
  digitalWrite(RIGHT_MOTOR_R_PIN, LOW);
  Serial.println("Drehe rechts");
}

void loop() {

  int distance = get_distance();
  Serial.println(distance);

  if (distance > 10) {
    forward(100);
  }
  else if (distance <= 10) {
    Serial.println("Ausweichen!!!");
    total_stop();
    turn_right(50);
  }

   delay(1000);
}



