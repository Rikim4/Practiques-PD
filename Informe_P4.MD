# PRÀCTICA 4

**L'objectiu de la pràctica es compendre el funcionament d'un sistema operatiu en temps real. Per tant, generarem varies tasques u veurem com s'executen dividint el tems d'us de la CPPU**

___
### EXERCICI PRÀCTIC 1

```
#include <Arduino.h>

void anotherTask( void * parameter );
void ThirdTask( void * parameter );

void setup()
{
  Serial.begin(115200);
  /* we create a new task here */
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(19, OUTPUT);
  xTaskCreate(
    anotherTask, /* Task function. */
    "another Task", /* name of task. */
    1000, /* Stack size of task */
    NULL, /* parameter of the task */
    1, /* priority of the task */
    NULL); /* Task handle to keep track of created task */

    xTaskCreate(
    ThirdTask, /* Task function. */
    "Third Task", /* name of task. */
    1000, /* Stack size of task */
    NULL, /* parameter of the task */
    1, /* priority of the task */
    NULL); /* Task handle to keep track of created task */
}
/* the forever loop() function is invoked by Arduino ESP32 loopTask */
void loop()
{
  Serial.println("this is ESP32 Task");
  vTaskDelay(300);
    digitalWrite(LED_BUILTIN, HIGH);
    vTaskDelay(300);
    digitalWrite(LED_BUILTIN, LOW);
    vTaskDelay(300);
}


/* this function will be invoked when additionalTask was created */
void anotherTask( void * parameter )
{
/* loop forever */
  for(;;)
{
    Serial.println("this is another Task");
    vTaskDelay(10000);
}
}
void ThirdTask( void * parameter )
{
/* loop forever */
  for(;;)
{
    Serial.println("this is the third Task");
    vTaskDelay(1000);
    digitalWrite(19, HIGH);
    vTaskDelay(1000);
    digitalWrite(19, LOW);
    vTaskDelay(1000);
}

/* delete a task when finish, this will never happen because this is infinity loop */
vTaskDelete( NULL );
}

```

***ENS DEMANA:***

1. **Descriure la sortida per el port serie**

La sortida del port serie es una seqüencia de mistages que si'imprimeixen al monitor.
* Desde la funció *loop()* 
  * S'escriu "this is ESP32 Task" constantment amb un retras de 300 milisegons entre cada impresió
  * Ademes el LED del micro fara pampallugues tambe amb un interval de 300 milisegons
* Desde la funció *anotherTask()*
  * S'escriu "this is another Task" constantment amb un retras de 10 segons entre cada impresiól
  *  El mistage s'imprimeix en paral·lel amb els misatges de la funcio*loop()*.
* Desde la funció *ThirdTask()*
  * S'escriu "this is the third Task" constantment amb un retras 1 segon entre cada impresió.
  * Ademes, el pin 19 s'alternara entre alt i baix amb un interval 1 segon entre cada estat.
  * Aquestes estaran en paral·lel amb les accions i els misatges de les funcions anteriors.
  
2. **Explicar el funcionament**

En general trobem 4 "funcions" principals
* La configuració inical  **setup()**
* El Bucle Principal **loop()**
* La tasca **anotherTask()**
* La tasca **ThirdTask()**
  

#### Configuración inicial setup()

S'estableixelmode de pins per el LED incorportat *LED_BUILTIN* i el pin 19 com a sortida.

En el meu codi he creat dos tasques de més, pero en podriem crear les que volguesim.
Aquestes, les he creat utilitant la funció *TaskCreate()* i les he anomenat
* anotherTask ---> Imprimeix "this is another Task" cada 10 sec.
* ThirdTask ---> Alterna el pin 19 cada sec i també imprimeix "this is the third Task" cada sec


#### Bucle principal (loop()):

És com si fos una altre tasca tot i que es la que menys preferencia te i les taques es poden posar per prioritats ( 1,2,3,4...).
Aquesta imprimeix "this is ESP32 Task" a traves de la comunicació serial.

Encen i apafa el LED incorporat en un cicle de 300 milisegons


#### Tasca anotherTask():

Aquesta funcioó s'executa com a una tasca independent.
En un bucle infinit, imprimeix  "this is another Task" cada 10 sec a traves del la comunicació serial.

#### Tarea ThirdTask():

Aquesta funció també spexecuta com a una altre tasca independent.
En un bucle infinit imprimeix "this is the third Task"cada segon mitjençant la comunicació serial.
Ademés, fa que el pin 19 fagi pampallugues, alternant entre *hight* i *low* cada segon.
___
Hem de tenir en compte que les tasques, e'executen de manera independent en segon pla, mentres que el bucle principal *loop()* s'executa en fil principal del programa. D'aquesta manera ens permet realitzat múltiples tasques simultaniament en el nostre micro, gràcies al sistema operatiu de temps real FreeRTOS.
___
## ECERCICI PRÀCTIC 2
1. Realitza un programa que utilitzi dos tasques, una encengui el led i l'altre l'apagui, aquestes tasques han d'estar sincronitzades.

En quant exercici ni he acabat d'entendre del tot aixi que he fet dos codis per provar.

**El primer** es el que crec que demana la pràctica que es un programa en el que dos tasques es sincronitzen per encendre i apagar un LED de la ESP32 S3. 
Aquest esta adjunt anomenta com prova 2

**CODI**
```
#include <Arduino.h>

// Prototipos de funciones
void TaskLEDOn(void *parameter);
void TaskLEDOff(void *parameter);

// Manejadores de tareas
TaskHandle_t TaskLEDOnHandle = NULL;
TaskHandle_t TaskLEDOffHandle = NULL;

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  // Crear la tarea que enciende el LED
  xTaskCreate(
    TaskLEDOn,       // Función de tarea
    "Task LED On",   // Nombre de la tarea
    1000,            // Tamaño de la pila
    NULL,            // Parámetro de la tarea
    1,               // Prioridad de la tarea
    &TaskLEDOnHandle // Manejador de la tarea
  );

  // Crear la tarea que apaga el LED
  xTaskCreate(
    TaskLEDOff,      // Función de tarea
    "Task LED Off",  // Nombre de la tarea
    1000,            // Tamaño de la pila
    NULL,            // Parámetro de la tarea
    1,               // Prioridad de la tarea
    &TaskLEDOffHandle // Manejador de la tarea
  );
}

void loop() {
  // El loop principal está vacío ya que las tareas se manejan por FreeRTOS
}

// Tarea para encender el LED
void TaskLEDOn(void *parameter) {
  for (;;) {
    // Esperar una notificación para encender el LED
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("LED encendido");
    
    // Notificar a la tarea de apagado del LED
    xTaskNotifyGive(TaskLEDOffHandle);
  }
}

// Tarea para apagar el LED
void TaskLEDOff(void *parameter) {
  for (;;) {
    // Esperar una notificación para apagar el LED
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("LED apagado");
    
    // Notificar a la tarea de encendido del LED
    xTaskNotifyGive(TaskLEDOnHandle);
  }
}
```
He utilitzar mecanismes de sincronitzacio de FreeRTOS com les senyals de tasques. Una tasca s'encarrega d'encendre el LED i l'altre d'apagar-lo utilitzant senyals de tasques per la comunicació entre elles


**El segon** codi que he intentat fer les recomenacions que posaven a les webs adjuntes al doc de la pràctica pero no m'hen he ensortit. El codi es el que es diu semaphore 
