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
char csensorValue;


char cvalorQ;
char cvalorR;

int leSens_Cond(int pinSensor, int media){
  int i;
  int sval = 0;
  char valorC;
  
  for (i = 0; i < media; i++){
    sval = sval + analogRead(pinSensor);    // salva valor lido pelo sensor
  }

  sval = sval / media;    // média
  sval = sval /4;         // converte para escala de 8 bits (0 - 255)
  sval = map(sval,0,255,0,99); //mapeia de 0-99

  valorC = sval;
  int valorQ = valorC/10;
  int valorR = valorC%10;
  cvalorQ = valorQ+48;
  cvalorR = valorR+48;

  return sval;
}

int moveMotor(){
  int l1;
  l1 = (command[1]-48)*10;
  l1 = l1+(command[2]-48);
  setPoint = l1;
 Serial.println(setPoint);

 //int mapsetPoint = map(setPoint,15,99,0,179);

//myservo.write(mapsetPoint);
  if(sensorValue<setPoint){  // Se estive mais claro do que o setado
      for (pos = 0; pos < 180; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
   }
//   else if (sensorValue == setPoint){
//    continue;
//   } 
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
  myservo.attach(9);
}

void loop() {
    csensorValue = leSens_Cond(analogInPin, 5); //salva valor tratado como sensorValue
    BT.write('*');
    BT.write('L');
    BT.write(cvalorQ);
    BT.write(cvalorR);
    BT.write('*');
    delay(100);
  if (BT.available()) // Read device output if available.
  { 
    while(BT.available()) // While there is more to be read, keep reading.
   {
     delay(10); // The DELAY! ********** VERY IMPORTANT *******
     char c = BT.read(); //Conduct a serial read
     command += c; //build the string.
  }
  Serial.println(command);
  if(command.startsWith("S")>0) moveMotor();
  command = ""; // No repeats
 }
  if (Serial.available())
  {
//    char bluetoothData=BT.read();
//    if(bluetoothData=='S') Serial.print("Reggae");// setPoint=Serial.parseInt();
      
    delay(10); // The DELAY! ********** VERY IMPORTANT *******
    BT.write(Serial.read());
   }
   
}
