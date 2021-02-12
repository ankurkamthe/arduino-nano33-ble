/*

In this sketch, we enable beaconing with a static manufacturer specific advertisement.

515-2# show ap debug ble-table mac-addr e4:f2:05:7e:e8:68

BLE Device Table
----------------
                                                                            
                                                                            
MAC                     : e4:f2:05:7e:e8:68                                 
RSSI                    : -86                                               
Last Update - Advert    : 4s                                                
Last Update - Scan Rsp  : 4s                                                
Local Name              : TEST                                             
Device Class            : iBeacon                                           
Major                   : 11                                                
Minor                   : 22                                                
UUID                    : 11111111-2222-2222-3333-333344444444              
Calib RSSI              : -77                                               
Scan Response[ 7]       : 06 09 54 45 53 54 31                              
Advertisement[30]       : 02 01 06 1A FF 4C 00 02 15 11 11 11 11 22 22 22   
                          22 33 33 33 33 44 44 44 44 00 0B 00 16 B3  
                          
*/

#include <ArduinoBLE.h>
#include <arduino-timer.h>

String inputString = "";      // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete

auto timer = timer_create_default();

int adv_type = 0;

/////////// Service and Characteristic Definition //////////

BLEService ledService("19B10000-E8F2-537E-4F6C-D104768A1214"); // BLE LED Service

// BLE LED Switch Characteristic - custom 128-bit UUID, read and writable by central
BLEByteCharacteristic switchCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);


const int ledPin = LED_BUILTIN; // pin to use for the LED

char buffer[100];   // using for formatted printfs... seems arduino does not have 



void setup() {
  Serial.begin(9600);
  while (!Serial);

  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
  
  // begin initialization
  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");

    while (1);
  }
  Serial.println("starting BLE SUCCESS!!!!");

  String address = BLE.address();
  Serial.println("MAC Address:");
  Serial.println(address);

  // set advertised local name and service UUID:
BLE.setLocalName("TEST");
BLE.setDeviceName("ARUN");
  // add the characteristic to the service
  ledService.addCharacteristic(switchCharacteristic);

  // add service
  BLE.addService(ledService);

  // set the initial value for the characeristic:
  switchCharacteristic.writeValue(0);

  // Set advertising interval
  BLE.setAdvertisingInterval(800);  // interval: 800x0.625us=500ms

//  // set advertisement payload to manufacturer specific
//  byte data[] = { 0x4c, 0x00, 0x02, 0x15, 0x11, 0x11, 0x11, 0x11,
//                  0x22, 0x22, 0x22, 0x22,
//                  0x33, 0x33, 0x33, 0x33,
//                  0x44, 0x44, 0x44, 0x44,
//                  0x00, 11, 0x00, 22,
//                  0xb3
//                };
//  BLE.setManufacturerData(data, sizeof(data));

  // start advertising
  BLE.advertise();

  Serial.println("Start loop");
}

void loop() {
  // listen for BLE peripherals to connect:
  BLEDevice central = BLE.central();

  // if a central is connected to peripheral:
  if (central) {
    Serial.print("Connected to central: ");
    // print the central's MAC address:
    Serial.println(central.address());

    // while the central is still connected to peripheral:
    while (central.connected()) {
      // if the remote device wrote to the characteristic,
      // use the value to control the LED:
      if (switchCharacteristic.written()) {
        if (switchCharacteristic.value()) {   // any value other than 0
          Serial.println("LED on");
          digitalWrite(ledPin, HIGH);         // will turn the LED on
        } else {                              // a 0 value
          Serial.println("LED off");
          digitalWrite(ledPin, LOW);          // will turn the LED off
        }
      }
    }

    // when the central disconnects, print it out:
    Serial.print("Disconnected from central: ");
    Serial.println(central.address());
  }

  if (stringComplete) {
    Serial.print("Received: ");
    Serial.println(inputString);
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
  
  timer.tick();
  serialEvent();
}

void serialEvent()
{
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
