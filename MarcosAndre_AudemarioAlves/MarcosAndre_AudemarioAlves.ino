const int potPin = A0;
const int motorPin1 = A5;
const int motorPin2 = A4;

void setup() {
  pinMode(potPin, INPUT);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
}

void loop() {
  int potValue = analogRead(potPin);
  int motorSpeed = map(potValue, 0, 1000, 0, 250);

  if (potValue < 512) {
    // Sentido horário
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
  } else {
    // Sentido anti-horário
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
  }

  // Controlando a velocidade do motor
  analogWrite(motorPin1, motorSpeed);
  analogWrite(motorPin2, motorSpeed);
}
