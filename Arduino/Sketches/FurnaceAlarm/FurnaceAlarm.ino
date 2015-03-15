
/*
  FurnaceAlarm
 Reads a digital input on pin 2, in this case, when the signal goes HIGH. 
 Prints the result to the serial monitor.
 Sends a message to Smart things that the furnace alarm event occured.
 Sends a message to Smart things that the furnace alarm is off.

 Code inspiration by DigitalRead.ino example. 
 To whomever originally authored that example code, Thank you. 
 */
#include <SoftwareSerial.h>  
#include <SmartThings.h>

// digital pin 2 has a relay attached to it. Give it a name:
int RELAY_DETECT_PIN = 2;
int PIN_THING_TX = 3; //at this time, this isn't used except it's needed by the ST constructor. So it's defined here to satisfy the c'tor.
int PIN_THING_RX = 4;
int PIN_RED_LED = 12;
int PIN_GREEN_LED = 13;

//set a delay constant for the loop. 
int DELAY_SECONDS = 2;

//constant to measure against.
int RELAY_CLOSED = 1;

//calculate convert DELAY_SECONDS to milliseconds for ardiuno consumption.
int delayMS = DELAY_SECONDS * 1000;

//boolean to help with code flow when in alarm state (or not)
boolean isAlarmTriggered = false;

//debug
boolean isDebugEnabled = true;

String alarmTriggeredMessage = "alarm";
String alarmResetMessage = "normal";

//construct the smartthing object.
SmartThingsCallout_t messageCallout;    // call out function forward decalaration
SmartThings smartthing(PIN_THING_RX, PIN_THING_TX, messageCallout);  // constructor

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the relay detect pin an input:
  pinMode(RELAY_DETECT_PIN, INPUT);
  pinMode(PIN_RED_LED, OUTPUT);
  pinMode(PIN_GREEN_LED, OUTPUT);
  digitalWrite(PIN_RED_LED, LOW); //initialized off
  digitalWrite(PIN_GREEN_LED, HIGH); //initialized on.
}

// the loop routine runs over and over again forever:
void loop() {
  
  // read the input pin:
  int buttonState = digitalRead(RELAY_DETECT_PIN);
  //case where the relay is closed (alarm state), then the alarm must have been triggered.
  //send a notification to SmartThings. 
  if(RELAY_CLOSED == buttonState) {
    isAlarmTriggered = true;
    digitalWrite(PIN_RED_LED, HIGH);
    digitalWrite(PIN_GREEN_LED, LOW);
    smartthing.send(alarmTriggeredMessage);
    Serial.println(alarmTriggeredMessage);
  }
  
  //case where the relay is open (normal state) and the alarm is in triggered state
  //this is where we think we're returning to normal operation.
  if(RELAY_CLOSED != buttonState && isAlarmTriggered) {
    digitalWrite(PIN_RED_LED, LOW);
    digitalWrite(PIN_GREEN_LED, HIGH);
    isAlarmTriggered = false;
    smartthing.send(alarmResetMessage);
    Serial.println(alarmResetMessage);
  }
  
  
  // print out the state of the button:
  Serial.println(buttonState);
  delay(delayMS);        // delay in between reads for stability
}

void messageCallout(String message)
{
  // if debug is enabled print out the received message
  if (isDebugEnabled)
  {
    Serial.print("Received message: '");
    Serial.print(message);
    Serial.println("' ");
  }
 /*
  // if message contents equals to 'on' then call on() function
  // else if message contents equals to 'off' then call off() function
  if (message.equals("on"))
  {
    on();
  }
  else if (message.equals("off"))
  {
    off();
  }
  else if (message.equals("hello"))
  {
    hello();
  }
  */
}
