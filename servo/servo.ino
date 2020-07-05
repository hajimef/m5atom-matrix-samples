#include "M5Atom.h"
#include <ESP32Servo.h>

#define SERVO_PIN 19

Servo sv;

void setup() {
  M5.begin(true, false, true);
  sv.attach(SERVO_PIN);
}

void loop() {
  sv.write(0);
  delay(1000);
  sv.write(90);
  delay(1000);
  sv.write(180);
  delay(1000);
  sv.write(90);
  delay(1000);
}
