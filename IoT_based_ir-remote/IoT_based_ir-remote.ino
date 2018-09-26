// Author:- K.V.Srikanth.
// program to control devices using mqtt.


#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#ifndef UNIT_TEST  
#include <Arduino.h>
#endif
#include <IRremoteESP8266.h>
#include <IRsend.h>

#define IR_LED 4  // ESP8266 GPIO pin to use. Recommended: 4 (D2).

IRsend irsend(IR_LED);  // Set the GPIO to be used to sending the message.


// Update these with values suitable for your network.

const char* ssid = "hachi";
const char* password = "12345678";
//const char* mqtt_server = "broker.mqtt-dashboard.com";
//const char* mqtt_server = "m20.cloudmqtt.com";//2.23
//const char* mqtt_server = "broker.hivemq.com";
const char* mqtt_server = "34.226.134.195";

//34.226.134.195
//1883,3033


const char* mqttUser = "binolozp";
const char* mqttPassword = "JUsbNVjD1LgU";
#define CLIENT_ID  "c" 
#define PUBLISH_DELAY 3000
#define SUB_TOPIC "ir-remote"



WiFiClient espClient;
PubSubClient client(espClient);
char code;

void setup() {
//  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an outputsss
  irsend.begin();
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
//  client.setServer(mqtt_server, 1883);
//  client.setServer(mqtt_server, 16320);
  client.setCallback(callback);
}

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}



void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.println((char)payload[i]);
   
   if((char)payload[i] =='i') {
    code='i';
   
   }
//   else{
//    code='error';
//   }
   if((char)payload[i] == '1') {
    code='1';
    
   }
//   else{
//    code='error';
//   }
   if((char)payload[i] == '0') {
    code='0';
    
   }
//   else{
//    code='error';
//   }
   if((char)payload[i] == '+') {
    code='+';
    
   }
//   else{
//    code='error';
//   }
   if((char)payload[i] == '-') {
    code='-';
    
   }
//   else{
//    code='error';
//   }
   if((char)payload[i] == 'z') {
    code='z';
    
   }
//   else{
//    code='error';
//   }
   if((char)payload[i] == 'g') {
    code='g';
    
   }
//   else{
//    code='error';
//   }

   if((char)payload[i] == 'p') {
    code='p';
    
   }
//   else{
//    code='error';
//   }
   if((char)payload[i] == 'd') {
    code='d';
    
   }
    if((char)payload[i] == 'm') {
    code='m';
    
   }
   if((char)payload[i] == 'a') {
    code='a';
    
   }
//   else{
//    code='error';
//   }
  }
  
// if(code=='error'){
//  Serial.print("you entered error code"); 
//  delay(500);
// } 
 if(code=='i'){
  Serial.print("sent code for info."); 
  irsend.sendNEC(0xC04FB, 32);
  delay(500);
 }
 
 if(code=='1'){
  Serial.print("sent code for power on");
  irsend.sendNEC(0xC40BF, 32);
  delay(500);
 }
 
 if(code=='0'){
  Serial.print("sent code for power off");
  irsend.sendNEC(0xC40BF, 32);
  delay(500);
  irsend.sendNEC(0xC40BF, 32);
 }
 
 if(code=='+'){
  Serial.print("sent code for volume up");
  irsend.sendNEC(0xC41BE, 32);
  delay(500);
 }

 if(code=='-'){
  Serial.print("sent code for volume down");
  irsend.sendNEC(0xCC13E, 32);
  delay(500);
 }

  if(code=='z'){
  Serial.print("sent code for zoom in");
  irsend.sendNEC(0xC18E7, 32);
  delay(500);
 }

 if(code=='g'){
  Serial.print("sent code for zoom out");
  irsend.sendNEC(0xC9867, 32);
  delay(500);
 }

 if(code=='p'){
  Serial.print("sent code for page up");
  irsend.sendNEC(0xCA05F, 32);
  delay(500);
 }

 if(code=='d'){
  Serial.print("sent code for page down");
  irsend.sendNEC(0xC609F, 32);
  delay(500);
 }

 if(code=='m'){
  Serial.print("sent code for page down");
  irsend.sendNEC(0xCF00F, 32);
  delay(500);
 }

 
 if(code=='a'){
  Serial.print("sent code for auto");
  irsend.sendNEC(0xC10EF, 32);
  delay(500);
 }
 
  Serial.println();


}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      boolean rc = client.connect(CLIENT_ID, mqttUser,mqttPassword);
      Serial.println("connected to your mqtt");
      client.subscribe(SUB_TOPIC);
      Serial.println("connected to SUB_TOPIC");
//      client.setCallback(callback);                       
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

}
