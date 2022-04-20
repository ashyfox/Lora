#include <Time.h>
#include <TimeLib.h>
#include <SPI.h>
#include <LoRa.h>


#define GMT (+8)
struct tm *info;
typedef bool boolean;
typedef unsigned char byte;
using namespace std; 
int sf;
long MHZ;
char message;
int senderpower;
int seq;
long ran;
using namespace std;

void setup() {
  Serial.begin(9600);
  while (!Serial);  //等待序列埠起始完畢
//  Serial.println("LoRa Receiver");
  Serial.print("MHZ");
  if (!LoRa.begin(MHZ)) { //起始 LoRa
    Serial.println("Starting LoRa failed!");
    while (1);
    }
   LoRa.setSpreadingFactor(sf); 
  }

void loop() {
  if(Serial.available()){
  int intMHZ = Serial.parseInt();
//  Serial.println(String("Enter MHZ:")+intMHZ); 
  Serial.print(" / SF,");
  int sf= Serial.parseInt();
//  Serial.println(String("Enter SF:")+sf); 

//  Serial.println("--------start---------"); 
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
    Serial.print(MHZ/1000000+String(","));
    Serial.println(sf);
    Serial.println("time,packet RSSI,RSSI,SNR,length,sender power,seq,rand");    

  while(true){    
  int packetSize=LoRa.parsePacket(); //讀取剖析 LoRa 封包大小
  if (packetSize) { //若有封包進來
 
    
    time_t t = now();
    Serial.print(hour(t)+String(":"));
    Serial.print(minute(t)+String(":"));
    Serial.print(second(t)+String(","));
 //  Serial.print(" ");
 //  Serial.print(day());
 //   Serial.print(" ");
 //   Serial.print(month());
 //  Serial.print(" ");
 //  Serial.print(year()+String(","));

     
//  Serial.print("packet RSSI= "); //輸出接收封包之 RSSI
    Serial.print(LoRa.packetRssi()+String(","));  //顯示接收信號強度
//  Serial.print(" RSSI= "); 
    Serial.print(LoRa.rssi()+String(",")); 
//  Serial.print(" SNR= "); //輸出接收封包之 SNR (信噪比)
    Serial.print(LoRa.packetSnr()+String(","));  //顯示接收信號信噪比
//  Serial.print(" SIZE= ");
    Serial.print(packetSize+String(","));    
    while (LoRa.available()) { //若接收緩衝器有內容
 // erial.print((char)LoRa.read());
    message =LoRa.read();
    Serial.print(message);
 // Serial.println(); 
    }
    Serial.println();
 
    }

        
      }
      while(1);
    }
  }
