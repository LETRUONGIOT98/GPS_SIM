#include <SoftwareSerial.h>
#include <TinyGPS.h>
TinyGPS gps;
SoftwareSerial SerialAT(10, 11); // RX, TX
SoftwareSerial gpst(3,4);
float flat, flon;
long times;
int coi = A0;
String valr="";
#define congtac 2
void setup()
{
  Serial.begin(9600);
  delay(1000);
  SerialAT.begin(9600);
  gpst.begin(9600);
  pinMode(coi, OUTPUT);
  //ss.begin(9600);
  delay(10000);
  digitalWrite(coi, HIGH);
  delay(3000);
  digitalWrite(coi, LOW);
}

void loop()
{ doc();
  if (digitalRead(congtac) == HIGH) {
    digitalWrite(4, HIGH);
        phanhoi(1);
        delay(1000);}
        else{digitalWrite(4, LOW);}
  
  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;

  // For one second we parse GPS data and report some key values
  
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (gpst.available())
    { doc();
      char c = gpst.read();
           if (gps.encode(c)) //Đọc gps
        newData = true;
    }
  }

  if (newData)
  { 
    doc();
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
     flat ==  flon,6;
     flon == flat,6;
    Serial.print("LAT=");
    Serial.print(flat,6 );
    Serial.print(" LON=");
    Serial.println(flon,6 );
  }
 
}
void doc(){
   if(SerialAT.available()>0){
    valr = SerialAT.readStringUntil('\n');
    Serial.println(valr);
    if(valr=="location\r" || valr=="Location\r" || valr=="LOCATION\r"){
      delay(100);
      phanhoi(1);
    }
    }
  valr="0";
}
void phanhoi(int tipe) {
  SerialAT.println("AT+CMGF=1"); //SMS text mode
  delay(1000);
  SerialAT.println("AT+CNMI=2,2,0,0,0"); //set sms received format
  delay(1000);
if (tipe == 1) {
    SerialAT.println("AT+CMGF=1");
    delay(1000); 
    SerialAT.println("AT+CMGS=\"+0365801715\"\r");   //Số điện thoại nhận tin nhắn phản hồi thay đổ cả dưới
    delay(1000);
    SerialAT.print("PHAT HIEN TE NGA! Vi Tri Hien Tai La: http://maps.google.com/maps?q=loc:");
    SerialAT.print(flat,6);
    SerialAT.print(",");
    SerialAT.print(flon,6);
    delay(1000);
    SerialAT.println((char)26); 
    delay(1000);
    Serial.println("DA GUI TIN NHAN");
    delay(100);
}
if(tipe == 2){
   SerialAT.println("AT+CMGF=1");
    delay(1000); 
    SerialAT.println("AT+CMGS=\"+0365801715\"\r");   //Số điện thoại nhận tin nhắn phản hồi
    delay(1000);
    SerialAT.print("stolen");
    delay(1000);
    SerialAT.println((char)26); 
    delay(1000);
    Serial.println("DA GUI TIN NHAN");
    delay(100);
}
}
