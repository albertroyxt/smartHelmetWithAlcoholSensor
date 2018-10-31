#include <VirtualWire.h>
#include <VirtualWire_Config.h>

const int AOUTpin=A0;//the AOUT pin of the alcohol sensor goes into analog pin A0 of the arduino
const int DOUTpin=A1;//the DOUT pin of the alcohol sensor goes into digital pin D8 of the arduino
const int AGND=A2;
const int AVCC=A3;
const int ledPin=13;//the anode of the LED connects to digital pin D13 of the arduino
const int switchGND=10;
const int switchPin=9;
const int switchVCC=8;
int switchVal;
int limit;
int value;

int TX_GND = 5;
int TX_PIN = 4;// Tell Arduino on which pin you would like to Transmit data NOTE should be a PWM Pin
int TX_VCC = 2;
int TX_ID = 3; // Transmitter ID address

struct roverRemoteData// Data Structure 
{
int    TX_ID;      // Initialize a storage place for the outgoing TX ID
int    Sensor1Data;// Initialize a storage place for the first integar that you wish to Send 
int    Sensor2Data;// Initialize a storage place for the Second integar that you wish to Send
int    Sensor3Data;// Initialize a storage place for the Third integar that you wish to Send
int    Sensor4Data;// Initialize a storage place for the Forth integar that you wish to Send


};

void setup() {

              pinMode(DOUTpin, INPUT);//sets the pin as an input to the arduino
              pinMode(AOUTpin, INPUT);
              pinMode(ledPin, OUTPUT);//sets the pin as an output of the arduino
              pinMode(switchPin, INPUT);
              pinMode(AGND, OUTPUT);
              pinMode(AVCC, OUTPUT);
              pinMode(switchVCC, OUTPUT);
              pinMode(switchGND, OUTPUT);
              pinMode(TX_VCC, OUTPUT);
              pinMode(TX_GND, OUTPUT);
              digitalWrite(AGND, LOW);
              digitalWrite(AVCC, HIGH);
              digitalWrite(switchGND, LOW);
              digitalWrite(switchVCC, HIGH);
              digitalWrite(TX_GND, LOW);
              digitalWrite(TX_VCC, HIGH);


              Serial.begin(9600);// Begin Serial port at a Buad speed of 9600bps 
              vw_setup(2000);// Setup and Begin communication over the radios at 2000bps( MIN Speed is 1000bps MAX 4000bps)
              vw_set_tx_pin(TX_PIN);// Set Tx Pin
 
              }
void loop()
{   

  
  struct roverRemoteData payload;// In this section is where you would load the data that needs to be sent.

  
  // If you want to read a analog pin and transmit its value you can do it as follows by removing the "//" 
  payload.TX_ID = TX_ID; // Set the Radio Address 
  payload.Sensor1Data =analogRead(AOUTpin);// analogRead(Sensor1Pin);
  payload.Sensor2Data =digitalRead(DOUTpin);// analogRead(Sensor2Pin);
  payload.Sensor3Data =digitalRead(switchPin);// analogRead(Sensor3Pin);
  payload.Sensor4Data =1;// analogRead(Sensor4Pin);
 
  
    
  
  vw_send((uint8_t *)&payload, sizeof(payload)); // Send the data 
  vw_wait_tx();// Wait for all data to be sent 
 // Serial.print(analogRead(AOUTpin));
  //Serial.print("\n");
  delay(1000);

}

