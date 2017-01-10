#include <dht.h>
#include <Wire.h>

dht DHT;
#define DHT11_PIN 2
#define WRITE_TO_SERIAL false
#define DEBUG false

#define SLAVE_ADDRESS 0x04

int number = 150;
int counter = 0;
byte temperature = 0;
byte humidity = 0;

void setup() {
  Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
  Wire.begin(SLAVE_ADDRESS);

  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);

  analogWrite(11, 255);
  analogWrite(10, 255);
  
  digitalWrite(7, 0);
  digitalWrite(8, 0);
  digitalWrite(12, 0);
  digitalWrite(13, 0);

  if (WRITE_TO_SERIAL){ Serial.println("Software initialised"); }
  if (DEBUG){
    Serial.println("Initiate testing sequence");
    for (int i=1; i<=8; i++){
      Serial.println(" >> Sending "+i);
      go(i);
      delay(500);
    }d
    
    for (int i=97; i<=104; i++){
      Serial.println(" >> Sending "+i);
      go(i);
      delay(500);
    }
    
    for (int i=201; i<=208; i++){
      Serial.println(" >> Sending "+i);
      go(i);
      delay(500);
    }
  }
  
  // define callbacks for i2c communication
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);
}

void sendData(){
  Wire.write(number);
}

void loop() {
  int chk = DHT.read11(DHT11_PIN);
  
  number = byte(number<101?DHT.temperature+101:(number<250?255:DHT.humidity));
    
  if (WRITE_TO_SERIAL){
    if (number>101){
      if (number>=250){
        Serial.println("Keep Alive");
      } else {
        Serial.print("Temperature = ");
        Serial.println(number-101);
      }
    } else {
      Serial.print("Humidity = ");
      Serial.println(number);
    }
  }

  counter++;
  if (counter>=4){
    go(0);
    counter = 0;
    if (WRITE_TO_SERIAL){ Serial.println(" >> RESET << "); }
  }
  
  delay(1000);
}

void receiveData(int byteCount){
  byte now = 0;
  while (Wire.available()) {
    now = Wire.read();

    counter = 0;
    go(now);

    if (WRITE_TO_SERIAL){ Serial.print(" >> Received "); Serial.println(now); }
  }
}

boolean go(byte nr){
  if (nr==0){
    execute(0, 0, 0, 0, 0, 0);
    if (WRITE_TO_SERIAL){ Serial.print("00"); }
    return true;
  }

  if (nr>247){ return true; }

  int spd = min(75+floor(nr / 8)*6, 255);
  
  switch (nr % 8){
    case 1:
        execute(spd, 0, 0, 1, 0, 0); 
        if (WRITE_TO_SERIAL){ Serial.print("+0"); Serial.println(spd); }
      break;
    case 2:
        execute(spd, spd, 0, 1, 0, 1); 
        if (WRITE_TO_SERIAL){ Serial.print("++"); Serial.println(spd); }
      break;
    case 3:
        execute(0, spd, 0, 0, 0, 1); 
        if (WRITE_TO_SERIAL){ Serial.print("0+"); Serial.println(spd); }
      break;
    case 4:
        execute(spd, spd, 1, 0, 0, 1); 
        if (WRITE_TO_SERIAL){ Serial.print("RL"); Serial.println(spd); }
      break;
    case 5:
        execute(spd, spd, 0, 1, 1, 0); 
        if (WRITE_TO_SERIAL){ Serial.print("RR"); Serial.println(spd); }
      break;
    case 6:
        execute(spd, 0, 1, 0, 0, 0); 
        if (WRITE_TO_SERIAL){ Serial.print("-0"); Serial.println(spd); }
      break;
    case 7:
        execute(spd, spd, 1, 0, 1, 0); 
        if (WRITE_TO_SERIAL){ Serial.print("--"); Serial.println(spd); }
      break;
    case 0:
        execute(0, spd, 0, 0, 1, 0); 
        if (WRITE_TO_SERIAL){ Serial.print("0-"); Serial.println(floor(nr/8)); }
      break;
  }

  return true;
}

void execute(byte el, byte er, byte a1, byte a2, byte a3, byte a4){
  analogWrite(11, el);
  analogWrite(10, er);
  digitalWrite(12, a1);
  digitalWrite(13, a2);
  digitalWrite(8, a3);
  digitalWrite(7, a4);
}
