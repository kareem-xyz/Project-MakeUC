#include <ArduinoBLE.h>
#include <DHT11.h>
BLEService humidity1Service("180F");
BLEUnsignedCharCharacteristic humidity1Char("2A19", BLERead | BLENotify);

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