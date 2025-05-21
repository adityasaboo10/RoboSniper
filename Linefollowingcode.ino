// Pin definitions
#define LS 11  // Left sensor pin
#define CS 12       // Center sensor pin
#define RS 13       // Right sensor pin
#define LM1 6     // Motor driver IN1 (left motor control)
#define LM2 7      // Motor driver IN2 (left motor control)
#define RM1 4      // Motor driver IN3 (right motor control)
#define RM2 5      // Motor driver IN4 (right motor control)
#define ENA 9     // PWM control for left motor
#define ENB 3   // PWM control for right motor

int last_direction = 0; // 0: straight, 1: right, -1: left

// Set motor speed
int motorSpeed = 100;  // Reduced for smooth following

void setup() {
    pinMode(LS, INPUT);
    pinMode(CS, INPUT);
    pinMode(RS, INPUT);
    pinMode(LM1, OUTPUT);
    pinMode(LM2, OUTPUT);
    pinMode(RM1, OUTPUT);
    pinMode(RM2, OUTPUT);
    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);

    analogWrite(ENA, motorSpeed);
    analogWrite(ENB, motorSpeed);
}

void loop() {
    bool leftSensor = digitalRead(LS);  
    bool centerSensor = digitalRead(CS);
    bool rightSensor = digitalRead(RS);

    // Movement based on sensor readings
    if (centerSensor && !leftSensor && !rightSensor) {  
        moveForward();  
        last_direction = 0;
    } 
    else if (leftSensor && !centerSensor && !rightSensor) {  
        turnSlightRight();  
        last_direction = 1;
    } 
    else if (!leftSensor && !centerSensor && rightSensor) {  
        turnSlightLeft();  
        last_direction = -1;
    } 
    else if (leftSensor && centerSensor && !rightSensor) {  
        turnSharpRight();  
        last_direction = 1;
    } 
    else if (!leftSensor && centerSensor && rightSensor) {  
        turnSharpLeft();  
        last_direction = -1;
    } 
    else if (!leftSensor && !centerSensor && !rightSensor) { // all sensors off (gap!)
        if (last_direction == -1) {
            turnSharpLeft();
        } else if (last_direction == 1) {
            turnSharpRight();
        } else {
            moveForward();
        }
    } 
    else if (leftSensor && centerSensor && rightSensor) { // all sensors on (intersection or wide line)
       if (last_direction == -1) {
            turnSharpLeft();
        } else if (last_direction == 1) {
            turnSharpRight();
        } else {
            moveForward();
        }
    } 
    else {  
        stopMotors();  
    }

    delay(10);  // Small delay for sensor stability
}

// Movement functions
void moveForward() {
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
    analogWrite(ENA, motorSpeed);
    analogWrite(ENB, motorSpeed);
}

void moveBackward() {
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, HIGH);
    analogWrite(ENA, motorSpeed);
    analogWrite(ENB, motorSpeed);
}

void turnSlightLeft() {
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, HIGH);
    analogWrite(ENA, motorSpeed / 2); // left wheel slower
    analogWrite(ENB, motorSpeed);
}

void turnSlightRight() {
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
    analogWrite(ENA, motorSpeed);
    analogWrite(ENB, motorSpeed / 2); // right wheel slower
}

void turnSharpLeft() {
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, HIGH);
    analogWrite(ENA, motorSpeed);
    analogWrite(ENB, motorSpeed);
}

void turnSharpRight() {
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
    analogWrite(ENA, motorSpeed);
    analogWrite(ENB, motorSpeed);
}

void stopMotors() {
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, LOW);
    analogWrite(ENA, 0);
    analogWrite(ENB, 0);
}