# Informe Pràctica RGB

Aquest codi controla el led RGB de la placa ESP32 i mostra informacio del micro a traves del port serie.

Basicament utilitzem la llibreria  Adafruit_NeoPixel i definim el pin LED i el nimero de LEDs (nomes n'hi ha un).
Inicialitzel'objecte pixel i configura la communicació serie per imprimir informacio del micro( model, revisió, nuclis...)

Encen el LED vermell, verd i blau amb un retard de 500 ms entre cada color i imprimeix "R", "G" o "B" en el monitorseie per indicar el colo actual delLED
loop():

ES un programa simple pero es per probar el LED del micro

**CODDI**

```
#include <arduino.h>
#include <Adafruit_NeoPixel.h>  //Incluimos la librería Adafruit_NeoPixe

// pin del led RGB en PCB
#define PIN 48  // ESP32S3 Generic -n8r2-

// Un solo led en PCB
#define NUMPIXELS 1

// Inicializamos el objeto "pixels"
// Argumento 1 = número de pixeles 
// Argumento 2 = número del pin de datos
// Argumento 3 = tipo de pixel: NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
// Time (en milliseconds) pausa entre pixels
#define DELAYVAL 500 

void setup() {
  delay(500);
  // Inicializamos el objeto pixels
  pixels.begin(); 
  Serial.begin(115200);
  delay(500);
  // Información chip
  Serial.println("\n\n================================");
  Serial.printf("Chip Modelo: %s\n", ESP.getChipModel());
  Serial.printf("Chip Revision: %d\n", ESP.getChipRevision());
  Serial.printf("E %d core\n", ESP.getChipCores());
  Serial.printf("Flash Chip capacidad: %d \n", ESP.getFlashChipSize());
  Serial.printf("Flash Chip velocidad: %d \n", ESP.getFlashChipSpeed());

  esp_chip_info_t chip_info;
  esp_chip_info(&chip_info);
  Serial.printf("\nCaracteristicas:\n %s\n %s\n %s\n %s\n %s\n",
      (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "flash en ESP32" : "Sin flash en ESP32",
      (chip_info.features & CHIP_FEATURE_WIFI_BGN) ? "2.4GHz WiFi" : "Sin Wifi",
      (chip_info.features & CHIP_FEATURE_BLE) ? "Bluetooth LE" : "Sin Bluetooth LE",
      (chip_info.features & CHIP_FEATURE_BT) ? "Bluetooth" : "Sin Bluetooth",
      (chip_info.features & CHIP_FEATURE_IEEE802154) ? "IEEE 802.15.4" : "NO IEEE 802.15.4");
  // MAC Address
  String MACString = "";
  uint64_t chipid = ESP.getEfuseMac(); 
  for (int i=0; i<6; i++) {
    if (i > 0) MACString.concat(":");
    uint8_t Octet = chipid >> (i * 8);
    MACString.concat(String(Octet, HEX));
  }
  Serial.println("MAC: " + MACString);
}

void loop() {
  // apagamos
  pixels.clear(); 
  pixels.show();
  Serial.println("");
  delay(1000); 
  
  // encendemos con el color rojo
  pixels.setPixelColor(0, pixels.Color(150, 0, 0));
  // enviamos
  pixels.show();   
  Serial.println("R");
  delay(DELAYVAL); 
  
  // encendemos con el color verde, con brillo moderado
  pixels.setPixelColor(0, pixels.Color(0, 150, 0));
  pixels.show();    
  Serial.println("G");
  delay(DELAYVAL); 
  
  // encendemos con el color azul, con brillo moderado
  pixels.setPixelColor(0, pixels.Color(0, 0, 150));
  pixels.show();     
  Serial.println("B");
  delay(DELAYVAL); 
  
}
```