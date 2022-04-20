#include <Console.h>
#include <SPI.h>
#include <RH_RF95.h>
#include <LoRa.h>


int counter;  //傳送次數計數器
long randNumber;
int a[10];//random
int sf;
long MHZ;
int packet=1;
int arrayrand[10];
int power;
int b[9]={1,2,3,4,5,6,7,8,9};
char packetzero[9]={'\0'};



void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
  while (!Serial);  //等待序列埠起始完畢
  Serial.println("LoRa Duplex - Set spreading factor");
  Serial.println("LoRa Sender");
  Serial.println("LoRa init succeeded.");
  Serial.println("Enter counter,Power,MHZ,SF");
  if (!LoRa.begin(MHZ)) {  //起始 433MHz LoRa
    Serial.println("Starting LoRa failed!");
    while (1);
    }
  LoRa.setSpreadingFactor(sf);    // ranges from 6-12,default 7 see API docs
  LoRa.setTxPower(power);         //ranges from 2-20,default 17 see API docs
  //setSignalBandwidth()
  /*  if (sbw <= 7.8E3) {
    bw = 0;
  } else if (sbw <= 10.4E3) {
    bw = 1;
  } else if (sbw <= 15.6E3) {
    bw = 2;
  } else if (sbw <= 20.8E3) {
    bw = 3;
  } else if (sbw <= 31.25E3) {
    bw = 4;
  } else if (sbw <= 41.7E3) {
    bw = 5;
  } else if (sbw <= 62.5E3) {
    bw = 6;
  } else if (sbw <= 125E3) {
    bw = 7;
  } else if (sbw <= 250E3) {
    bw = 8;
  } else if (sbw <= 250E3) {
    bw = 9;
  }*/
  Serial.println("LoRa init succeeded.");
  Serial.println("Enter counter,Power,MHZ,SF");
  Serial.println("-----------------"); 
  }

void loop() {
  if(Serial.available()){
  counter = Serial.parseInt();
  Serial.println(String("Enter counter:")+counter);
  int power = Serial.parseInt();
  Serial.println(String("Enter Power:")+power);    
  int intMHZ = Serial.parseInt();
  Serial.println(String("Enter MHZ:")+intMHZ); 
  int sf= Serial.parseInt();
  Serial.println(String("Enter SF:")+sf); 
    Serial.println("--------start---------"); 
 for (int i=0; i<counter; i++){
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
    
  if (!LoRa.begin(MHZ)) { //起始 433MHz LoRa
    Serial.println("Starting LoRa failed!");
    while (1);
    }
    LoRa.setSpreadingFactor(sf);    // ranges from 6-12,default 7 see API docs
    LoRa.setTxPower(power);         ////ranges from 2-20,default 17 see API docs
      Serial.println(String("Power:")+power); 
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
  sprintf(packetzero, "%04d",packet++); 
  Serial.println(String("packet:")+packetzero);//
  Serial.print("Sending packet: ");
  //Serial.println(randNumber);
  for (int i=0; i<9; i++){ 
  Serial.print(b[i]);
  }
  //Serial.print((packet-1)+String(",")+arrayrand[i]);
  Serial.println();
  LoRa.beginPacket();  //封包傳送開始
 // LoRa.println("hello");  //封包內容
 // LoRa.println(String("packet:")+(packet-1)); 
  LoRa.print(power+String(","));
  LoRa.print((packetzero)+String(","));
  //LoRa.print(randNumber);  //封包內容
  for (int i=0; i<9; i++){ 
  LoRa.print(b[i]);
  }
  LoRa.endPacket();  //封包傳送結束
  Serial.println("--------end---------"); 
  delay(2000);
  }
  while(1);
  }
  }
