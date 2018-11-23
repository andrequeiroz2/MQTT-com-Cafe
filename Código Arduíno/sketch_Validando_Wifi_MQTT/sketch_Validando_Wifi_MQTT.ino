/*****
 
 Projeto Teste de comunicação MQTT:
 
*****/

/*
 * Inclui as bibliotecas de dependencia do projeto
 */
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Zhone_AD62";
const char* password = "znid307908706";
const char* mqtt_server = "iot.eclipse.org";

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi(){
  
  delay(100);
  Serial.println();
  Serial.print("Conectando-se a rede WiFi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
    {
      delay(500);
      Serial.print(".");
      }
      Serial.println("");
      Serial.print("Conectado a Rede Wifi ");
      Serial.print("( ");
      Serial.print(ssid);
      Serial.println(" )");
      Serial.print("Endereco IP do seu Arduino: " );
      Serial.println(WiFi.localIP());
  }

void reconnect(){

  while(!client.connected())
  {

    Serial.println("Estabelecendo conexao com o servidor MQTT");

    if(client.connect("ESP8266Client2608")) 
    {

      Serial.print("Conectado ao Servidor MQTT: ");
      Serial.println(mqtt_server);

      client.subscribe("gdgfoz/coffeeiot");
      
      }else{

              Serial.print("Falha, rc= ");
              Serial.println(client.state());
              Serial.println("Nova tentativa em 5 segundos");
              delay(5000);
        
        }
    
    }
  
  }

void callback(String topic, byte* message, unsigned int length){

  Serial.print("[Mensagem Recebida] Topico: ");
  Serial.print(topic);
  Serial.print(" Mensagem: ");
  String messageTemp;

  for(int i = 0; i < length; i++){

    Serial.print((char)message[i]);
    
    messageTemp += (char)message[i];
    
  }
 }

void setup() {

  setup_wifi();

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

 }

void loop() {

  if(!client.connected())
  {

    reconnect();
      
    }

  if(!client.loop())

    client.connect("ESP8266Client2608");
   client.loop();
}

