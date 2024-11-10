#include <DHT11.h>

DHT11 dht11(2); 

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
 
 int humidity1 = dht11.readHumidity();

 Serial.println(humidity1);

}