#include <Arduino.h>
#include <WiFi.h>                   // Biblioteca para gestión de WiFi
#include <WiFiManager.h>            // Biblioteca para configuración WiFi simplificada
#include <PubSubClient.h>           // Biblioteca PubSubClient para comunicación MQTT
#include <WiFiClientSecure.h>


//*************************************
//********      GLOBALS         *******
//*************************************
bool topic_obteined = false;
char device_topic_subscribe[40];
char device_topic_publish[40];
char msg[60];
long milliseconds = 0;

#define ledpin 2
int fotopin=33;

int var = 0;
int ledval = 0;
int fotoval = 0;
char datos[40];
String resultS = "";



//CONECTAR AL BROKER MQTT EMQX

// Información del broker EMQX
const char* mqtt_broker = "broker.emqx.io"; // Dirección del broker MQTT
const int mqtt_port = 1883; // Puerto TCP por defecto para MQTT

const char* mqtt_user = "6aL4uU9b5axRmJv";  // Reemplaza con tu usuario EMQX (opcional)
const char* mqtt_pass = "contraseña_emqx"; // Reemplaza con tu contraseña EMQX (opcional)

// Crear una instancia de WiFiClientSecure
WiFiClientSecure espClient;

// Instancia del cliente MQTT
PubSubClient mqttclient(espClient); // Cliente MQTT (espClient es la instancia de WiFiClient)

// Función callback (opcional) para procesar mensajes recibidos
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensaje recibido en el tema: ");
  Serial.println(topic);
  Serial.print("Carga útil: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void reconnect()
{

  while (!mqttclient.connected())
  {
    Serial.println("Intentando conexión MQTT SSL");
    // we create client id
    String clientId = "esp32_fmg_";
    clientId += String(random(0xffff), HEX);
    // Trying SSL MQTT connection
    if (mqttclient.connect(clientId.c_str(), mqtt_user, mqtt_pass))
    {
      Serial.println("Conectado al Broker MQTT EMQX!");
      // We subscribe to topic

      mqttclient.subscribe(device_topic_subscribe);
    }
    else
    {
      Serial.print("falló :( con error -> ");
      Serial.print(mqttclient.state());
      Serial.println(" Intentamos de nuevo en 5 segundos");

      delay(100);
     // ReStartESP();
    }
  }
}

void setup() {
  Serial.begin(115200);

  // Configura el modo WiFi a estación (STA)
  WiFi.mode(WIFI_STA);

  // Crea una instancia de WiFiManager
  WiFiManager wm;

  // (Opcional) Reinicia la configuración almacenada (útil para pruebas)
  // wm.resetSettings();  // Descomenta esta línea para borrar credenciales guardadas

  // Intenta la conexión automática usando credenciales guardadas
  // Si falla, crea un punto de acceso con el nombre "AutoConnectAP" y contraseña "password"
  bool conectado = wm.autoConnect("YAKU AP", "yaku0381");

  if (!conectado) {
    Serial.println("Fallo al conectar");
    // (Opcional) Reinicia el ESP32 si falla la conexión
    // ESP.restart();
    Serial.println("Fallo al conectar. Reconectando WiFi y MQTT");
    reconnect();

  } else {
    Serial.println("Conectado al WiFi...!");
    // Agrega aquí tu código para la aplicación
    mqttclient.setServer(mqtt_broker, mqtt_port);
    mqttclient.setCallback(callback);
    
  }
}

void loop() {
  // Tu código principal se ejecuta aquí repetidamente
  if (!mqttclient.connected()) {
    reconnect();
  }
  mqttclient.loop();

  Serial.print("String: ");
  Serial.println(resultS);

  if(var == 0)
  {
  digitalWrite(ledpin,LOW);
  }
  else if (var == 1)
  {
  digitalWrite(ledpin,HIGH);
  }

  fotoval = analogRead(fotopin);
  Serial.print("Foto: ");
  Serial.println(fotoval);

  sprintf(datos, "Valor LDR: %d ", fotoval);
  mqttclient.publish("Salida/01",datos);
  delay(5000);
  
}

