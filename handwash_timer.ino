#include <Servo.h>

#define TRIG_PIN 5
#define ECHO_PIN 18
#define BUZZER 12
#define SERVO_PIN 13

Servo myServo;

long duration;
int distance;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER, OUTPUT);

  myServo.attach(SERVO_PIN);
  myServo.write(0);  // initial position

  Serial.begin(115200);
}

void loop() {
  // Trigger ultrasonic
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2;

  Serial.println(distance);

  // If hand detected within 10 cm
  if (distance > 0 && distance < 10) {
    startTimer();
    delay(2000); // prevent retrigger
  }
}

void startTimer() {
  Serial.println("Hand detected! Starting timer...");

  // Move servo (start washing indication)
  myServo.write(90);

  // 10-second countdown
  for (int i = 10; i > 0; i--) {
    Serial.println(i);
    delay(1000);
  }

  // Stop servo
  myServo.write(0);

  // Buzzer beep
  digitalWrite(BUZZER, HIGH);
  delay(1000);
  digitalWrite(BUZZER, LOW);

  Serial.println("Done!");
}