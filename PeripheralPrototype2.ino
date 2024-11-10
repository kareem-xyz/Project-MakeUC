#include <ArduinoBLE.h>
#include <DHT11.h>

const char* deviceServiceUuid = "0937b3bb-fe53-4b5f-80c4-bb5ff2400018";
const char* deviceServiceCharacteristicUuid = "0937b3bb-fe53-4b5f-80c4-bb5ff2400019";

BLEService humidity1Service(deviceServiceUuid);
BLEUnsignedCharCharacteristic humidity1Char(deviceServiceCharacteristicUuid, BLERead | BLENotify);

DHT11 dht11(3);

void setup() {
Serial.begin(9600);
while (!Serial);

pinMode(LED_BUILTIN, OUTPUT);
if (!BLE.begin()) 
{
Serial.println("BLE STARTUP FAILED");
while (1);
}

BLE.setLocalName("Big Papa");
BLE.setAdvertisedService(humidity1Service);
humidity1Service.addCharacteristic(humidity1Char);
BLE.addService(humidity1Service);

BLE.advertise();
Serial.println("ON SIGHT!");
}

void loop() 
{
BLEDevice central = BLE.central();

if (central) 
{
Serial.print("TRANSMISSION BEGUN");
Serial.println(central.address());
digitalWrite(LED_BUILTIN, HIGH);

while (central.connected()) {

      int humidity1 = dht11.readHumidity();
      Serial.print("Humidity: ");
      Serial.print(humidity1);
      Serial.println("%");
      humidity1Char.writeValue(humidity1);
      delay(1000);

}
}
digitalWrite(LED_BUILTIN, LOW);
Serial.print("ROME HAS FALLEN");
Serial.println(central.address());
}