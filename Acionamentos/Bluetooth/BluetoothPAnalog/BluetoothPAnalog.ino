/*
Controle de persiana atraves de celular, modulo bluetooth e ldr(sendo emulado por um potenciometro
*/
#include <SoftwareSerial.h>
#include <Servo.h>
SoftwareSerial BT(10, 11); // RX, TX
Servo myservo;

String command = ""; // Stores response of bluetooth device

const int analogInPin = A0;  // Entrada analogica do pot
const int analogOutPin = 9; // Saida para o motor

int sensorValue = 0;        // Leitura do Potenciometro
int outputValue = 0;        // Saida PWM (analog out)
int setPoint = 0;           //Setpoint a ser definido pelo usuário
int pos = 0;

int leSens_Cond(int pinSensor, int media){
  int i;
  int sval = 0;

  for (i = 0; i < media; i++){
    sval = sval + analogRead(pinSensor);    // salva valor lido pelo sensor
  }

  sval = sval / media;    // média
  sval = sval /4;         // converte para escala de 8 bits (0 - 255)
  sval = map(sval,0,255,0,100); //mapeia de 0-100
  return sval;
}

int controlMotor(){
  if(sensorValue<setPoint){  // Se estive mais claro do que o setado
      for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
   }
   else if (sensorValue == setPoint){
   continue;
   } 
   else{
      for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
  }
}
void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  Serial.println("Type AT commands!");
  BT.begin(9600); // HC-06 usually default baud-rate
}

void loop() {
   sensorValue = leSens_Cond(analogInPin, 5); //salva valor tratado como sensorValue
  
  if (BT.available()) // Read device output if available.
  {
    while(BT.available()) // While there is more to be read, keep reading.
   {
     delay(10); //Delay added to make thing stable 
     char c = BT.read(); //Conduct a serial read
     command += c; //build the string.
    } 
    Serial.println("");
    Serial.println(command);
    Serial.print("*L"+String(sensorValue)+"*");  // Padrão "*T"+String(echotime)+"*"
    
    command = ""; // No repeats
  } 
  if (Serial.available())
  {
    delay(10); // The DELAY! ********** VERY IMPORTANT *******
    BT.write(Serial.read());
   }
}
