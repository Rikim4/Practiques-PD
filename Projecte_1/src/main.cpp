#include <Arduino.h>
#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include <FS.h>
#include <LiquidCrystal_I2C.h>
#include <Audio.h>

const int chipSelect = 5; // Pin CS de la tarjeta SD
const int SPEAKER_PIN = 3; // Pin del altavoz

LiquidCrystal_I2C lcd(0x27, 16, 2); // Dirección I2C y tamaño del display

AudioPlaySdWav audioPlayer;

void setup() {
  Serial.begin(9600);
  
  // Inicializar el display LCD
  lcd.init();
  lcd.backlight();
  
  // Inicializar la tarjeta SD
  if (!SD.begin(chipSelect)) {
    Serial.println("Error al inicializar la tarjeta SD.");
    return;
  }
  
  Serial.println("Tarjeta SD inicializada correctamente.");
  
  // Inicializar el altavoz
  pinMode(SPEAKER_PIN, OUTPUT);
}

void loop() {
  // Limpiar el display LCD
  lcd.clear();
  
  // Mostrar el contenido de la tarjeta SD en el display LCD
  showDirectoryOnLCD("/");
  
  // Reproducir la primera canción encontrada en la tarjeta SD
  playFirstSong();
  
  delay(5000); // Esperar 5 segundos antes de volver a mostrar el contenido y reproducir otra canción
}

void showDirectoryOnLCD(String directory) {
  File root = SD.open(directory);
  
  if (!root) {
    Serial.println("Error al abrir el directorio.");
    return;
  }
  
  lcd.setCursor(0, 0);
  lcd.print("Contenido de la SD:");
  
  while (true) {
    File entry = root.openNextFile();
    
    if (!entry) {
      // No más archivos
      break;
    }
    
    // Imprimir el nombre del archivo en el display LCD
    lcd.setCursor(0, 1);
    lcd.print(entry.name());
    
    entry.close();
  }
  
  root.close();
}

void playFirstSong() {
  // Abre el primer archivo de audio encontrado en la tarjeta SD
  File root = SD.open("/");
  while (true) {
    File entry =  root.openNextFile();
    if (!entry) {
      // No más archivos
      Serial.println("No se encontraron archivos de audio.");
      return;
    }
    // Reproduce el primer archivo que tenga la extensión .wav
    if (strstr(entry.name(), ".wav")) {
      Serial.print("Reproduciendo: ");
      Serial.println(entry.name());
      audioPlayer.play(entry.name());
      return;
    }
    entry.close();
  }
}
