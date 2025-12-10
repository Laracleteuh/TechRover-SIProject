// -- THIS IS A BETA VERSION WITH SERVO STEERING -- //
// -- PLEASE TEST AND REPORT ANY ISSUES -- //

#include <Servo.h>  // Include the servo library

// --- PIN DEFINITIONS ---
// Motor A (Left)
const int enA = 10; 
const int in1 = 8;
const int in2 = 7;

// Motor B (Right)
const int enB = 9;  
const int in3 = 6;
const int in4 = 5;

// Receiver
const int rxSpeedPin = 2;    // Channel 1 (Throttle)
const int rxSteeringPin = 3; // Channel 2 (Steering)

// Servo
const int servoPin = 11;     // NEW: Servo on Pin 11

// --- CONFIGURATION ---
const int rxMin = 1000;      
const int rxMax = 2000;
const int rxCenter = 1500;   
const int deadzone = 30;

// Create Servo Object
Servo myServo;

void setup() {
  // Motor Pins
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Receiver Pins
  pinMode(rxSpeedPin, INPUT);
  pinMode(rxSteeringPin, INPUT);

  // Attach Servo
  myServo.attach(servoPin); // Attaches the servo on pin 11

  Serial.begin(9600);
}

void loop() {
  // 1. Read the raw signals from the receiver
  int speedRaw = pulseIn(rxSpeedPin, HIGH);
  int steeringRaw = pulseIn(rxSteeringPin, HIGH);

  // Safety: If transmitter is off (0 signal), stop everything
  if (speedRaw == 0 && steeringRaw == 0) {
    stopMotors();
    return;
  }

  // 2. Convert Raw RC signals to usable values
  int throttle = rcToSpeed(speedRaw);   // Returns -255 to 255
  int steering = rcToSpeed(steeringRaw); // Returns -255 to 255

  // --- SERVO CONTROL ---
  // Convert the steering Raw signal (1000-2000) directly to Servo Angle (0-180)
  // 1000us -> 0 deg (Full Right/Left)
  // 1500us -> 90 deg (Center)
  // 2000us -> 180 deg (Full Left/Right)
  int servoAngle = map(constrain(steeringRaw, rxMin, rxMax), rxMin, rxMax, 0, 180);
  myServo.write(servoAngle);

  // 3. THE DIFFERENTIAL MIXING ALGORITHM
  // Mix Throttle + Steering for the rear motors
  int motorALeft = throttle + steering;
  int motorBRight = throttle - steering;

  // 4. Constraint check
  motorALeft = constrain(motorALeft, -255, 255);
  motorBRight = constrain(motorBRight, -255, 255);

  // 5. Send commands to motors
  setMotor(1, motorALeft);
  setMotor(2, motorBRight);
  
  // Debugging
  // Serial.print(" S_Raw:"); Serial.print(steeringRaw);
  // Serial.print(" Angle:"); Serial.println(servoAngle);
}

// --- HELPER FUNCTIONS ---

int rcToSpeed(int rawValue) {
  if (rawValue < 500) return 0;
  if (abs(rawValue - rxCenter) < deadzone) return 0;
  return map(rawValue, rxMin, rxMax, -255, 255);
}

void setMotor(int motorID, int speed) {
  int pinIn1, pinIn2, pinEn;
  if (motorID == 1) { 
    pinIn1 = in1; pinIn2 = in2; pinEn = enA;
  } else {            
    pinIn1 = in3; pinIn2 = in4; pinEn = enB;
  }

  if (speed > 0) {
    digitalWrite(pinIn1, HIGH);
    digitalWrite(pinIn2, LOW);
    analogWrite(pinEn, speed);
  } else if (speed < 0) {
    digitalWrite(pinIn1, LOW);
    digitalWrite(pinIn2, HIGH);
    analogWrite(pinEn, abs(speed));
  } else {
    digitalWrite(pinIn1, LOW);
    digitalWrite(pinIn2, LOW);
    analogWrite(pinEn, 0);
  }
}

void stopMotors() {
  setMotor(1, 0);
  setMotor(2, 0);
}
