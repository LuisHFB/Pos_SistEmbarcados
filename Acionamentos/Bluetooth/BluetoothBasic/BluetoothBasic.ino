#include <SoftwareSerial.h>
SoftwareSerial BT(10, 11); // RX, TX
String command = ""; // Stores response of bluetooth device

void setup()
{
  Serial.begin(9600);
  Serial.println("Type AT commands!");
  BT.begin(9600); // HC-06 usually default baud-rate
}
void loop()
{
  if (BT.available()) // Read device output if available.
  {
    while(BT.available()) // While there is more to be read, keep reading.
   {
     delay(10); //Delay added to make thing stable 
     char c = BT.read(); //Conduct a serial read
     command += c; //build the string.
    } 
    Serial.println(command);
    command = ""; // No repeats
  } 
  if (Serial.available())
  {
    delay(10); // The DELAY! ********** VERY IMPORTANT *******
    BT.write(Serial.read());
   }
}
