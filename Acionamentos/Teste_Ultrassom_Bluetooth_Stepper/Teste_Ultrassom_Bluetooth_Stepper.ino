//TESTE - HC-SR04
#include <SoftwareSerial.h>
#include <Stepper.h>

//Serial por software: RX = digital pin 5, TX = digital pin 6
//Cria um objeto SoftwareSerial
SoftwareSerial bluetooth(5, 6);

//Ultrassom
const int trig = 12;
const int echo = 13;
unsigned long previousMicros;
unsigned long timeout = 29000;  //Dmax = 500 cm, D = t/58, timeout = 500.58

//Motor de passo
const int stepsPerRevolution = 2048;
//Cria um objeto Stepper
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() {
  //Máximo 3 rpm:
  myStepper.setSpeed(3);
  //Inicializa a porta serial
  Serial.begin(9600);
  bluetooth.begin(9600);
  
  //Inicializa o HC-SR04
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

unsigned int ultrassom_tempo() {
  //Pulso de 10us
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  //Lê tempo atual
  previousMicros = micros();
  //Aguarda borda de subida ou timeout
  while(!digitalRead(echo) && (micros() - previousMicros) <= timeout); // wait for the echo pin HIGH or timeout
  //Atualiza o tempo atual
  previousMicros = micros();
  //Aguarda borda de descida ou timeout
  while(digitalRead(echo)  && (micros() - previousMicros) <= timeout); // wait for the echo pin LOW or timeout
  //Calcula a diferença de tempos
  return micros() - previousMicros; // duration
}

unsigned int ultrassom_cm(unsigned int tempo_us) {
  return tempo_us / 58;
}

void loop() {
  unsigned int tempo;
  unsigned int cm;
  unsigned int graus = 0;
  unsigned int avanco = 30;
  
  //Teste 1 - Teste o HC-SR04
 /* while(1){
    tempo = ultrassom_tempo();
    cm = ultrassom_cm(tempo);
    Serial.print("Tempo do eco [us]: "); Serial.println(tempo);
    Serial.print("Distância do objeto [cm]: "); Serial.println(cm);
    delay(100);
  }*/
  
  //Teste 2 - Radar com o HC-SR04
  while(0){
    if(graus > 180)
    {
      //Home
      graus = 0;
      //Limpa o gráfico do app Bluetooth Electronics
      bluetooth.print("*HC*");
      //Retorna o motor 180 graus
      myStepper.step(-stepsPerRevolution/2);
      //Aguarda um tempo para reiniciar
      delay(1000);      
    }
    while (graus <= 180)
    {
      //Posiona o motor/sensor
      myStepper.step((stepsPerRevolution*avanco)/360);
      //Executa a leitura
      tempo = ultrassom_tempo();
      cm = ultrassom_cm(tempo);
      //Envia pela serial
      Serial.print("Tempo do eco [us]: "); Serial.println(tempo);
      Serial.print("Distância do objeto [cm]: "); Serial.println(cm);
      //Envia via bluetooth para o app Bluetooth Electronics
      bluetooth.print("*HX");
      bluetooth.print(graus,DEC);
      bluetooth.print("Y");
      bluetooth.print(cm);
      bluetooth.print("*");
      //Avança o motor
      graus += 30;
      //Aguarda um tempo até a próxima leitura
      delay(100);
    }
  }
}


