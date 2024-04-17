#include <Arduino.h>
#if defined(ESP8266)
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif


#include <WiFiManager.h>
#include <Separador.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include <DHT.h>

#define DHTPIN 34   // Pin de datos del sensor DHT22
#define DHTTYPE DHT22 // Tipo de sensor DHT22

DHT dht(DHTPIN, DHTTYPE);




//*********************************
//*********** CONFIG **************
//*********************************

#define WIFI_PIN 17
#define LED 2 //On Board LED

int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by

// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8; //Resolution 8, 10, 12, 15

//estos datos deben estar configurador también en las constantes de tu panel
// NO USES ESTOS DATOS PON LOS TUYOS!!!!
const String serial_number = "797079";
const String insert_password = "285289";
const String get_data_password = "420285";
const char *server = "yakubox.info";

// MQTT
const char *mqtt_server = "broker.emqx.io";
const int mqtt_port = 8883;

//no completar, el dispositivo se encargará de averiguar qué usuario y qué contraseña mqtt debe usar.
char mqtt_user[20] = "";
char mqtt_pass[20] = "";

const int expected_topic_length = 26;

WiFiManager wifiManager;
WiFiClientSecure client;
PubSubClient mqttclient(client);
WiFiClientSecure client2;

Separador s;




//************************************
//***** DECLARACION FUNCIONES ********
//************************************
bool get_topic(int length);
void callback(char* topic, byte* payload, unsigned int length);
void reconnect();
void send_mqtt_data();
void send_to_database();

//SENSORES
void fDht22();



//*************************************
//********      GLOBALS         *******
//*************************************
bool topic_obteined = false;
char device_topic_subscribe [40];
char device_topic_publish [40];
char msg[25];
float temp = 0;
int hum = 0;
long milliseconds = 0;
byte sw1 = 0;
byte sw2 = 0;
byte slider = 0;


//STRING DATA BASE
int data_1;
float data_2; // DHT22 - TEMP
float data_3; // DHT22 - HUM
float data_4; // PH H2O
int data_5;
int data_6;
int data_7;
int data_8;
int data_9;
int data_10;


void setup() {
  randomSeed(analogRead(0));


  pinMode(LED,OUTPUT);

  // configure LED PWM functionalitites
  ledcSetup(ledChannel, freq, resolution);

  // attach the channel to the GPIO2 to be controlled
  ledcAttachPin(LED, ledChannel);

  Serial.begin(115200);
  dht.begin();

  pinMode(WIFI_PIN,INPUT_PULLUP);

  wifiManager.autoConnect("YAKU Admin");
  Serial.println("Conexión a WiFi exitosa!");



  //client2.setCACert(web_cert);

  while(!topic_obteined){
    topic_obteined = get_topic(expected_topic_length);
    delay(30);
  }


  //set mqtt cert
  //client.setCACert(mqtt_cert);
  mqttclient.setServer(mqtt_server, mqtt_port);
	mqttclient.setCallback(callback);


}

void loop() {


    //Llamadas de Funciones
    fDht22();

  if (!client.connected()) {
		reconnect();
	}

//si el pulsador wifi esta en low, activamos el acces point de configuración
  if ( digitalRead(WIFI_PIN) == LOW ) {
    WiFiManager wifiManager;
    wifiManager.startConfigPortal("YAKU Admin");
    Serial.println("Conectados a WiFi!!! :)");
  }

  //si estamos conectados a mqtt enviamos mensajes
  if (millis() - milliseconds > 3000){
    milliseconds = millis();


    if(mqttclient.connected()){
      //set mqtt cert

      data_1 = 0;
      data_4 =  random(0,1401)/100.0; // PH H20
      data_5 =  random(5,20);
      data_6 =  random(0,50);
      data_7 =  random(1,33);
      data_8 =  random(2,57);
      data_9 =  random(3,20);
      data_10 = 0;


      String to_send = String(data_1) + "," + String(data_2) + "," + String(data_3) + "," + String(data_4) + "," + String(data_5) + "," + String(data_6) + "," + String(data_7) + "," + String(data_8) + "," + String(data_10) + "," + String(sw1)+","+ String(sw2);
      to_send.toCharArray(msg,20);
      mqttclient.publish(device_topic_publish,msg);

        send_to_database();
      
    }

  }

  mqttclient.loop();

}



//************************************
//*********** FUNCIONES **************
//************************************

void callback(char* topic, byte* payload, unsigned int length) {
  String incoming = "";
	Serial.print("Mensaje recibido desde tópico -> ");
	Serial.print(topic);
	Serial.println("");
	for (int i = 0; i < length; i++) {
		incoming += (char)payload[i];
	}
	incoming.trim();
	Serial.println("Mensaje -> " + incoming);

  String str_topic = String(topic);
  String command = s.separa(str_topic,'/',3);
  Serial.println(command);

  if(command=="sw1"){
    Serial.println("Sw1 pasa a estado " + incoming);
    sw1 = incoming.toInt();
  }

  if(command=="sw2"){
    Serial.println("Sw2 pasa a estado " + incoming);
    sw2 = incoming.toInt();
  }

  if(command=="slider"){
    Serial.println("Sw1 pasa a estado " + incoming);
    slider = incoming.toInt();
    ledcWrite(ledChannel,slider);
  }

}

void reconnect() {

	while (!mqttclient.connected()) {
		Serial.println("Intentando conexión MQTT SSL");
		// we create client id
		String clientId = "esp32_ia_";
		clientId += String(random(0xffff), HEX);
		// Trying SSL MQTT connection
		if (mqttclient.connect(clientId.c_str(),mqtt_user,mqtt_pass)) {
			Serial.println("Conectado EXITOSAMENTE al Broker MQTT - EMQX!");
			// We subscribe to topic

			mqttclient.subscribe(device_topic_subscribe);

		} else {
			Serial.print("falló :( con error -> ");
			Serial.print(mqttclient.state());
			Serial.println(" Intentamos de nuevo en 5 segundos");

			delay(50);
		}
	}
}

//función para obtener el tópico perteneciente a este dispositivo
bool get_topic(int length){

  Serial.println("\nIniciando conexión segura para obtener tópico raíz...");

  if (!client2.connect(server, 443)) {
    Serial.println("Falló conexión!");
  }else {
    Serial.println("Conectados a servidor para obtener tópico - ok");
    // Make a HTTP request:
    String data = "gdp="+get_data_password+"&sn="+serial_number+"\r\n";
    client2.print(String("POST ") + "/app/getdata/gettopics" + " HTTP/1.1\r\n" +\
                 "Host: " + server + "\r\n" +\
                 "Content-Type: application/x-www-form-urlencoded"+ "\r\n" +\
                 "Content-Length: " + String (data.length()) + "\r\n\r\n" +\
                 data +\
                 "Connection: close\r\n\r\n");

    Serial.println("Solicitud enviada - ok");

    while (client2.connected()) {
      String line = client2.readStringUntil('\n');
      if (line == "\r") {
        Serial.println("Headers recibidos - ok");
        break;
      }
    }

    String line;
    while(client2.available()){
      line += client2.readStringUntil('\n');
    }
    Serial.println(line);
    String temporal_topic = s.separa(line,'#',1);
    String temporal_user = s.separa(line,'#',2);
    String temporal_password = s.separa(line,'#',3);



    Serial.println("El tópico es: " + temporal_topic);
    Serial.println("El user MQTT es: " + temporal_user);
    Serial.println("La pass MQTT es: " + temporal_password);
    Serial.println("La cuenta del tópico obtenido es: " + String(temporal_topic.length()));

    if (temporal_topic.length()==length){
      Serial.println("El largo del tópico es el esperado: " + String(temporal_topic.length()));

      String temporal_topic_subscribe = temporal_topic + "/actions/#";
      temporal_topic_subscribe.toCharArray(device_topic_subscribe,40);
      Serial.println(device_topic_subscribe);
      String temporal_topic_publish = temporal_topic + "/data";
      temporal_topic_publish.toCharArray(device_topic_publish,40);
      temporal_user.toCharArray(mqtt_user,20);
      temporal_password.toCharArray(mqtt_pass,20);

      client2.stop();
      return true;
    }else{
      client2.stop();
      return false;
    }

  }
}


void send_to_database(){

  Serial.println("\nIniciando conexión segura para enviar a base de datos...");

  if (!client2.connect(server, 443)) {
    Serial.println("Falló conexión!");
  }else {
    Serial.println("Conectados a servidor para insertar en db - ok");
    // Make a HTTP request:
    String data = "idp="+insert_password+"&sn="+serial_number+"&data_1="+String(data_1)+"&data_2="+String(data_2)+"&data_3="+String(data_3)+"&data_4="+String(data_4)+"&data_5="+String(data_5)+"&data_6="+String(random(0.1,3.0))+"&data_7="+String(data_7)+"&data_8="+String(data_8)+"&data_9="+String(data_9)+"&data_10="+String(data_10)+"\r\n";
    client2.print(String("POST ") + "/app/insertdata/insert" + " HTTP/1.1\r\n" +\
                 "Host: " + server + "\r\n" +\
                 "Content-Type: application/x-www-form-urlencoded"+ "\r\n" +\
                 "Content-Length: " + String (data.length()) + "\r\n\r\n" +\
                 data +\
                 "Connection: close\r\n\r\n");

    Serial.println("Solicitud enviada - ok");

    while (client2.connected()) {
      String line = client2.readStringUntil('\n');
      if (line == "\r") {
        Serial.println("Headers recibidos - ok");
        break;
      }
    }


    String line;
    while(client2.available()){
      line += client2.readStringUntil('\n');
    }
    Serial.println(line);
    client2.stop();

    }

  }


//*********************************************
//*********** FUNCIONES SENSORES **************
//*********************************************


//FUNCION SENSOR DHT22 (HUM & TEMP AMBIENTE)

void fDht22(){

// Leer la temperatura y la humedad del sensor
  float sTemp = dht.readTemperature();
  float sHum = dht.readHumidity();

  // Verificar si se leyó correctamente la información
  if (isnan(sTemp) || isnan(sHum)) {
    Serial.println("Fallo al leer el sensor DHT22!");
    return;
  }

  // Imprimir los valores de temperatura y humedad
  Serial.print("Temperatura: ");
  Serial.print(sTemp);
  Serial.print(" °C");
  Serial.print("  Humedad: ");
  Serial.print(sHum);
  Serial.print("%");
  Serial.println();

  data_2 = sTemp;
  data_3 = sHum;

  delay(20);


  }