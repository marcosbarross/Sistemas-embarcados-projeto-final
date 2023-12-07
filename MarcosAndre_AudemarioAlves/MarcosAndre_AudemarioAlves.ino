#include <Servo.h>

const int S0 = 4;
const int S1 = 3;
const int S2 = 2;
const int S3 = 1;
const int buttonPin = 0;

const int toggleSwitch = 11;
const int motorTerminal1 = 5;
const int motorTerminal2 = 8;
const int enablePin = 9;
const int potPin = A0;
const int servoPin = A5;

int potValue;
int numeroAtual = 0;
bool botaoPressionado = false;
Servo servoMotor;

void incremetar() {
  if (digitalRead(buttonPin) == LOW && !botaoPressionado) {
    botaoPressionado = true;
    numeroAtual = (numeroAtual + 1) % 4;
  } else if (digitalRead(buttonPin) == HIGH) {
    botaoPressionado = false;
  }
}

void controlarMotorDC(int iniciador) {
  if (iniciador == 1) {
    if (potValue > 90) {
      digitalWrite(motorTerminal1, LOW);  // Invertendo a direção
      digitalWrite(motorTerminal2, HIGH); 
    } else {
      digitalWrite(motorTerminal1, HIGH);
      digitalWrite(motorTerminal2, LOW);
    }
  } else {
    digitalWrite(motorTerminal1, LOW);
    digitalWrite(motorTerminal2, LOW);
  }
}

void controlarServoMotor(int iniciador){
  if(iniciador == 2){
    // Define o ângulo do servo motor com base no valor do potenciômetro
    int servoAngle = 180 - potValue;
    servoMotor.write(servoAngle);
  }
}

void exibirNumero(int numero) {
  digitalWrite(S0, bitRead(numero, 0));
  digitalWrite(S1, bitRead(numero, 1));
  digitalWrite(S2, bitRead(numero, 2));
  digitalWrite(S3, bitRead(numero, 3));
}

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  pinMode(motorTerminal1, OUTPUT);
  pinMode(motorTerminal2, OUTPUT);
  pinMode(enablePin, OUTPUT);

  pinMode(potPin, INPUT);
  digitalWrite(enablePin, HIGH);

  servoMotor.attach(servoPin);  // Anexar o servo motor ao pino especificado
}

void loop() {
  // Mapeia os valores do potenciômetro de 0 a 1023 para 0 a 180
  potValue = map(analogRead(potPin), 0, 1023, 0, 180);

  delay(50);
  incremetar();
  controlarMotorDC(numeroAtual);
  controlarServoMotor(numeroAtual);
  exibirNumero(numeroAtual);
}
