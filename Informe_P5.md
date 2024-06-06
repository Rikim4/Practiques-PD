# INFORME PRÀCTICA 5

## Exercici Pràctic 1
En aquest primer exercici pràctic, hem realitzat un programa escaner amb el I2C on les resistencies de pull-ip depenen del numero de dispositius 

CODI:
```
#include <Arduino.h>
#include <Wire.h>
void setup()
{
 Wire.begin();
 Serial.begin(115200);
 while (!Serial); // Leonardo: wait for serial monitor
 Serial.println("\nI2C Scanner");
}
void loop()
{
 byte error, address;
int nDevices;
 Serial.println("Scanning...");
 nDevices = 0;
 for(address = 1; address < 127; address++ )
 {
 // The i2c_scanner uses the return value of
 // the Write.endTransmisstion to see if
 // a device did acknowledge to the address.
 Wire.beginTransmission(address);
 error = Wire.endTransmission();
 if (error == 0)
 {
 Serial.print("I2C device found at address 0x");
 if (address<16)
 Serial.print("0");
 Serial.print(address,HEX);
 Serial.println(" !");
 nDevices++;
 }
 else if (error==4)
 {
 Serial.print("Unknown error at address 0x");
 if (address<16)
 Serial.print("0");
 Serial.println(address,HEX);
 } 
 }
 if (nDevices == 0)
 Serial.println("No I2C devices found\n");
 else
 Serial.println("done\n");
 delay(5000); // wait 5 seconds for next scan
}
```


### Descriu la sortida del port serie:

La sortida del port serie propociona informacio sobre els dispositius I2C trobats durant l'escaneix.

Al començar e programa, comença imprimint *"scaning"* per indicar que esta inician el proces.
Per a cada diercció I2C en el rang de 1 a 127, el programa intenta iniciar la comunicacio amb el dispositiu amb aquella direcció, si no hi ha ha hagut un ningun error, imprimeix un misatge indicant que s'ha trobat un dispositiu amb aquella direccio.

*"I2C device found at address 0x3F !"*

En cas de que hi hagues algun error durant la comunicació amb algun dispositiu  en una direcció determinada, apareix un misatge d'error indicant el tipos d'error i la direccio.

*"Unknown error at address 0x42"*

Una vegada s'han escanejat totes les direccions en el rang especificat, s'imprimeix un misatge indicant que l'escaneix s'ha finalitzat.
Si s'han trobat dispositius durant l'escaneix, el misatge serà *done*, en cas contrari *no I2C devices found*

### Explicació del funcionament:


En la funció setup(), s'inicialitza la comunicacio I2C mitjançant wire.begin() i la comunicaio serial amb serial.begin(115200). S'espera  a que s'obri el monitor serial amb *while (!Serial)*, ja que es especific per les plaques com Arduino. Despres s'imprimeix un mustage indicant que l'escaner I2C esta preparat.

En la funció loop(), s'inici el escaneix del bus I2C. Per a cada direcció posible en el rang del 1 a 127.

* S'intenta iniciar una transmisio I2C fins aquella direccio utilitzant wire.beginTransmission(adressa).
* Es verifica si hi ha algun error en la comunicació mitjançant wire.endTransmission(). Llavors, si el resoltat es 0, significa que no hi han haguts errors, per tant hi ha un dispsitiu en aquella direcció.
S'incrementa el contador de dispositius trobats ( nDevices ) i s'imprimeix un misatge indicant la direccio del dispositiu trobat.

Despres d'imprimir els resoltats del escaneix, el programa espera 5 segons abans de començar el seguient scaneix. Aquest procés es repeteix coninuament ja que esta en un bucle infinit i peret escanejar el bus I2C repetitivament per detectar qualsevol canvi en els dispositius conectats.

La comunicació serial s'utilitza per mostrar els resoltats del escaner en el monitor serial, el que ens permet visualitzar quins dispositius estan conectats al bus I2Ci en quina direccio estan ubicats.


## Exercici Pràctic 2

1. Realitza un programa que utilitzi un dispositiu I2C com per exemple algun dels seguents

> He realitzat un programa en el que a traves d'un display LCD podem veure el missatge programat

Aquest crea instancia del LCD amb la direcció del dispositiu I2C ( 0x27 ) i les dimensions definides.
S'inicialitza la LCD i s'encen la llum de fons de la LCS.
Es mostre el misatge "HOLA MUNDO" en la primera fila durant 1 segon i despres borra la pantalla y surt a la seguent fila un altre misatge.
Aquest cicle es repeteix indefinidament, mostrant cada missatge secuencialment.

