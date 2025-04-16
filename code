#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <Dabble.h>

#define INT1 4
#define INT2 5
#define INT3 6
#define INT4 7

void setup()
{
  // Inicializando a comunicação serial para depuração
  Serial.begin(9600);  // Use uma taxa de 9600 baud, que é mais comum para comunicação com o Dabble
  Dabble.begin(9600, 2, 3);  // Defina a comunicação com o módulo Dabble

  // Configura os pinos como saída para controle dos motores
  pinMode(INT1, OUTPUT);
  pinMode(INT2, OUTPUT);
  pinMode(INT3, OUTPUT);
  pinMode(INT4, OUTPUT);

  Stop();  // Inicializa o robô parado
}

void loop() {
  // Processa as entradas do GamePad
  Dabble.processInput();

  // Verifica se algum botão do GamePad foi pressionado
  if (GamePad.isUpPressed()) {
    Serial.println("Movendo para frente");
    forward(); 
  }
  else if (GamePad.isDownPressed()) {
    Serial.println("Movendo para trás");
    backward(); 
  }
  else if (GamePad.isLeftPressed()) {
    Serial.println("Movendo para a esquerda");
    left(); 
  }
  else if (GamePad.isRightPressed()) {
    Serial.println("Movendo para a direita");
    right(); 
  }
  else {
    Serial.println("Parando");
    Stop();  // Se nenhum botão foi pressionado, o robô para
  }
}

// Função para mover o robô para frente
void forward() {
  digitalWrite(INT1, LOW);
  digitalWrite(INT2, HIGH);
  digitalWrite(INT3, HIGH);
  digitalWrite(INT4, LOW);
}

// Função para mover o robô para trás
void backward() {
  digitalWrite(INT1, HIGH);
  digitalWrite(INT2, LOW);
  digitalWrite(INT3, LOW);
  digitalWrite(INT4, HIGH);
}

// Função para mover o robô para a esquerda
void left() {
  digitalWrite(INT1, HIGH);
  digitalWrite(INT2, LOW);
  digitalWrite(INT3, HIGH);
  digitalWrite(INT4, LOW);    
}

// Função para mover o robô para a direita
void right() {
  digitalWrite(INT1, LOW);
  digitalWrite(INT2, HIGH);
  digitalWrite(INT3, LOW);
  digitalWrite(INT4, HIGH);  
}

// Função para parar o robô
void Stop() {
  digitalWrite(INT1, LOW);
  digitalWrite(INT2, LOW);

  digitalWrite(INT3, LOW);
  digitalWrite(INT4, LOW);  
}
