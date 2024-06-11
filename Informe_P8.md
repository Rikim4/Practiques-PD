# INFORME PRÀCTICA 8

En aquesta pràctica, hem realitzat un codi molt simple que permet la comunicació bidireccional entre dos ports. El port serial estàndard (serial) i el port serial adicional(serial1).
Les dades rebudes en serial1 s'envien a serial i viceversa.

**CODI:**

```
# include <Arduino.h>
# define RXD1 17 
# define TXD1 18 

void setup() {
Serial.begin(115200, SERIAL_8O1);
Serial1.begin(115200, SERIAL_8O1, RXD1, TXD1);
}

void loop() {
  if(Serial1.available()>0){
  Serial.write(Serial1.read());
  }
  if(Serial.available()>0){
  Serial1.write(Serial.read());
  }
}
```

## Explicacio del codi  

En la funció **setup()**, s'inicialitza els dos ports serial. 
> Un serial amb una velocitat de 115200 baudios i una configuració de 8 bits de dades, sense paritat i 1 bit de parada (SERIAL_801).

> Un altre serial amb la mateixa configuracio de baudios i de format de dades, utilitzant els pins 17 i 18 per recepció i transmissió, respectivament.
---
En la funció **loop()**, es realitza, de forma continua:

> Si hi han dades disponibles per llegir en Serial1 (serial adicicional), es llegeixen les dades i s'escriuen en serial (serial estàndard).

> Si hi han dades disponibles per llegir en serial (serial estàndard), es llegeixenles dades i s'escriuen en Serial1 (serial adicional).
---

Aixo ens pot ser util, per exemple, per passar dades entre un dispositiu conectat al Serial1 i un ordinador conectat a traves del port USB, que es normalment que utilitza el Serial.