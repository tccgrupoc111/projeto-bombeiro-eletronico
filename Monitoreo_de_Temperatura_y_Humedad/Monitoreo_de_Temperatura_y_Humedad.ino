#include "DHT.h"
#include "BluetoothSerial.h"

#define DHTPIN 4    

#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);


#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

void setup() {
  SerialBT.begin("BluetoothESP32");
  dht.begin();
  
}

void loop() {
  
  delay(1000);

  float t = dht.readTemperature();
  float h = dht.readHumidity();
  

  if (isnan(t) || isnan(h)) {
    return;
  }

  SerialBT.print(t);
  SerialBT.print(";");
  SerialBT.print(h);
  SerialBT.println(";");

}
