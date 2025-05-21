// Test code for ultrasonic sensor (HC-SR04)

const int triggerPin = 10;  // Trigger pin
const int echoPin = A0;     // Echo pin

long duration;
float distance;

void setup() {
  Serial.begin(9600);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Send ultrasonic pulse
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  // Measure echo response time
  duration = pulseIn(echoPin, HIGH, 30000);  // timeout after 30ms
  distance = duration * 0.0343 / 2;          // Convert to cm

  // Print result to Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(500);  // Wait before next measurement
}
