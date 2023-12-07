#include <Servo.h>
#include <Stepper.h>

// Definição dos pinos para controle do display de 7 segmentos
const int S0 = 4;
const int S1 = 3;
const int S2 = 2;
const int S3 = 1;
const int buttonPin = 0;

// Definição dos pinos para controle do motor DC
const int toggleSwitch = 11;
const int motorTerminal1 = 5;
const int motorTerminal2 = 8;
const int enablePin = 9;

// Pino analógico para leitura do potenciômetro e controle do servo motor
const int potPin = A0;
const int servoPin = A5;

// Configuração do motor de passo
const int passosPorRevolucao = 50;
const int stepperIn1 = 13;
const int stepperIn2 = 12;
const int stepperIn3 = 11;
const int stepperIn4 = 10;

// Criação do objeto Stepper para controle do motor de passo
Stepper stepperMotor(passosPorRevolucao, stepperIn1, stepperIn2, stepperIn3, stepperIn4);

// Variáveis globais
int potValue;
int numeroAtual = 0;
bool botaoPressionado = false;
Servo servoMotor;

// Função para incrementar o número atual ao pressionar o botão
void incremetar() {
  if (digitalRead(buttonPin) == LOW && !botaoPressionado) {
    botaoPressionado = true;
    numeroAtual = (numeroAtual + 1) % 5;  // Ajusta o número de funções conforme necessário
  } else if (digitalRead(buttonPin) == HIGH) {
    botaoPressionado = false;
  }
}

// Função para controlar o motor DC baseado no potenciômetro
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

// Função para controlar o servo motor baseado no potenciômetro
void controlarServoMotor(int iniciador) {
  if (iniciador == 2) {
    // Define o ângulo do servo motor com base no valor do potenciômetro
    int servoAngle = 180 - potValue;
    servoMotor.write(servoAngle);
  }
}

// Função para controlar o motor de passo baseado no potenciômetro
void controlarMotorPasso(int iniciador) {
  if (iniciador == 3) {
    // Mapeia os valores do potenciômetro para o número de passos
    int steps = map(potValue, 0, 180, -passosPorRevolucao, passosPorRevolucao);

    // Configura a velocidade do motor de passo
    stepperMotor.setSpeed(10); 

    // Rotaciona o motor de passo
    stepperMotor.step(steps);
  }
}

// Função para exibir o número no display de 7 segmentos
void exibirNumero(int numero) {
  digitalWrite(S0, bitRead(numero, 0));
  digitalWrite(S1, bitRead(numero, 1));
  digitalWrite(S2, bitRead(numero, 2));
  digitalWrite(S3, bitRead(numero, 3));
}

void setup() {
  // Configuração dos pinos de controle do display de 7 segmentos
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  // Configuração dos pinos de controle do motor DC
  pinMode(motorTerminal1, OUTPUT);
  pinMode(motorTerminal2, OUTPUT);
  pinMode(enablePin, OUTPUT);

  // Configuração do pino analógico para leitura do potenciômetro
  pinMode(potPin, INPUT);
  digitalWrite(enablePin, HIGH);

  // Anexa o servo motor ao pino especificado
  servoMotor.attach(servoPin);

  // Configuração do motor de passo com a biblioteca Stepper
}

void loop() {
  // Mapeia os valores do potenciômetro de 0 a 1023 para 0 a 180
  potValue = map(analogRead(potPin), 0, 1023, 0, 180);

  // Aguarda um curto período de tempo
  delay(50);

  // Chama as funções para controlar os dispositivos
  incremetar();
  controlarMotorDC(numeroAtual);
  controlarServoMotor(numeroAtual);
  controlarMotorPasso(numeroAtual);
  exibirNumero(numeroAtual);
}