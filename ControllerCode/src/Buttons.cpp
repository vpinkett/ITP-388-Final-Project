#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <Adafruit_I2CDevice.h>
#include <SPI.h>


// setting up network
const char* ssid = "ESP32AP";
const char* password = "Password";
const char* receiver_ip("192.168.4.1"); // IP address of microcontroller
// initializing pins for buttons
const int BlueButtonPin = 14; 
const int RedButtonPin = 32;
const int GreenButtonPin = 15; 
const int YellowButtonPin = 33; 
// initial button values
int BlueButton = 1;
int RedButton = 1;
int GreenButton = 1;
int YellowButton = 1;
int check_connection=0;

WiFiServer server(80); // creating server

void setup() {
  Serial.begin(9600); // serial begins for printing etc.
  delay(10);

  // creating Wi-Fi network 
  Serial.println("Access Point"); // updates
  WiFi.softAP(ssid, password);
  Serial.print("AP IP Address: "); // prints IP
  Serial.println(WiFi.softAPIP());
  server.begin();
  Serial.println("WiFi server started"); // updates

  // initializes all the button pins as inputs with pull up resistors
  pinMode(BlueButtonPin, INPUT_PULLUP); 
  pinMode(RedButtonPin, INPUT_PULLUP); 
  pinMode(GreenButtonPin, INPUT_PULLUP); 
  pinMode(YellowButtonPin, INPUT_PULLUP); 
}

void loop() {
  // checks for client connections
  WiFiClient client = server.available();
  if (check_connection=0 && client)
  {
    Serial.println("New client connected"); // updates on client connection
    int check_connection=1;
  }
  // reads all the buttons
  BlueButton = digitalRead(BlueButtonPin);
  RedButton = digitalRead(RedButtonPin);
  GreenButton = digitalRead(GreenButtonPin);
  YellowButton = digitalRead(YellowButtonPin);

  if (client) {
    // read request 
    String request = client.readStringUntil('\r');
    Serial.println("Request: " + request);

    // sends response to the server with all of the button values
    String BlueButtonVal = String(BlueButton);
    String RedButtonVal = String(RedButton);
    String GreenButtonVal = String(GreenButton);
    String YellowButtonVal = String(YellowButton);
    client.print("BlueButton= "+BlueButtonVal+" ");
    client.print("RedButton= "+RedButtonVal+" ");
    client.print("GreenButton= "+GreenButtonVal+" ");
    client.print("YellowButton= "+YellowButtonVal+" ");
    client.flush();
  }
}