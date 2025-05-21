//only gun code
#include <Servo.h>

// ----- Servo Objects -----
Servo servoradar;
Servo servogun;
Servo servotrigger;

// ----- Pin Assignments -----
int servoradarpin=8;    // Radar servo pin
int servogunpin=A1;      // Gun aiming servo pin
int servotriggerpin=2;  // Trigger pulling servo pin
int triggerpin=10;       // Ultrasonic trigger pin
int echopin=A0;          // Ultrasonic echo pin

// ----- Constants and Variables -----
float distancefilter=10;
int pulltriggerangle=40;
long pingTraveltime;

int radarangle = 0;
bool sweepDirection = true;
bool enemyDetected = false;
int waittimeforkill = 10000;

unsigned long lastRadarMoveTime = 0;
unsigned long radarMoveInterval = 50;
unsigned long enemyDetectedTime = 0;

int radarlimit=80;   //radarlimit for scanning 
int gunlockangle =40;  // intial postion of gun

// -----------------------------------------------------------------------------
// Radar sweep function
void moveRadarServo() {
  servoradar.write(radarangle);
  if (sweepDirection) {
    radarangle += 5;
    if (radarangle >= (radarlimit)) sweepDirection = false;
  } else {
    radarangle -= 5;
    if (radarangle <=0) sweepDirection = true;
  }
}

// -----------------------------------------------------------------------------
// Measure distance
float measuredistance() {
  digitalWrite(triggerpin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerpin, LOW);

  pingTraveltime = pulseIn(echopin, HIGH, 30000);
  float distance = pingTraveltime * 0.0343 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  return distance;
}

// Setup
void setup() {
  Serial.begin(9600);
  Serial.println("Line follower starting");

  servoradar.attach(servoradarpin);
  servogun.attach(servogunpin);
  servotrigger.attach(servotriggerpin);

  pinMode(triggerpin, OUTPUT);
  pinMode(echopin, INPUT);
  servogun.write(gunlockangle);
  servotrigger.write(0);
}

// -----------------------------------------------------------------------------
// Main loop
void loop() {
  if (millis() - lastRadarMoveTime >= radarMoveInterval) {
    lastRadarMoveTime = millis();
    moveRadarServo();

    float positionlength = measuredistance();

    if (positionlength < distancefilter) {
      Serial.println("Enemy detected!");
      gunlockangle=radarangle;
      servogun.write(gunlockangle);
      enemyDetected = true;
      enemyDetectedTime = millis();
    }
  }

  if(enemyDetected){
   // Move gun slowly towards detected angle
  int currentGunAngle = servogun.read();  // Read current angle of gun servo
  if (currentGunAngle < gunlockangle) {
    for (int pos = currentGunAngle; pos <= gunlockangle; pos += 20) {
      servogun.write(pos);
      delay(100);  // Adjust delay for smoother or faster movement
    }
  } else {
    for (int pos = currentGunAngle; pos >= gunlockangle; pos -= 20) {
      servogun.write(pos);
      delay(100);  // Adjust delay for smoother or faster movement
    }
  }

  delay(1000);  // Small pause before firing
  
  servotrigger.write(pulltriggerangle);
  delay(500);
  servotrigger.write(0);
  delay(1000);

  enemyDetected = false;
  }
}