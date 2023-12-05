const int S0 = 4;    // Pino S0 do BCD conectado ao pino 4 do Arduino
const int S1 = 3;    // Pino S1 do BCD conectado ao pino 3 do Arduino
const int S2 = 2;    // Pino S2 do BCD conectado ao pino 2 do Arduino
const int S3 = 1;    // Pino S3 do BCD conectado ao pino 1 do Arduino
const int buttonPin = 0;  // Pino do botão conectado ao pino 0 do Arduino

int numeroAtual = 0;
bool botaoPressionado = false;

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(buttonPin) == LOW && !botaoPressionado) {
    botaoPressionado = true;
    // Incrementa o número e o exibe
    numeroAtual = (numeroAtual + 1) % 4;  // 4 é o número máximo
    exibirNumero(numeroAtual);
  } else if (digitalRead(buttonPin) == HIGH) {
    botaoPressionado = false;
  }
}

void exibirNumero(int numero) {
  // Configura as entradas BCD para o número desejado
  digitalWrite(S0, bitRead(numero, 0));
  digitalWrite(S1, bitRead(numero, 1));
  digitalWrite(S2, bitRead(numero, 2));
  digitalWrite(S3, bitRead(numero, 3));
}
