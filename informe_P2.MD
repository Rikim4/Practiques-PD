# INFORME PRACTICA 2 - Interrupcions

***L'objectiu d'aquesta pràctica es compendre el funcionament de les interrupcions***

La practica consta de controlar 2 leds de forma periodica i una entrada de forme que l'us de l'entrada provoqui un canvi de frequencies de les oscil·lacions nomes en un dels leds.

## Practica A interrupció por GPIO

```
struct Button {
 const uint8_t PIN;
 uint32_t numberKeyPresses;
 bool pressed;
};
Button button1 = {18, 0, false};
void IRAM_ATTR isr() {
 button1.numberKeyPresses += 1;
 button1.pressed = true;
}
void setup() {
 Serial.begin(115200);
 pinMode(button1.PIN, INPUT_PULLUP);
 attachInterrupt(button1.PIN, isr, FALLING);
}
void loop() {
 if (button1.pressed) {
 Serial.printf("Button 1 has been pressed %u times\n",
button1.numberKeyPresses);
 button1.pressed = false;
 }
 //Detach Interrupt after 1 Minute
 static uint32_t lastMillis = 0;
 if (millis() - lastMillis > 60000) {
 lastMillis = millis();
 detachInterrupt(button1.PIN);
 Serial.println("Interrupt Detached!");
 }
}
```
**En aquesta Pràctica A**
Podem veure que hi han moltissims rebots mecanics, per evitar-los podriem utilitzar un condensador, el quan seria una tècnica o per altre banda utilitzar el delay pero et podria trencar tot
programa per interrupcion...
El franc de baixada passa el mateix, si el deixem apretat, nomes detecta un.

**ANALISISS DE LES FUNCIONS "DESCONEGUDES"**

>Button button1 = {18, 0, false};

* Button -> Es el tipus de la variable.
* Button1 -> Es el nom de la variable
* 18 -> Num del pin assignat 
* 0 -> Estat inicial del boto.
* false -> boolea que representa si esta presionat o no el boto.
  
>void IRAM_ATTR isr()
* Void->Indica que es una funció
* IRAM_ATTER -> Ho guarda en un lloc de memoria flash a l'Internal RAM, en un tipo de memoria especial (ram / rom).
* isr()-> Es simplement el nom de la funcio, li podria dir "pepito".

>attachInterrupt(button1.PIN, isr, FALLING)

Es per configurar una interrupcio externa en un micro.
* Configura l'interrupcio en el pin especificat per *button1.PIN* de manera que quan el senyal en aquell pin canvii "HIGH" a "LOW", s'executa directament la funció "isr".
* Passa de "HIGH" a "LOW" perque esta determinat com a *FALLING*.

**L'impresio serial** conta les vegades que es presiona un boto conectat al pin 18 i mostra aquesta informacio en el monitor serie. Ademes desactiva la interrupcio despres d'un minut i notifica l'usuari

## Pràctica B interrupció per TIMER

```
#include <Arduino.h>

volatile int interruptCounter;
int totalInterruptCounter;
hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

void IRAM_ATTR onTimer() {
 portENTER_CRITICAL_ISR(&timerMux);
 interruptCounter++;
 portEXIT_CRITICAL_ISR(&timerMux);
}
void setup() {
 Serial.begin(115200);
 timer = timerBegin(0, 80, true);
 timerAttachInterrupt(timer, &onTimer, true);
 timerAlarmWrite(timer, 4000000, true);
 timerAlarmEnable(timer);
}
void loop() {
 if (interruptCounter > 0) {
 portENTER_CRITICAL(&timerMux);
 interruptCounter--;
 portEXIT_CRITICAL(&timerMux);
 totalInterruptCounter++;
 Serial.print("An interrupt as occurred. Total number: ");
 Serial.println(totalInterruptCounter);
 }
}
```
---
**ANALISISS DE LES FUNCIONS "DESCONEGUDES"**

> Volatile

Es una variable global per a que el compilador optimitzi,NO intentara reduir essspai.
>hw_timer_t * timer = NULL;

Inicialitza el Timer, es un punter que es indica on es guarda la variable, pero com l'hem inicialitzat coma "NULL", no apunta a ninguna ubicació de memoria válida.
>portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

Tipo de timer per configurar el timer 
Despres tenim la interrupcio en la que hi han dos funcions d'arduino que el que fan es desahbiliar les interrupcions.

>portENTER_CRITICAL_ISR(&timerMux);

Funcio que ens assegura que no s'interrumpira, proporcionant exclució mutua. Es la funció que deixa d'escoltar.
> interruptCounter++

Quan hi ha una interrupcio, aquesta es a funcio que fara, l'hem definit com a volatil més amunt.
>timerBegin(0, 80, true);

Es una funció d'arduino la qual inicialitza el timer.
* el primer element, especifica el índex del temporitzador que s'utilitzara. En el nostre cas, s'inicialitza el temporitzador a 0.
* El segon element es el divisor que controla la velocitat del temporitzador. Nosaltres tenim 80 i quan mes gran sigui el divisor mes baixa sera la velocita
* El tercer element es la direccio del contador del temporitzador, el *TRUE* indica que contara cap amunt 
>timerAttachInterrupt(timer, &onTimer, true);

Aquesta asocia la funcio onTimer al temporizador especificat, de manera que la duncio s'exeectutara cada vegada que hi hagi una interrupció del temporitzador. En el nostre codi el flanc es ascendent (TRUE). La funcio
de modo que la función se ejecutará cada vez que ocurra una interrupción del temporizador, en este caso, en el flanc ascendente.
* La función onTimer es la funció d'interrupcio i  li posem el & per obtenir la direccio de la funció.
>timerAlarmWrite(timer, 4000000, true);

Estableix el valor de l'alarma del temporitzador a 4000000 i la habilita. Aixo vol dir que el temporitzador generarà una interrupcio quan arribi a aquest valor i la funcio previa, s'exeecutaraen resposta a aquesta interrupcio.
>Void Loop()

Basicament en el Loop decrementa per no perdre el compte i s'escriuen per pantalla el  nombre total d'interrupcions (*totalinterruptcounter*) el ultim que hi ha.

**L'impresio serial** proporciona una forma de monitoritzar en temps real el numero total d'interrupcions que han sigut causades per l'ESP32

## CONCLUSIÓ
He apres i definit, de forma resumida, les funcions les quals no sabia com funcionaven o que simplement no sabia que feien.