# Pràctica del semaphore

> En la pràctica 4, tambés ens demanava un exercici pràctic 2 en el que consistia en realitzar un **semaphore** un programa que utulitzi dos tasques, una que ensengui un led i una altre que l'apagui i aquestes tasques han d'estar sincronitzades.


* **Codi utilitzat**
* **Explicació del codi**
## Codi

```
#include <arduino.h>

long debouncing_time = 150; 
SemaphoreHandle_t interruptSemaphore;
volatile unsigned long last_micros;

void interruptHandler() {
xSemaphoreGiveFromISR(interruptSemaphore, NULL);
}

void debounceInterrupt() {
if((long)(micros() - last_micros) >= debouncing_time * 1000) {
interruptHandler();
last_micros = micros();
}
}

void TaskLed(void *pvParameters)
{
(void) pvParameters;
pinMode(8, OUTPUT);
while(1) {
if (xSemaphoreTake(interruptSemaphore, portMAX_DELAY) == pdPASS) {
digitalWrite(8, !digitalRead(8));
}  
}
}

void TaskLed1(void *pvParameters)
{
(void) pvParameters;
pinMode(7, OUTPUT);
while(1) {
digitalWrite(7, HIGH);
vTaskDelay(200 / portTICK_PERIOD_MS);
digitalWrite(7, LOW);
vTaskDelay(200 / portTICK_PERIOD_MS);
}
}
void setup() {
  pinMode(2, INPUT_PULLUP);
  xTaskCreate(TaskLed,  "Led", 128, NULL, 0, NULL );
xTaskCreate(TaskLed1,  "LedBlink", 128, NULL, 0, NULL );
  interruptSemaphore = xSemaphoreCreateBinary();
  if (interruptSemaphore != NULL) {
    attachInterrupt(digitalPinToInterrupt(2), debounceInterrupt, LOW);
  }
}
void loop() {}
```
## Explicació del Codi

Per començar el codi he declarat les llibreries necesaries. Seguidament s'ha declarat una variable de tipo *SemaphoreHandle_t* per emagatzemar els valors del semaphore.

>SemaphoreHandle_t interruptSemaphore;

1. **void interruptHandler():**
   Aquesta funció s'executa cuan hi ha una interrupció. Notifica a la tasca que la interrupció s'ha realitzat. Utilitza la funió *xSemaphoreGiveFromISR()* per donar al semafor interruptSemaphore desde una ISR, el qual permet a una tasca que esta esperant el semafor a procesar la seva execució.
   
2. **debounceInterrupt()**
S'encarrega dels rebots del boto per evitar activacions multiples degut a fluctuacions electriques. Aquesta funció compara el temps actual en microsegons amb el temps del ultim rebot emagatzemat en *last_micros*. Si ha passat el temps de rebot (debouncing_time), es crida *interruptHandler()* per notificar que s'ha presionat el boto i actualtzar *last_micros*.

4. **TaskLed**
Controla el LED conectat al pin 8. S'espera fins que es lliberi el semafor interruptSemaphore, indicant que s'ha presionat el boto. La tasca esta en un bucle infinit on espera indefinidament la disponibilitat del semafor, i quan el semafor esta lliure, inverteix l'estat del led.

5. **TaskLed1**
Un LED conectat al pin 7 fagi pampallugues e intervals regulars. La tasca esta en un bucle indefinit on encen el LED, espera 200 milisegons i despres l'apaga i espera de nou uns altres 200 milisegons utilitzant la funcio vTaskDelay() per proporcionar retards precisos.

6. **Void setup()**  es crea dos tasques (TaskLEDiy TaskLED1 ), utilitzan l'API xTaskCreate() i desores es crea un semafor utilitzant *xSemaphoreCreateBinary()*. Creo una tasca amb les mateixes prioritats i despres es juga amb aquest numero. Ademés, configuro el pin 2 com entrada i s'habilita la resitencia pull-up interna i conete el pin d'interrupció.


**EL Void loop() estara buit**