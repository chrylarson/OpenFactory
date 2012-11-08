#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <Dns.h>

IPAddress receiverIP(74, 125, 140, 99); // backup IP of udp packets receiver. used if dns lookup fails. set this to your node.js server IP
unsigned int receiverPort = 8080;      // port for Arduino communication to node.js server
byte mac[] = {  0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02 }; //mac address
EthernetUDP Udp;
byte serialNum[] = {  0x99, 0xAA, 0xBB, 0xCC }; // a unique identifier for each arduino on the network
int sensorPin = A0; //define sensor pin
int sensorValue;

void setup() {
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    for(;;)
      ;
  }
  // print your local IP address:
  Serial.print("My IP address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print(".");
  }
  Serial.println();
  Udp.begin(receiverPort);
  // lookup the IP of the logging site
  DNSClient dns;
  IPAddress remote_addr;
  int ret = 0;
  Serial.print("DNS IP is ");
  dns.begin(Ethernet.dnsServerIP());
  ret = dns.getHostByName("www.google.com",remote_addr); // set this to the DNS name of your server.
  Serial.println(remote_addr);
  Serial.print("Log IP is ");
  if (ret == 1) {
    receiverIP = remote_addr; // dns lookup was successful
  }
  Serial.println(receiverIP);
}

void loop() {
  sensorValue = analogRead(sensorPin);//read sensor value from 0 to 1023 
  byte valueInBytes[8] = {lowByte(sensorValue), highByte(sensorValue), serialNum[0], serialNum[1], serialNum[2], serialNum[3]}; //convert it to byte array
  Udp.beginPacket(receiverIP, receiverPort); //start udp packet
  Udp.write(valueInBytes, 8); // write sensor data and serial number to udp packet
  Udp.endPacket(); // end packet

  delay(10000);
}


