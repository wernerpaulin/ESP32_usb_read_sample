#include <HardwareSerial.h>
#include <Arduino.h>
#include <ESP32Servo.h>

Servo sorterServo;

// ===== CONFIG =====
const int SERVO_PIN = 19;
const int LED_PIN = 18;        // Test-LED Pin

const int IDLE_ANGLE = 10;     
const int BIN_1_ANGLE = 50;    
const int BIN_2_ANGLE = 110;   
const int BIN_3_ANGLE = 155;

const int SERVO_AUTO_RETURN_TIME_MS = 6000;
// ==================

unsigned long moveTime = 0;
bool waitingToReturn = false;

// Led Blinking
unsigned long previousMillisLed = 0;
const long ledInterval = 500;  
bool ledState = LOW;

void moveServoTo(int angle) {
  sorterServo.write(angle);
  moveTime = millis();
  waitingToReturn = true;
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  // init LED
  pinMode(LED_PIN, OUTPUT);

  // Servo Setup
  ESP32PWM::allocateTimer(0);
  sorterServo.setPeriodHertz(50);
  sorterServo.attach(SERVO_PIN, 500, 2400);

  // Start position
  sorterServo.write(IDLE_ANGLE);
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillisLed >= ledInterval) {
    previousMillisLed = currentMillis;
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
  }

  // serial commands
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim(); 

    if (cmd == "BIN_1") {
      moveServoTo(BIN_1_ANGLE);
    } 
    else if (cmd == "BIN_2") {
      moveServoTo(BIN_2_ANGLE);
    } 
    else if (cmd == "BIN_3") {
      moveServoTo(BIN_3_ANGLE);
    } 
    else if (cmd != "") {
    }
  }

  // --- AUTO RETURN NACH 6s ---
  if (waitingToReturn && currentMillis - moveTime >= SERVO_AUTO_RETURN_TIME_MS) {
    waitingToReturn = false;
    sorterServo.write(IDLE_ANGLE);
  }
}