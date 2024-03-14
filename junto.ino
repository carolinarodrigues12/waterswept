#include <SoftwareSerial.h>

SoftwareSerial SIM900(2, 3); 

#include <String.h>

#define echo 4
#define trig 7
#define limite 8 //limite distância por definir //dúvidas
#define APN_OPERADORA internet
#define API_WRITE 3XWEVIXWQKIJIVKK
float t = 0;

unsigned long tempo;
double distancia;

void setup() {
  
   SIM900.begin(19200);   //Begin serial communication with Arduino and SIM900
  // Give time to your GSM shield log on to network
  delay(20000); 
    
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  Serial.begin(9600);

  digitalWrite(trig,LOW);

}

void loop() {
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  tempo = pulseIn(echo, HIGH);

  distancia  = tempo/58;

  Serial.println(distancia);

  if distancia //por definir //dúvida

  delay(500);

  {
      //float t = dht.readTemperature(); 
      t = t + 1;  //simula envio de leituras do sensor em incrementos de 1
      delay(100);   
         
      Serial.print("Sensor1 = ");
      Serial.println(t);
      
   
  if (SIM900.available())
    Serial.write(SIM900.read());
 
  SIM900.println("AT");
  delay(1000);
  ShowSerialData();     //mostra resposta do modulo SIM900
 
  SIM900.println("AT+CSTT=\"APN_OPERADORA\"");//start task and setting the APN,
  delay(1000);
  ShowSerialData();     //mostra resposta do modulo SIM900
 
  SIM900.println("AT+CIICR");//bring up wireless connection
  delay(3000);
  ShowSerialData();     //mostra resposta do modulo SIM900
 
  SIM900.println("AT+CIFSR");//get local IP adress
  delay(2000);
  ShowSerialData();     //mostra resposta do modulo SIM900
 
  SIM900.println("AT+CIPSPRT=0");
  delay(3000);
  ShowSerialData();     //mostra resposta do modulo SIM900
  
  SIM900.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");//start up the connection
  delay(6000);
  ShowSerialData();     //mostra resposta do modulo SIM900
 
  SIM900.println("AT+CIPSEND");//begin send data to remote server
  delay(4000);
  ShowSerialData();     //mostra resposta do modulo SIM900
  
  String str="GET https://api.thingspeak.com/update?api_key=3XWEVIXWQKIJIVKK&field1=0" + String(t);
  Serial.println(str);
  SIM900.println(str);//begin send data to remote server
  delay(4000);
  ShowSerialData();     //mostra resposta do modulo SIM900
 
  SIM900.println((char)26);//sending
  delay(5000);//waitting for reply, important! the time is base on the condition of internet 
  SIM900.println();
   ShowSerialData();     //mostra resposta do modulo SIM900
 
  SIM900.println("AT+CIPSHUT");//close the connection
  delay(100);
  ShowSerialData();     //mostra resposta do modulo SIM900
} 

void sendSMS() {
  // AT command to set SIM900 to SMS mode
  SIM900.print("AT+CMGF=1\r"); 
  delay(100);

  // REPLACE THE X's WITH THE RECIPIENT'S MOBILE NUMBER
  // USE INTERNATIONAL FORMAT CODE FOR MOBILE NUMBERS
  SIM900.println("AT+CMGS=\"+351915458519\""); 
  delay(100);
  
  // REPLACE WITH YOUR OWN SMS MESSAGE CONTENT
  SIM900.println("Ola Mundo."); 
  delay(100);

  // End AT command with a ^Z, ASCII code 26
  SIM900.println((char)26); 
  delay(100);
  SIM900.println();
  // Give module time to send SMS
  delay(5000); 
}

void ShowSerialData()
{
  while(SIM900.available()!=0)
  Serial.write(SIM900.read());
  delay(5000); 
  
}
