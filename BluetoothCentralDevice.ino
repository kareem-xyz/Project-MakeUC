

#include <ArduinoBLE.h>
#include <DHT11.h>

DHT11 dht11(2); 

const char* deviceServiceUuid = "01931651-0c2e-7d1d-b245-55b6294abbd0";
const char* deviceServiceCharacteristicUuid = "01931651-5243-7ff6-a683-080e43c87a28";

int humidity1 = -1;  
int oldhumidity1 = -1;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  
  if (!BLE.begin()) {
    Serial.println("Mission Failed");
    while (1);
  }
  
  BLE.setLocalName("Bigger Papa"); 
  BLE.advertise();

  Serial.println("BiggerPapa");
  Serial.println(" ");
}

void loop() {
  connectToPeripheral();
}

void connectToPeripheral(){
  BLEDevice peripheral;
  
  Serial.println("Looking for Device");

  do
  {
    BLE.scanForUuid(deviceServiceUuid);
    peripheral = BLE.available();
  } while (!peripheral);
  
  if (peripheral) {
    Serial.println("Found Peripheral Device");
    Serial.print("Device Mac Address");
    Serial.println(peripheral.address());
    Serial.print("Device Name:");
    Serial.println(peripheral.localName());
    Serial.print("AdvertisedService");
    Serial.println(peripheral.advertisedServiceUuid());
    Serial.println(" ");
    BLE.stopScan();
    controlPeripheral(peripheral);
  }
}

void controlPeripheral(BLEDevice peripheral) {
  Serial.println("Looking for peripheral");

  if (peripheral.connect()) {
    Serial.println("Connection to peripheral failed");
    Serial.println(" ");
  } else {
    Serial.println("Failed to find peripheral");
    Serial.println(" ");
    return;
  }

  Serial.println("Looking for Peripheral Attributes");
  if (peripheral.discoverAttributes()) {
    Serial.println("Found Peripheral Attributes");
    Serial.println(" ");
  } else {
    Serial.println("Failed to find peripheral attributes");
    Serial.println(" ");
    peripheral.disconnect();
    return;
  }

  BLECharacteristic humidity1Characteristic = peripheral.characteristic(deviceServiceCharacteristicUuid);
    
  if (!humidity1Characteristic) {
    Serial.println("* Peripheral device does not have humidity characteristic!");
    peripheral.disconnect();
    return;
  } else if (!humidity1Characteristic.canWrite()) {
    Serial.println("* Peripheral does not have a writable humidity characteristic!");
    peripheral.disconnect();
    return;
  }
  
  while (peripheral.connected()) {
    int humidity1 = dht11.readHumidity();
    

    if (oldhumidity1 != humidity1) {  
      oldhumidity1 = humidity1;
      Serial.print("* Writing value to humidity characteristic: ");
      Serial.println(humidity1);
      humidity1Characteristic.writeValue((byte)humidity1);
      Serial.println("* Writing value to humidity1 characteristic done!");
      Serial.println(" ");
    }
  
  }
  Serial.println("- Peripheral device disconnected!");
}
  