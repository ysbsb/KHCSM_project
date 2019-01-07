#include <SoftwareSerial.h>
 
SoftwareSerial BTSerial(2, 3);  // Bluetooth's TX, RX
 
int firePin = 6;
int cancelPin = 7;
 
int lastB1 = HIGH;
int lastB2 = HIGH;
 
unsigned long lastSendTime = 0;
unsigned long RESEND_THRESHOLD = 200;
 
void setup() {
  pinMode(firePin, INPUT_PULLUP);
  pinMode(cancelPin, INPUT_PULLUP);
  BTSerial.begin(9600);
}
 
void loop() {
  int curB1 = digitalRead(firePin);
  int curB2 = digitalRead(cancelPin);
  
  unsigned long curTime = millis();
  if(curTime > lastSendTime + RESEND_THRESHOLD) {
    if(curB1 == LOW) {
      BTSerial.write('b');
      lastSendTime = curTime;      
    } else if(curB2 == LOW) {
      BTSerial.write('c');
      lastSendTime = curTime;      
    }
  }
  
  lastB1 = curB1;
  lastB2 = curB2;
}
