#include <ArduinoBLE.h>
#include <DHT11.h>

DHT11 dht11(3);

BLEUnsignedCharCharacteristic humidity1Char ("2A19", BLERead | BLENotify);

//Configures services to be readable on the bulletin
const char * deviceServiceUuid = "50215b12-5f68-479b-86ae-5c9640b728a2";
const char * deviceServiceRequestCharacteristicUuid = "50215b12-5f68-479b-86ae-5c9640b728a3";
const char * deviceServiceResponseCharacteristicUuid = "50215b12-5f68-479b-86ae-5c9640b728a4";

//int humidity1 = -1 //Unsure if needed

//Defines services with specific variables
BLEService humidity1Service(deviceServiceUuid);
BLEStringCharacteristic humidity1RequestCharacteristic(deviceServiceRequestCharacteristicUuid, BLEWrite, 4);
BLEStringCharacteristic humidity1ResponseCharacteristic(deviceServiceResponseCharacteristicUuid, BLENotify, 4);

void setup()
{
  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);

  //I love it when you call me Big Poppa
  //Throw your hands in the air if you's a true player
  BLE.setDeviceName("Big Papa");
  BLE.setLocalName("Big Papa");

//Announce Failure 
  if(!BLE.begin())
  {
    Serial.println("It's so over");
    while(1);
  }
//Posts values to bulletin
  BLE.setAdvertisedService(humidity1Service);
  humidity1Service.addCharacteristic(humidity1RequestCharacteristic);
  humidity1Service.addCharacteristic(humidity1ResponseCharacteristic);
  BLE.addService(humidity1Service);

 humidity1ResponseCharacteristic.writeValue("ALL CLEAR");
  BLE.advertise();
  Serial.println("SCANNING START");


  

}

void loop()
{
  BLEDevice central = BLE.central();
  Serial.println("ON SIGHT!");
  delay(500);

  if(central)
  {
    Serial.println("THE BLUETOOTH DEVICE IS CONNECTEDUH SUCCESSFULLAY");
    Serial.println(central.address());
    digitalWrite(LED_BUILTIN, HIGH);

    while(central.connected())
    {
      int humidity1 = dht11.readHumidity();
      
      if (humidity1 != DHT11::ERROR_CHECKSUM && humidity1 != DHT11::ERROR_TIMEOUT) 
      {
        Serial.print("Humidity: ");
        Serial.print(humidity1);
        Serial.println("%");
        humidity1Char.writeValue(humidity1);
        delay(200);
      }
    }
  }
  digitalWrite(LED_BUILTIN, LOW);
  Serial.print("Rome has fallen");
  Serial.println(central.address());

}