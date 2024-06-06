# Informe Pràctica 3 - WIFI y BLUETOOTH

## Practica A generación de una pagina web

En quan aquest apartat, hem relitzat un codi on ens conectem a la red de la nostre casa y d'aquesta manera generar una IP la qual genereria una pagina web que haguesim programat.

**Codi en el que vem generar amb una web simple:**

```

#include <WiFi.h>
#include <WebServer.h>

// SSID & Password
const char* ssid = "MOVISTAR_PLUS9601"; // Ingresa tu SSID aquí
const char* password = "948571838"; // Ingresa tu contraseña aquí

WebServer server(80); // Objeto de WebServer (puerto HTTP, 80 es el predeterminado)

// HTML contenido que se muestra en el servidor web
String HTML = "<!DOCTYPE html>\
<html lang='es'>\
<head>\
    <meta charset='UTF-8'>\
    <meta name='viewport' content='width=device-width, initial-scale=1.0'>\
    <title>Tipos de Guitarras</title>\
</head>\
<body>\
    <h1>LA GUITARRA</h1>\
    \
    <h2>Introducción</h2>\
    <p>La guitarra es uno de los instrumentos musicales más populares del mundo. A lo largo de los siglos, ha evolucionado en diversos tipos, cada uno con sus propias características y aplicaciones.</p>\
    \
    <h2>Historia</h2>\
    <p>La historia de la guitarra se remonta a miles de años atrás. Se cree que sus orígenes se encuentran en la antigua Persia, donde se desarrollaron instrumentos de cuerda similares. Con el tiempo, la guitarra se ha transformado y adaptado en diferentes culturas y épocas, dando lugar a una amplia variedad de estilos y diseños.</p>\
    \
    <h2>Tipos de Guitarras</h2>\
    <p>A continuación se presentan algunos de los tipos más comunes de guitarras:</p>\
    <ul>\
        <li><strong>Guitarra Acústica:</strong> Perfecta para tocar en cualquier lugar sin necesidad de amplificación.</li>\
        <li><strong>Guitarra Eléctrica:</strong> Ideal para estilos de música más eléctricos y se puede conectar a amplificadores para aumentar su sonido.</li>\
        <li><strong>Guitarra Clásica:</strong> Con cuerdas de nylon, es adecuada para estilos de música clásica y flamenco.</li>\
        <li><strong>Guitarra Semiacústica:</strong> Combina características de la guitarra eléctrica y la acústica, proporcionando un sonido más cálido.</li>\
        <li><strong>Guitarra de 12 Cuerdas:</strong> Tiene el doble de cuerdas que una guitarra estándar, lo que produce un sonido más rico y completo.</li>\
        <li><strong>Guitarra Resonadora:</strong> Utiliza un cono metálico para amplificar el sonido, siendo común en estilos de blues y country.</li>\
    </ul>\
    \
    <h2>Cómo Elegir la Guitarra Correcta</h2>\
    <p>Al elegir una guitarra, es importante considerar factores como el estilo de música que deseas tocar, tu nivel de experiencia y tu presupuesto. También es recomendable probar diferentes guitarras antes de tomar una decisión final.</p>\
    \
    <h2>Mantenimiento y Cuidado</h2>\
    <p>Para mantener tu guitarra en óptimas condiciones, es importante limpiarla regularmente, cambiar las cuerdas cuando sea necesario y almacenarla en un lugar seguro y adecuado.</p>\
    \
    <h2>Conclusión</h2>\
    <p>La guitarra es un instrumento versátil y emocionante que ha capturado la imaginación de músicos y aficionados de todo el mundo. Con una amplia variedad de tipos disponibles, siempre hay una guitarra adecuada para cada persona y estilo de música.</p>\
</body>\
</html>";

// Manejar la URL raíz (/)
void handle_root() {
    server.send(200, "text/html", HTML);
}

void setup() {
    Serial.begin(115200);
    Serial.println("Intentando conectar a ");
    Serial.println(ssid);
    
    // Conectar al modem de Wi-Fi
    WiFi.begin(ssid, password);
    
    // Verificar que se haya conectado a la red Wi-Fi
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    
    Serial.println("");
    Serial.println("Conexión Wi-Fi exitosa");
    Serial.print("IP asignada: ");
    Serial.println(WiFi.localIP()); // Mostrar la IP de ESP32 en serie
    
    server.on("/", handle_root);
    server.begin();
    Serial.println("Servidor HTTP iniciado");
    delay(100);
}

void loop() {
    server.handleClient();
}

```

1. Realitza l'informe de funcionament aixi com la sortida per la terminal i la visualitzacio de la conecció a la pagina web amb un navegador

Basicament el codi configura un servido web en el micro en mode estació (STA). Permet que els altres dispositius conectats a la mateixa red wi-fi accedeixin a una pagina web que esta al micro. 

S'inclueixen les llibreries necesaries per la conectivitat wi-fi i el servidor web

Se incluyen las librerías necesarias para manejar la conectividad Wi-Fi y el servidor web i es defineix les credencials de la xarxa.

S'inicialitza la comunicacio serie i es conecta el micro ala xarxa ambwifi.begin(). Una vegada conectada, s'imprimeix l'IP asignada al ESP32. ES configura el servidor per organitzar solicituds en l'arrel de la ruta (/) cridant a handle_root i s'inicialitza el servidor web.

Es crida continuament  a server.handleClient() per organitzar les solicituds entrants.

Es definex una cadena amb el contingur HTML que es mostrara en la web

Una vegada es carregi i s'executi el programa la sortida en el monitor serie sortira:

```
Try Connecting to 
*****
.....
WiFi connected successfully
Got IP: 192.168.1.10
HTTP server started

```
2. Modificar la pagina web generant un fitxer HTML amb l'editor de Mark Down i incloure'l en el codi. Incluir el fitxer adicional 


En aquest apartat he intentat el proposat, he intentat fer un codi en el que jo li adjunt-hi un fitxer HTML exter i que generi l'IP i tot igual, pero no m'en he ensortit.

Aquest es el codi que he genereat per a intentar-ho:

```
#include <WiFi.h>
#include <WebServer.h>
#include <FS.h> // Incluir la biblioteca FS

// SSID & Password
const char* ssid = "MOVISTAR_PLUS9601"; // Enter your SSID here
const char* password = "948571838"; // Enter your Password here
WebServer server(80); // Object of WebServer(HTTP port, 80 is default)

// Handle root url (/)
void handle_root() {
    // Abrir el archivo en modo lectura
    File file = SPIFFS.open("/web_viatges.html", "r");

    if (!file) {
        Serial.println("Error al abrir el archivo HTML");
        return;
    }

    // Enviar el contenido del archivo como respuesta
    server.streamFile(file, "text/html");

    // Cerrar el archivo
    file.close();
}

void setup() {
    Serial.begin(115200);
    Serial.println("Try Connecting to ");
    Serial.println(ssid);

    // Montar el sistema de archivos SPIFFS
    if (!SPIFFS.begin(true)) {
        Serial.println("Error al montar el sistema de archivos SPIFFS");
        return;
    }

    // Connect to your Wi-Fi modem
    WiFi.begin(ssid, password);
    
    // Check Wi-Fi connection
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected successfully");
    Serial.print("Got IP: ");
    Serial.println(WiFi.localIP()); // Show ESP32 IP on serial

    server.on("/", handle_root);
    server.begin();
    Serial.println("HTTP server started");
    delay(100);
}

void loop() {
    server.handleClient();
}
```
He intentat utilitzar la llibreria FS.h que es la que em recomenaven en varis llocs pero no m'en he ensortit. Al guit hub tambe deixare la web en HTML que vaig crear.


## Practica B comunicación bluetooth con el movil

Aquesta practica no la he pogut provar del tot ja que tinc problemes amb el mobil de cara a aquesta practica.

Basicament el codo transforma un ESP32 en un dispositiu bluetooth Serial (SPP). La seva funcio es enviar i rebre dades entre els ports serie i la conecció bluetooth. Al iniciar-se, espera dades tant el port serie com el Bluetooth, retransmiten-se en les dos direccions

**CODI**

```
    #include "BluetoothSerial.h"

    #if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
    #error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
    #endif

    BluetoothSerial SerialBT;

    void setup() {
      Serial.begin(115200);
      SerialBT.begin("ESP32test"); //Bluetooth device name
      Serial.println("The device started, now you can pair it with bluetooth!");
    }

    void loop() {
      if (Serial.available()) {
        SerialBT.write(Serial.read());
      }
      if (SerialBT.available()) {
        Serial.write(SerialBT.read());
      }
      delay(20);
    }
```





