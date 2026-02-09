#include <Arduino.h>

// LED pins
constexpr int RED_LED    = 25;
constexpr int GREEN_LED  = 26;
constexpr int YELLOW_LED = 27;

void lightLed(int pin) {
  digitalWrite(pin, HIGH);
  delay(400);
  digitalWrite(pin, LOW);
}

void setup() {
  Serial.begin(9600);
  delay(1000);

  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);

  Serial.println("ESP32 ready");
}

void loop() {
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();  // remove \r, spaces, etc.

    if (cmd == "BIN_1") {
      lightLed(RED_LED);
    } 
    else if (cmd == "BIN_2") {
      lightLed(GREEN_LED);
    } 
    else if (cmd == "BIN_3") {
      lightLed(YELLOW_LED);
    } 
    else {
      Serial.print("Unknown command: ");
      Serial.println(cmd);
      lightLed(RED_LED);
    }
  }
}


