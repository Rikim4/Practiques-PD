# Informe Pràctica 7 - Buses de comunicació III (I2S)
## Exercici pràctic 1 - Reproducció desde la memoria interna

```
#include "AudioGeneratorAAC.h"
#include "AudioOutputI2S.h"
#include "AudioFileSourcePROGMEM.h"
#include "sampleaac.h"

AudioFileSourcePROGMEM *in;
AudioGeneratorAAC *aac;
AudioOutputI2S *out;

void setup(){
  Serial.begin(115200);

  in = new AudioFileSourcePROGMEM(sampleaac, sizeof(sampleaac));
  aac = new AudioGeneratorAAC();
  out = new AudioOutputI2S();
  out -> SetGain(0.125);
  out -> SetPinout(4,5,6);
  aac->begin(in, out);
}

void loop(){
  if (aac->isRunning()) {
    aac->loop();
  } else {
    aac -> stop();
    Serial.printf("Sound Generator\n");
    delay(1000);
  }
}
```
___

1. Descriu la sortida per el port serie

La sortida al port serie es produeix a la funció loop() cuan el reproductor del audio ha finalitzat. El misatge de sortida es "Sound Generator"

Elprograma espera 1000 milisegons abans de començar de nou la reproduccio del audio.

Per tant, cada vegada que es completa la reproducció del arxiu d'audio es veura "Sound Generator" impres en el monitor serial seguit d'un retras d'un segon abans de que el programa torni a intentarreproduir l'audio.
___
1. Explica el funcionament
 
Aquest reprodueix un arxiu d'audio AAC utilitzant la biblioteca AudioGeneratorAAC.

Es creen tres objectes globals ( in, aac i out) que representen respectivament la font d'arxiu d'audio.

Com normalment, inicialitzem la comunicació serial i establim el volum de sortida i la configuracio dels pins de sortida d'audio.

Es crida al begin() del objecte aac pasant la font d'arxiu d'audio i la sortida d'audio com parametres per iniciar la reproduccio del arxiu AAC

Es comprova si la reproducció del audio esta en curs utilitzant isRunning() del objecte aac, i si esta en curs, crida loop() per continuar reproduint l'audio

Quan la reproduccióhagi finalitzat, es para el genereador d'audio cridant a stop().


##  Exercici Pràctic 2 - Reproduir un arxiu wave en el micro desde una SD externa

```
#include "Audio.h"
#include "SD.h"
#include "FS.h"

// Digital I/O used
#define SD_CS         39
#define SPI_MOSI      35
#define SPI_MISO      37
#define SPI_SCK       36
#define I2S_DOUT      6
#define I2S_BCLK      4
#define I2S_LRC       5

Audio audio;

void setup(){
    pinMode(SD_CS, OUTPUT);
    digitalWrite(SD_CS, HIGH);
    SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI);
    Serial.begin(115200);
    SD.begin(SD_CS);
    audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
    audio.setVolume(10); // 0...21
    audio.connecttoFS(SD,"arkano.wav");
}

void loop(){
    audio.loop();
}

// optional
void audio_info(const char *info){
    Serial.print("info        "); Serial.println(info);
}
void audio_id3data(const char *info){  //id3 metadata
    Serial.print("id3data     ");Serial.println(info);
}
void audio_eof_mp3(const char *info){  //end of file
    Serial.print("eof_mp3     ");Serial.println(info);
}
void audio_showstation(const char *info){
    Serial.print("station     ");Serial.println(info);
}
void audio_showstreaminfo(const char *info){
    Serial.print("streaminfo  ");Serial.println(info);
}
void audio_showstreamtitle(const char *info){
    Serial.print("streamtitle ");Serial.println(info);
}
void audio_bitrate(const char *info){
    Serial.print("bitrate     ");Serial.println(info);
}
void audio_commercial(const char *info){  //duration in sec
    Serial.print("commercial  ");Serial.println(info);
}
void audio_icyurl(const char *info){  //homepage
    Serial.print("icyurl      ");Serial.println(info);
}
void audio_lasthost(const char *info){  //stream URL played
    Serial.print("lasthost    ");Serial.println(info);
}
void audio_eof_speech(const char *info){
    Serial.print("eof_speech  ");Serial.println(info);
}
```
___

1. Descriu la sortida del port serie

(OPCIONAL)
La sortida del port serie en aquest codi proporciona informació util sobre el progres de reproduccio d'audio.

> INFO: Proporciona informacio general sobre l'estat del audio, com quant s'inicia la reproducció

> ID3DATA: Si l'arxiu conte metadades ID3 les mostrara. (titol, artista...)

> EOF_MP3: Ens indica que ha arribat al final del arxiu d'audio MP3

>STATION: Diu si l'arxiu d'audio provee d'una estació de radio en linia o te informació similar integrada

> STREAMINFO: Si s'esta produint un arxiu d'audio en striming, proporciona informacio sobre la transmisió, com la calitat d'audio o la tasa de bits

> STREAMTITLE: Mostra el titol actual de la pista

> BITRATE: Mostra la tasa de bits del arxiu d'audio que s'esta reproduint

> COMMERCIAL: En cas de que hi hagues un anunci en l'arxiu, doncs aquesta linia pot mostrar la duracio d'els anuncis

> ICYURL: Aquesta linia mostraria l'enllas asociat en cas de que hi hagues.

> LASTHOST: Mostra l'URL del flux d'audio que esta reproduint

> dawEOF_SPEECH: Ens indica que ha arribat al final del arxiu d'audio de tipo discurs.


___
   1. Explica el funcionament

Es un programa que reprodueix un arxiu d'audio. En el meu cas el "arkano.wav" el qual el llegeix desde una targeta SD utilitzant un modul d'audio i un microcontrolador.

Definim els pins pe la comunicacio SPI i la sortida d'audio I2C.
S'inicialitzen aquests pins i configurem la sortida d'audio i el volum

S'executa el audio.loop() que es el q controla la reproduccio del arxiu d'audio. 

Es defineixen algunes funcios de retorn de crida que s'utilitzen per imprimir informacio com he explicat en el punt 1
