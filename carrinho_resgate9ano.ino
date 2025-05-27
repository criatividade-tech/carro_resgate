#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <Dabble.h>
#include <Servo.h>

#define INT1 4
#define INT2 5
#define INT3 6
#define INT4 7
#define EXTRA_MOTOR_PIN 8
#define SERVO_PIN 9

bool motorLigado = false;
bool botaoTrianguloAnterior = false;

bool rampaAtivada = false;
bool botaoQuadradoAnterior = false;

Servo rampaServo;
int anguloAtual = 0;  // Guarda a posição atual do servo

void setup()
{
  Serial.begin(9600);
  Dabble.begin(9600, 2, 3);

  pinMode(INT1, OUTPUT);
  pinMode(INT2, OUTPUT);
  pinMode(INT3, OUTPUT);
  pinMode(INT4, OUTPUT);
  pinMode(EXTRA_MOTOR_PIN, OUTPUT);

  digitalWrite(EXTRA_MOTOR_PIN, LOW);

  rampaServo.attach(SERVO_PIN);
  rampaServo.write(anguloAtual);

  Stop();
}

void loop() {
  Dabble.processInput();

  // Controle do robô
  if (GamePad.isUpPressed()) {
    forward(); 
  }
  else if (GamePad.isDownPressed()) {
    backward(); 
  }
  else if (GamePad.isLeftPressed()) {
    left(); 
  }
  else if (GamePad.isRightPressed()) {
    right(); 
  }
  else {
    Stop();
  }

  // Controle do motor extra - botão Triângulo
  bool botaoTrianguloAtual = GamePad.isTrianglePressed();
  if (botaoTrianguloAtual && !botaoTrianguloAnterior) {
    motorLigado = !motorLigado;
    digitalWrite(EXTRA_MOTOR_PIN, motorLigado ? HIGH : LOW);
    Serial.print("Motor extra ");
    Serial.println(motorLigado ? "LIGADO" : "DESLIGADO");
  }
  botaoTrianguloAnterior = botaoTrianguloAtual;

  // Controle do servo (rampa) com movimento suave - botão Quadrado
  bool botaoQuadradoAtual = GamePad.isSquarePressed();
  if (botaoQuadradoAtual && !botaoQuadradoAnterior) {
    rampaAtivada = !rampaAtivada;
    int anguloDestino = rampaAtivada ? 60 : 0;
    moverServoSuavemente(anguloDestino);
    Serial.print("Rampa ");
    Serial.println(rampaAtivada ? "LEVANTADA (60°)" : "RECOLHIDA (0°)");
  }
  botaoQuadradoAnterior = botaoQuadradoAtual;
}

// Função para mover o servo suavemente até um ângulo
void moverServoSuavemente(int destino) {
  if (destino > anguloAtual) {
    for (int ang = anguloAtual; ang <= destino; ang++) {
      rampaServo.write(ang);
      delay(15);  // Atraso para suavidade
    }
  } else {
    for (int ang = anguloAtual; ang >= destino; ang--) {
      rampaServo.write(ang);
      delay(15);
    }
  }
  anguloAtual = destino;  // Atualiza posição atual
}

// Funções de movimentação
void forward() {
  digitalWrite(INT1, LOW);
  digitalWrite(INT2, HIGH);
  digitalWrite(INT3, HIGH);
  digitalWrite(INT4, LOW);
}

void backward() {
  digitalWrite(INT1, HIGH);
  digitalWrite(INT2, LOW);
  digitalWrite(INT3, LOW);
  digitalWrite(INT4, HIGH);
}

void left() {
  digitalWrite(INT1, HIGH);
  digitalWrite(INT2, LOW);
  digitalWrite(INT3, HIGH);
  digitalWrite(INT4, LOW);    
}

void right() {
  digitalWrite(INT1, LOW);
  digitalWrite(INT2, HIGH);
  digitalWrite(INT3, LOW);
  digitalWrite(INT4, HIGH);  
}

void Stop() {
  digitalWrite(INT1, LOW);
  digitalWrite(INT2, LOW);
  digitalWrite(INT3, LOW);
  digitalWrite(INT4, LOW);  
}
