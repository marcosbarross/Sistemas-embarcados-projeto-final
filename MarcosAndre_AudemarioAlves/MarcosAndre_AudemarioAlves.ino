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

int numeroAtual = 0;
bool botaoPressionado = false;

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

  Serial.begin(9600);
}

void loop() {
  int potValue = analogRead(potPin);
  Serial.println(potValue);

  delay(50);  // Adiciona um pequeno atraso para evitar leituras muito rápidas

  if (potValue > 600) {
    // Sentido horário
    digitalWrite(motorTerminal1, LOW);
    digitalWrite(motorTerminal2, HIGH);
  } else {
    // Sentido anti-horário
    digitalWrite(motorTerminal1, HIGH);
    digitalWrite(motorTerminal2, LOW);
  }

  if (digitalRead(buttonPin) == LOW && !botaoPressionado) {
    botaoPressionado = true;
    numeroAtual = (numeroAtual + 1) % 4;
    exibirNumero(numeroAtual);
  } else if (digitalRead(buttonPin) == HIGH) {
    botaoPressionado = false;
  }

  // Resto do código...
}

void exibirNumero(int numero) {
  digitalWrite(S0, bitRead(numero, 0));
  digitalWrite(S1, bitRead(numero, 1));
  digitalWrite(S2, bitRead(numero, 2));
  digitalWrite(S3, bitRead(numero, 3));
}
