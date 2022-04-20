#include <Console.h>
#include <SPI.h>
#include <RH_RF95.h>
#include <LoRa.h>


int counter=1;  //傳送次數計數器
long randNumber;
int a[10];
int sf;
long MHZ;
int packet=1;



void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
  while (!Serial);  //等待序列埠起始完畢
  Serial.println("LoRa Duplex - Set spreading factor");
  Serial.println("LoRa Sender");
  if (!LoRa.begin(MHZ)) {  //起始 433MHz LoRa
    Serial.println("Starting LoRa failed!");
    while (1);
    }
  LoRa.setSpreadingFactor(sf);           // ranges from 6-12,default 7 see API docs
  Serial.println("LoRa init succeeded.");
  Serial.println("Enter MHZ,SF");
  Serial.println("-----------------"); 
  }

void loop() {

  if(Serial.available()){
//  counter = Serial.parseInt();
//  Serial.println(String("Enter counter:")+counter);    
  int intMHZ = Serial.parseInt();
  Serial.println(String("Enter MHZ:")+intMHZ); 
  int sf= Serial.parseInt();
  Serial.println(String("Enter SF:")+sf); 
    Serial.println("--------start---------"); 
 while(counter>0){
  if(intMHZ==868){
    MHZ=868E6;
  }
  else if(intMHZ==915){
    MHZ=915E6;
  }
  else if(intMHZ==433){
    MHZ=433E6;
  }
  else
  {
    Serial.println("wrong frequency");
    }
    
  if (!LoRa.begin(MHZ)) {  //起始 433MHz LoRa
    Serial.println("Starting LoRa failed!");
    while (1);
    }
      Serial.println(String("MHZ:")+MHZ);
      Serial.println(String("SF:")+sf); 
  // randNumber = random(300);
 for (int i=0; i<10; i++){ 
   a[i]=random()%10+1;
    for (int j=0; j<i; j++){
        if (a[i]==a[j]) {
            a[i]=0;
              break;    
            }   
        }
  }

  Serial.println(String("packet:")+packet++);

  Serial.println("Sending packet: ");
  //Serial.println(randNumber);
  for (int i=0; i<10; i++){ 
  Serial.print(a[i]);
  }
  Serial.println();
  LoRa.beginPacket();  //封包傳送開始
  LoRa.println("hello");  //封包內容
  LoRa.println(String("packet:")+(packet-1));
  //LoRa.print(randNumber);  //封包內容
  for (int i=0; i<10; i++){ 
  LoRa.print(a[i]);
  }
  Serial.println();
  LoRa.endPacket();  //封包傳送結束
  Serial.println("--------end---------"); 
  delay(2000);
  }
  while(1);
  }
  }
