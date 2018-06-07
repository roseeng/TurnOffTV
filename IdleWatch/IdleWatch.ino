/*

*/

#include <IRremote.h>
IRsend irsend;

#define PIR_MOTION_SENSOR 2//Use pin 2 to receive the signal from the module

unsigned long previousMillis = 0;        // will store last time LED was updated 
unsigned long interval = 5*60*1000L;           // How long idle time before we turn off the TV

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);   // Status message will be sent to PC at 9600 baud

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  // initialize digital pin PIR_MOTION_SENSOR as an input.
  pinMode(PIR_MOTION_SENSOR, INPUT);

  previousMillis = millis();
  
  Serial.print("Setup finished.\n");
}

// the loop function runs over and over again forever
void loop() {
  unsigned long currentMillis = millis(); 
  if (currentMillis < previousMillis) {
    Serial.print("millis() has wrapped around.\n");
    previousMillis = currentMillis;
  }
  
  if (isPeopleDetected()) {
    Serial.print("Detect!\n");
    previousMillis = currentMillis;   
    flash();
  }

//  debugOut(currentMillis, previousMillis);

  if (currentMillis - previousMillis > interval) {
    Serial.print("Idle timeout reached, powering off...\n");
    previousMillis = currentMillis;   
    PowerOff();
  }
  
  delay(500);
}

void PowerOff() {
  for (int i = 0; i < 3; i++) {
    irsend.sendSAMSUNG(0xE0E019E6, 32); // Power Off
    delay(40);
  }
}

void flash() {
  blink(500, 500);
  blink(500, 500);
  blink(500, 500);
}

void blink(int onTime, int offTime)
{
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(onTime);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(offTime);                       // wait for a second
}

boolean isPeopleDetected()
{
    int sensorValue = digitalRead(PIR_MOTION_SENSOR);
    if(sensorValue == HIGH)//if the sensor value is HIGH?
    {
        return true;//yes,return true
    }
    else
    {
        return false;//no,return false
    }
}

void debugOut(unsigned long currentMillis, unsigned long previousMillis)
{
  Serial.print("Current:");
  Serial.print(currentMillis);
  Serial.print(" Previous::");
  Serial.print(previousMillis);
  Serial.print("\n");
}

