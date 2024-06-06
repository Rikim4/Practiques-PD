# Informe Pràctica 6

## Exercici pràctic 1 Lectura/escritura de memoria SD

**CODI**

```
#include <SPI.h>
#include <SD.h>

File myFile;

void setup()
{
  Serial.begin(9600);
  Serial.print("Iniciando SD ...");
  if (!SD.begin(4)) {
    Serial.println("No se pudo inicializar");
    return;
  }
  Serial.println("inicializacion exitosa");
 
  myFile = SD.open("archivo.txt");//abrimos  el archivo 
  if (myFile) {
    Serial.println("archivo.txt:");
    while (myFile.available()) {
    	Serial.write(myFile.read());
    }
    myFile.close(); //cerramos el archivo
  } else {
    Serial.println("Error al abrir el archivo");
  }
}

void loop()
{
  
}
```

1. Descriu la sortida del port serie

La sorida del port serie imprimeix el contingut del arxiu *archivo.txt*, si s'aconsegueix obrir correctament.Si hi ha algun error al obrir el arxiu o alinicialitzar la SD, imprimira un misatge d'error.

Si la tarjeta SD s'inicialitza correctament i el arxiu s'obre de forma correcte, la sortida del port serie mostrara el contingt del *arxiu.txt* línia per líniea. Cada liniea del arxiu s'enviara byte per byte a traves del port serie a una velocitat de transmisio de 9600 baudios, que es la velocitat de communicació especifica en la que funciona el serial.begin(9600).

La sortida en el monitor serial es veu algo semblant al seguent 

```
Iniciando SD ...Inicializació exitosa
archivo.txt:
Contingut de la primera línea
Contingut de la segona línea
Contingut de la tercera línea
...
```
On *contingut de la primera línea*,*contingut delasegona línea*... representen el contingut del arxiu.txt.Cada línia del arxiu es mostrara en una linia separada en el monitor serial.Si l'arxiu no te moltes línieas, s'imprimira cada una d'elles de manera secuencial fins que arribi al final del arxiu.

---

2. Explica el funcionament

Es declara un objecte myfile de tipos File. Aquest objecte s'utilitzara per interectuar amb l'arxiu de la tarjeta SD

El codi, comença iniciant la comunicació serial amb una velocitat detransmisió de 9600 baudios a traves del seria.begin (9600)

S'intenta inicialitzarla tarjeta SD en el pint 4 (begin(4)). Si l'inicialització es exitosa, s'imprimeix *inicialitzacio exitodsa* per el port serie, per el contrari, s'imprimeix*no s'ha pogut inicialitzar*.

El programa entra en el bucle while que s'executara mentres hi hagin dades disponibles en l'arxiu ( myFile.available()). En cada iteració del bucle, es llegeix un byte del arxiu amb myFile.read() i s'envia a traves del port serie amb serial.write().

Una vegada s'hagi llegit tot el contingut, es tenca l'arxiu amb myFile.close()


## Exercici Pràctic 2 - Lectura d'etiqueta RFID

Aques programa esta disenyat per llegir l'Uid deles targetes RFID utilitzant el modl MFRC522.

**CODI**

```
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN	9    //Pin 9 para el reset del RC522
#define SS_PIN	10   //Pin 10 para el SS (SDA) del RC522
MFRC522 mfrc522(SS_PIN, RST_PIN); //Creamos el objeto para el RC522

void setup() {
	Serial.begin(115200); //Iniciamos la comunicación  serial
	SPI.begin();        //Iniciamos el Bus SPI
	mfrc522.PCD_Init(); // Iniciamos  el MFRC522
	Serial.println("Lectura del UID");
}

void loop() {
	// Revisamos si hay nuevas tarjetas  presentes
	if ( mfrc522.PICC_IsNewCardPresent()) 
        {  
  		//Seleccionamos una tarjeta
            if ( mfrc522.PICC_ReadCardSerial()) 
            {
                  // Enviamos serialemente su UID
                  Serial.print("Card UID:");
                  for (byte i = 0; i < mfrc522.uid.size; i++) {
                          Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
                          Serial.print(mfrc522.uid.uidByte[i], HEX);   
                  } 
                  Serial.println();
                  // Terminamos la lectura de la tarjeta  actual
                  mfrc522.PICC_HaltA();         
            }      
	}	
}
```

1. Descriu la sortida del port serie

Cada vegada que una targeta RFID es detectada i llegida amb exit, la sortida del port serie sera de la forma:
```
objectivec
Copiar código
Card UID: XX XX XX XX
```
On XX representa els bytes del UID de la targeta en format hexadecimal, separats per espais. El proces es repeteix cada vegada que una nova targeta es presentada al lector RFID.

2. Explica el funcionament

Bueno, com sempre inicialitzem la comunicació serial, la del BUS SPI i tambe inicialitzem la del Modul MFRC522.
Aquesta ultima l'inicia per configura els pins necesaries i preparar el modul per la lectura de targetes.

A continuacio,mfrc522.PICC_IsNewCardPresent(), verifica si hi ha una nova tarjeta RFID aprop del lector. Si es detecta una targeta, llegeix el UID de la targeta RFID i ho emagatzema en l'escritura mfrc522.uid.
