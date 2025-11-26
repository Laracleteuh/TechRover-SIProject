// --- PIN DEFINITIONS ---
// Motor A
const int enA = 10; // PWM pin
const int in1 = 8;
const int in2 = 7;

// Motor B
const int enB = 9;  // PWM pin
const int in3 = 6;
const int in4 = 5;

// Receiver
const int rxPin = 2; // Input from the receiver

// --- CONFIGURATION ---
// Adjust these based on your specific transmitter
const int rxMin = 1000;      // Stick all the way down
const int rxMax = 2000;      // Stick all the way up
const int rxCenter = 1500;   // Stick in the middle
const int deadzone = 30;     // "Wiggle room" for the center stick to ensure motors stop completely

// Variables
int rxValue = 0;             // To store the read value
int motorSpeed = 0;          // Calculated PWM speed (0-255)

void setup() {

  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(rxPin, INPUT);

  Serial.begin(9600);
}

void loop() {
  // 1. Read the pulse width from the receiver

  // pulseIn waits for the pin to go HIGH, starts a timer, waits for LOW, returns microseconds.
  rxValue = pulseIn(rxPin, HIGH);

 
  if (rxValue == 0) {
    stopMotors();
    return;
  }

  // Debugging: Print the raw value to Serial Monitor
  // Serial.print("RX Value: ");
  // Serial.println(rxValue);

  // 2. Determine Direction and Speed
  
  // FORWARD Logic (Stick pushed up)
  if (rxValue > (rxCenter + deadzone)) {
    // Map the RC input (1530 to 2000) to PWM output (0 to 255)
    motorSpeed = map(rxValue, rxCenter + deadzone, rxMax, 0, 255);
    motorSpeed = constrain(motorSpeed, 0, 255); // Ensure we don't go over 255
    moveForward(motorSpeed);
  }
  
  // BACKWARD Logic (Stick pushed down)
  else if (rxValue < (rxCenter - deadzone)) {
    // Map the RC input (1470 to 1000) to PWM output (0 to 255)
    // Note: We map "rxCenter" to 0 and "rxMin" to 255
    motorSpeed = map(rxValue, rxCenter - deadzone, rxMin, 0, 255);
    motorSpeed = constrain(motorSpeed, 0, 255);
    moveBackward(motorSpeed);
  }
  
  // STOP Logic (Stick is in the middle deadzone)
  else {
    stopMotors();
  }
}



void moveForward(int speed) {
  // Motor A Forward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, speed);

  // Motor B Forward
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, speed);
}

void moveBackward(int speed) {
  // Motor A Backward
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, speed);

  // Motor B Backward
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB, speed);
}

void stopMotors() {
  // Turn off enable pins
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  
  // Optional: Set all digital pins LOW
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}// --- PIN DEFINITIONS ---
// Motor A
const int enA = 10; // PWM pin
const int in1 = 8;
const int in2 = 7;

// Motor B
const int enB = 9;  // PWM pin
const int in3 = 6;
const int in4 = 5;

// Receiver
const int rxPin = 2; // Input from the receiver

// --- CONFIGURATION ---
// Adjust these based on your specific transmitter
const int rxMin = 1000;      // Stick all the way down
const int rxMax = 2000;      // Stick all the way up
const int rxCenter = 1500;   // Stick in the middle
const int deadzone = 30;     // "Wiggle room" for the center stick to ensure motors stop completely

// Variables
int rxValue = 0;             // To store the read value
int motorSpeed = 0;          // Calculated PWM speed (0-255)

void setup() {

  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(rxPin, INPUT);

  Serial.begin(9600);
}

void loop() {
  // 1. Read the pulse width from the receiver

  // pulseIn waits for the pin to go HIGH, starts a timer, waits for LOW, returns microseconds.
  rxValue = pulseIn(rxPin, HIGH);

 
  if (rxValue == 0) {
    stopMotors();
    return;
  }

  // Debugging: Print the raw value to Serial Monitor
  // Serial.print("RX Value: ");
  // Serial.println(rxValue);

  // 2. Determine Direction and Speed
  
  // FORWARD Logic (Stick pushed up)
  if (rxValue > (rxCenter + deadzone)) {
    // Map the RC input (1530 to 2000) to PWM output (0 to 255)
    motorSpeed = map(rxValue, rxCenter + deadzone, rxMax, 0, 255);
    motorSpeed = constrain(motorSpeed, 0, 255); // Ensure we don't go over 255
    moveForward(motorSpeed);
  }
  
  // BACKWARD Logic (Stick pushed down)
  else if (rxValue < (rxCenter - deadzone)) {
    // Map the RC input (1470 to 1000) to PWM output (0 to 255)
    // Note: We map "rxCenter" to 0 and "rxMin" to 255
    motorSpeed = map(rxValue, rxCenter - deadzone, rxMin, 0, 255);
    motorSpeed = constrain(motorSpeed, 0, 255);
    moveBackward(motorSpeed);
  }
  
  // STOP Logic (Stick is in the middle deadzone)
  else {
    stopMotors();
  }
}



void moveForward(int speed) {
  // Motor A Forward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, speed);

  // Motor B Forward
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, speed);
}

void moveBackward(int speed) {
  // Motor A Backward
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, speed);

  // Motor B Backward
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB, speed);
}

void stopMotors() {
  // Turn off enable pins
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  
  // Optional: Set all digital pins LOW
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
