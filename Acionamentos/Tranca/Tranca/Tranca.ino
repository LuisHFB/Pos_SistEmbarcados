#include <RotaryEncoder.h>

#define wipeB 3 //botão SW

RotaryEncoder encoder(A2, A3);

byte senha[]={15,-22,15}; // senha salva
byte matriz[3]; //guarda senha lida
boolean match = false; 

void setup() {
  pinMode(wipeB, INPUT_PULLUP);   // Enable pin's pull up resistor
  Serial.begin(57600);
  static int n = 0; // inicia em zero
    PCICR |= (1 << PCIE1);    // This enables Pin Change Interrupt 1 that covers the Analog input pins or Port C.
  PCMSK1 |= (1 << PCINT10) | (1 << PCINT11);
}

bool monitorWipeButton(uint32_t interval) {
  uint32_t now = (uint32_t)millis();
  while ((uint32_t)millis() - now < interval)  {
    // check on every half a second
    if (((uint32_t)millis() % 500) == 0) {
      if (digitalRead(wipeB) != LOW)
        return false;
    }
  }
  return true;
}

ISR(PCINT1_vect) {
  encoder.tick(); // just call tick() to check the state.
}

void loop() {
   int n;
   static int pos = 0;
  encoder.tick();

  int newPos = encoder.getPosition();
  if (pos != newPos) {
    Serial.print(newPos);
    Serial.println();
    pos = newPos;

    bool buttonState = monitorWipeButton(1000);
    if(buttonState){
      pos = matriz[n];
      ++n;
      pos = 0;
      Serial.println("ok"); 
    }
    if (n>=2){
      if ( a[0] != 0 )      // Make sure there is something in the array first
    match = true;       // Assume they match at first
      for(int i=0; i<2; ++i){
        if(senha[i] != matriz[i])
        match = false;
      }
      if(match){
       Serial.print("Destrava"); //Destrava
      }
      else {
       Serial.print("Bloqueia"); //bloqueia
      }
      n=0;
    }
   }
}

