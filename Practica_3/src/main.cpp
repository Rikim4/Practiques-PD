#include <WiFi.h>
#include <WebServer.h>
#include <FS.h> // Incluir la biblioteca FS

// SSID & Password
const char* ssid = "*****"; // Enter your SSID here
const char* password = "*****"; // Enter your Password here
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




















/*
#include <WiFi.h>
#include <WebServer.h>
#include <SPIFFS.h>

// SSID & Password
const char* ssid = "MOVISTAR_9601"; // Enter your SSID here
const char* password = "9CFF1CB960E2216032B5"; //Enter your Password here
WebServer server(80); // Object of WebServer(HTTP port, 80 is defult)

// HTML & CSS contents which display on web server
String HTML = "<!DOCTYPE html>\"
<html>\
<body>\
<h1>Explora el Món</h1>

<p>Benvingut al nostre racó de viatges, on l'aventura mai s'aca ba! Descobreix destinacions emocionants, aconsegueix consells pràctics i submergeix-te en històries fascinants de viatgers de tot el món.</p>

<h2>Destinacions Destacades</h2>

<h3>París, França</h3>
<img src="https://cdn-imgix.headout.com/media/images/c90f7eb7a5825e6f5e57a5a62d05399c-25058-BestofParis-EiffelTower-Cruise-Louvre-002.jpg" alt="Torre Eiffel">
<p>Descobreix la màgia de la Ciutat de la Llum. Des de la majestuosa Torre Eiffel fins als encantadors cafès a Montmartre, París és una experiència única.</p>

<h3>Machu Picchu, Perú</h3>
<img src="https://historia.nationalgeographic.com.es/medio/2023/01/25/istock_bc3b04ec_930824730_230125152421_1280x853.jpg" alt="Machu Picchu">
<p>Explora les místiques ruïnes incas al cim dels Andes. Navega pel Camí Inca i maravella't amb l'arquitectura ancestral.</p>

<h3>Kioto, Japó</h3>
<img src="https://media.tacdn.com/media/attractions-content--1x-1/10/7a/ea/31.jpg" alt="Kioto">
<p>Submergeix-te en l'elegància tradicional japonesa. Descobreix temples mil·lenaris, jardins zen i l'autèntica cultura geisha a Kioto.</p>

<h2>Consells per Viatjar</h2>

<h3>Fes la Maleta Intel·ligentment</h3>
<p>Viatja lleuger però preparat. Fes una llista d'articles essencials i assegura't de tenir adaptadors de corrent i productes de cura personal.</p>

<h3>Explora la Cultura Local</h3>
<p>Investiga sobre les costums locals. Aprèn algunes frases bàsiques de l'idioma local i respecta les tradicions per a una experiència enriquidora.</p>

<h2>Històries d'Aventures</h2>

<h3>Travessant l'Amazònia</h3>
<img src="https://img2.rtve.es/i/?w=1600&i=1619727769660.jpg" alt="Amazònia">
<p>Embarca en una inoblidable expedició per la selva amazònica. Descobreix la flora i fauna úniques mentre navegues pels seus rius caudalosos.</p>

<h3>Travessa per Europa en Motxilla</h3>
<img src="https://estaticos-cdn.prensaiberica.es/clip/0e9a97a8-679b-4fa0-b0ee-59cc8301103a_source-aspect-ratio_default_0.jpg" alt="Europa">
<p>Recorre Europa amb una motxilla i un mapa a la mà. Des dels Alps suïssos fins a les platges mediterrànies, cada racó ofereix una nova aventura.</p>

<h2>Recomanacions Gastronòmiques</h2>

<h3>Delícies Parisines</h3>
<p>Gaudeix de croissants recentment fornejats i formatge francès a les encantadores brasseries parisenques. No et perdis l'oportunitat de tastar macarons a Ladurée.</p>

<h3>Sabors de Kioto</h3>
<p>Explora la rica tradició culinària de Kioto. Prova el kaiseki, una experiència gastronòmica japonesa refinada i plena de sabors autèntics.</p>

<h2>Planificació del Viatge</h2>

<h3>Recursos Útils</h3>
<ul>
    <li><a href="https://www.parisinfo.com/">Lloc web de turisme de París</a></li>
    <li><a href="https://www.machupicchu.gob.pe/">Informació sobre Machu Picchu</a></li>
    <li><a href="https://www.japan-guide.com/e/e2158.html">Guia de viatge de Kioto</a></li>
</ul>

<h3>Eines de Viatge</h3>
<p>Descarrega aplicacions útils com Google Maps, Duolingo i Tripadvisor per facilitar la teva aventura.</p>

<p><strong>Esperem que aquesta guia t'inspiri i t'ajudi a planificar el teu proper viatge. Que les teves aventures siguin inoblidables!</strong></p>

</html>";

// Handle root url (/)
void handle_root() {
    File file = SPIFFS.open("/prova.html", "r");
    if (!file) {
        Serial.println("Failed to open file for reading");
        return;
    }

    String htmlContent;
    while(file.available()){
        htmlContent += char(file.read());
    }
    file.close();

    server.send(200, "text/html", htmlContent);
}


void setup() {
    Serial.begin(115200);
    if(!SPIFFS.begin(true)){
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
    }

    Serial.println("Try Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected successfully");
    Serial.print("Got IP: ");
    Serial.println(WiFi.localIP());

    server.on("/", handle_root);

    server.begin();
    Serial.println("HTTP server started");
    delay(100);
}


void loop() {
    server.handleClient();
}
*/
