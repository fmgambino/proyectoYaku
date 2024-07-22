#include <Arduino.h>

// Definir los pines para el relé y los MOSFET
const int relayPin = 25;
const int mosfetPin1 = 26;
const int mosfetPin2 = 27;

// Definir el tiempo de intervalo en milisegundos
const unsigned long interval = 500;

// Variable para almacenar el tiempo anterior
unsigned long previousMillis = 0;

// Variable para controlar el estado de los pines
int state = 0;

void setup() {
    // Configurar los pines como salidas
    pinMode(relayPin, OUTPUT);
    pinMode(mosfetPin1, OUTPUT);
    pinMode(mosfetPin2, OUTPUT);

    // Inicializar los pines en LOW
    digitalWrite(relayPin, LOW);
    digitalWrite(mosfetPin1, LOW);
    digitalWrite(mosfetPin2, LOW);
}

void loop() {
    // Obtener el tiempo actual
    unsigned long currentMillis = millis();

    // Verificar si ha pasado el tiempo de intervalo
    if (currentMillis - previousMillis >= interval) {
        // Guardar el tiempo actual
        previousMillis = currentMillis;

        // Cambiar el estado de los pines de manera secuencial
        switch (state) {
            case 0:
                digitalWrite(relayPin, HIGH);
                digitalWrite(mosfetPin1, LOW);
                digitalWrite(mosfetPin2, LOW);
                state = 1;
                break;
            case 1:
                digitalWrite(relayPin, LOW);
                digitalWrite(mosfetPin1, HIGH);
                digitalWrite(mosfetPin2, LOW);
                state = 2;
                break;
            case 2:
                digitalWrite(relayPin, LOW);
                digitalWrite(mosfetPin1, LOW);
                digitalWrite(mosfetPin2, HIGH);
                state = 0;
                break;
        }
    }
}
