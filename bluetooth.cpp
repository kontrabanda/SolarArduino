
#include "bluetooth.h"

int Bluetooth::getrxPin(){
    return rxPin;
}

void Bluetooth::setrxPin(int rx){
    rxPin = rx;
}

int Bluetooth::gettxPin(){
    return txPin;
}

void Bluetooth::settxPin(int tx){
    txPin = tx;
}

void Bluetooth::setupBluetooth(){
    btSerial = new SoftwareSerial(rxPin, txPin);
//    pinMode(txPin, OUTPUT);
//    pinMode(rxPin, INPUT);

    btSerial->begin(9600);

    Serial.println("Bluetooth with 9600");
    btSerial->write("AT+BAUD4");
    delay(1100);
    while (btSerial->available()) 
    Serial.write(btSerial->read());

    btSerial->write(Name);
    delay(1100);
    while (btSerial->available()) 
    Serial.write(btSerial->read());

    Serial.println("\nAjusting PIN - 6666");
    btSerial->write("AT+PIN6666");
    delay(1100);
    while (btSerial->available()) 
    Serial.write(btSerial->read());

    Serial.println("\nBluetooth version");
    btSerial->write("AT+VERSION\n");
    delay(1100);
    while (btSerial->available()) 
    Serial.write(btSerial->read());
}

Bluetooth::Bluetooth(char name[]){
    setName(name);
    setrxPin(2);
    settxPin(3);
}

Bluetooth::Bluetooth(char name[], int r, int t){
    setName(name);
    setrxPin(r);
    settxPin(t);
    setupBluetooth();
}

void Bluetooth::setName(char c[]){
    strcpy(Name, "AT+NAME");
    strcat(Name, c);
}
char * Bluetooth::getName(){
    return &Name[0];
}


String Bluetooth::Read(){
    char c;
    String retorno = "";
    if(btSerial->available())
        while(1){
            c = btSerial->read();
            if((int)c != -1)
              retorno += c;
            if(c == '#')
              break;
        }
    return retorno;
}

char Bluetooth::ReadFrom(){
  char c;
  c = btSerial->read();
  return c;
}

void Bluetooth::Send(char c[]){
    btSerial->print(c);
}

void Bluetooth::SendTo(char c){
    btSerial->print(c);
}

void Bluetooth::SendAcceleration(int inf){
  char temp[10];
  clearArray(temp, 10);
  
  sprintf(temp, "%d", inf);
  
  SendInformation(temp, 10, Bluetooth::ACCELERATION);
}

void Bluetooth::SendAngle(float inf_x, float inf_y, float inf_z){
  char temp[32];
  
  char tempX[10];
  char tempY[10];
  char tempZ[10];
  clearArray(tempX, 10);
  clearArray(tempY, 10);
  clearArray(tempZ, 10);
  
  dtostrf(inf_x, 5, 5, tempX);
  dtostrf(inf_y, 5, 5, tempY);
  dtostrf(inf_z, 5, 5, tempZ);
  
  for(int i=0; i<10; i++)
    temp[i] = tempX[i];
  temp[10] = '|';  
  
  for(int i=11; i<21; i++)
    temp[i] = tempY[i-11];
  temp[21] = '|';
    
  for(int i=22; i<32; i++)
    temp[i] = tempZ[i-22];
    
  SendInformation(temp, 32, Bluetooth::ANGLE);
}

void Bluetooth::SendBatteryVoltage(float inf){
  char temp[10];
  clearArray(temp, 10);
  dtostrf(inf, 5, 5, temp);
  
  SendInformation(temp, 10, Bluetooth::BATTERY_VOLTAGE);
}

void Bluetooth::SendBatteryCurrent(float inf){
  char temp[10];
  clearArray(temp, 10);
  dtostrf(inf, 5, 5, temp);
  
  SendInformation(temp, 10, Bluetooth::BATTERY_CURRENT);
}

void Bluetooth::SendSolarVoltage(float inf){
  char temp[10];
  clearArray(temp, 10);
  dtostrf(inf, 5, 5, temp);
  
  SendInformation(temp, 10, Bluetooth::SOLAR_VOLTAGE);
}

void Bluetooth::SendEnginePower(int inf){
  char temp[10];
  clearArray(temp, 10);
  sprintf(temp, "%d", inf); 
  
  SendInformation(temp, 10, Bluetooth::ENGINE_POWER);
}

void Bluetooth::clearArray(char* array, int n){
  for(int i=0; i<n; i++)
    array[i] = 'n';
}

void Bluetooth::SendInformation(const char inf[], int n, valuesTypes type){
  
      btSerial->print((char)(48 + type));
      btSerial->print('|');

      for(int i=0; i < n; i++)
        btSerial->print(inf[i]);
      
      btSerial->print('#');    
      btSerial->print('\n');
}
