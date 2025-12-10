// --- PIN DEFINITIONS ---
// Motor A
const int enA = 10; 
const int in1 = 8;
const int in2 = 7;

// Motor B
const int enB = 9;  
const int in3 = 6;
const int in4 = 5;

// Receiver
const int rxXPin = 2; // channel 1
const int rxYPin = 3; // channel 2

// --- RECEIVER CONFIGURATION ---
const int rxMin = 1000;      
const int rxMax = 2000;      
const int rxCenter = 1500;   
const int deadzone = 25;     

void setup() {

  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);


  pinMode(rxXPin, INPUT);
  pinMode(rxYPin, INPUT);

  Serial.begin(9600);

}

void loop() {

    int rxXValue = pulseIn(rxXPin, HIGH);
    int rxYValue = pulseIn(rxYPin, HIGH);

    // DEBUG
    //Serial.println(rxXValue);
    //Serial.println(rxYValue);

    if (rxXValue == 0) {
        stopMotors();
        return;
    }

    
    if (rxXValue > (rxCenter + deadzone)) {
        motorSpeed = map(rxXValue, rxCenter + deadzone, rxMax, 0, 255);
        motorSpeed = constrain(motorSpeed, 0, 255);
        moveForward(motorSpeed);
    }

    else if (rxXValue < (rxCenter - deadzone)) {
        motorSpeed = map(rxXValue, rxCenter - deadzone, rxMin, 0, 255);
        motorSpeed = constrain(motorSpeed, 0, 255);
        moveBackward(motorSpeed);
    }

    else {
        stopMotors();
    }
}

void moveForward(int speed) {

    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);

    analogWrite(enA, speed);
    analogWrite(enB, speed);

}

void moveBackward(int speed) {

    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);

    analogWrite(enA, speed);
    analogWrite(enB, speed);

}

void stopMotors() {

    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);

    analogWrite(enA, 0);
    analogWrite(enB, 0);

}


