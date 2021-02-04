#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define BLYNK_PRINT Serial
BlynkTimer timer;
#define ultraTrig D6
#define ultraEcho D7
#define myLed D1
int msg = 0;
long ultraDetectFunc();
void msgService();
char auth[] = "fvU4ImdxnhFN15zra9B7gKVRCdQ4WDv2";
char ssid[] = "sushanthiot";
char pass[] = "Diya318@#";
void setup() {
    pinMode(ultraTrig,OUTPUT);
    pinMode(ultraEcho,INPUT);
    pinMode(myLed,INPUT);
    Serial.begin(9600);
       Blynk.begin(auth, ssid, pass);
   timer.setInterval(1000L,msgService);
}
BLYNK_WRITE(V3) // V1 is the number of Virtual Pin  
{
int pinValue = param.asInt();
delay(200);
if(pinValue == 1 )
              Serial.println(msg);
                msg = 0;
}
void loop() {

  while(1) {
      Blynk.run();
        long ultraBuff = ultraDetectFunc();
        int quantity = map(ultraBuff,0,40,0,100);
            Serial.println(ultraBuff);
            if( ultraBuff < 15 ) {
                timer.run(); 
                  digitalWrite(myLed, HIGH); // Turn LED on.
                  }
            else
                  digitalWrite(myLed, LOW); // Turn LED on.
                        Blynk.virtualWrite(V4,quantity);
        delay(1000);
             } 
          }


long ultraDetectFunc() {
        digitalWrite(ultraTrig,LOW);
        delayMicroseconds(2);
        digitalWrite(ultraTrig,HIGH);
        delayMicroseconds(10);
        digitalWrite(ultraTrig,LOW);
        long duration = pulseIn(ultraEcho,HIGH);
        long distance = duration / 58.2;
        delay(50);
  return distance;
}


void msgService() {
  if( msg == 0 ) {
    Serial.println("Sent");
    Blynk.email("sushanthsmbanger318@gmail.com","DustBin is Full","Please empty the dustbin");
    Blynk.notify("DustBin is full - Please empty the dustbin ");
    msg = 1;
  }
}
