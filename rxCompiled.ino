#include <VirtualWire.h>
#include <VirtualWire_Config.h>
#include <LiquidCrystal.h>
const int LCDVSS=2;
const int LCDVCC=3;
const int rs=4;
const int rw=5;
const int en=6;
const int d4=7;
const int d5=8;
const int d6=9;
const int d7=10;

const int relayout1=A0;
const int relayout2=A1;

const int RX_VCC = 11;
const int RX_PIN = 12;// Tell Arduino on which pin you would like to receive data NOTE should be a PWM Pin
const int RX_GND = 13;
const int RX_ID = 3;// Recever ID address 
int TX_ID;
struct roverRemoteData //Data Structure 
{
int    TX_ID;      // Initialize a storage place for the incoming TX ID  
int    Sensor1Data;// Initialize a storage place for the first integar that you wish to Receive 
int    Sensor2Data;// Initialize a storage place for the Second integar that you wish to Receive
int    Sensor3Data;// Initialize a storage place for the  Third integar that you wish to Receive
int    Sensor4Data;// Initialize a storage place for the Forth integar that you wish to Receive

};

void setup() {
              pinMode(rw, OUTPUT);
              pinMode(LCDVCC, OUTPUT);
              pinMode(LCDVSS, OUTPUT);

              digitalWrite(LCDVCC, HIGH);
              digitalWrite(LCDVSS, LOW);
              digitalWrite(rw, LOW);

              LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
  
              Serial.begin(9600);// Begin Serial port at a Buad speed of 9600bps 
              vw_setup(2000);// Setup and Begin communication over the radios at 2000bps( MIN Speed is 1000bps MAX 4000bps)
              vw_set_rx_pin(RX_PIN);// Set RX Pin 
              vw_rx_start(); 
                   
              }  
void loop()
{
      struct roverRemoteData receivedData;
      uint8_t rcvdSize = sizeof(receivedData);//Incoming data size 
      vw_wait_rx();// Start to Receive data now 

if (vw_get_message((uint8_t *)&receivedData, &rcvdSize)) // Check if data is available 
{
  if (receivedData.TX_ID == RX_ID) //Check if the radio signal recieved matches the ID of the Reciever
    { 
      // If data was Recieved print it to the serial monitor.
         Serial.println("------------------------New MSG-----------------------");
         Serial.print("TX ID:");
         Serial.println(TX_ID);
         Serial.print("Sensor1Data:");
         Serial.println(receivedData.Sensor1Data);
         Serial.print("Sensor2Data:");
         Serial.println(receivedData.Sensor2Data);
         Serial.print("SensorData3:");
         Serial.println(receivedData.Sensor3Data);
         Serial.print("SensorData4:");
         Serial.println(receivedData.Sensor4Data);
        
         Serial.println("-----------------------End of MSG--------------------");
        } 
      else
        { 
Serial.println(" ID Does not match waiting for next transmission ");
        } 
      } 
    }

