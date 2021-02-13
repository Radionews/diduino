//---Radionews---https://github.com/Radionews
//---Walhi---https://github.com/walhi
//---13.02.2021---

#define ST A3
#define SH A2
#define DS A1
#define AR0 2
#define AR1 3
#define AR2 4
#define READ 5
#define CS 6
#define WRITE 7
#define DS_POWER 8
#define DS_DATA 9

#define BUF_LEN 8

/* Voltage control (for programming chips) */
#define voltageControl A4
#define rTop 10000.0
#define rBottom 2200.0


#include <OneWire.h>
OneWire ds(DS_DATA);

typedef enum chipType {
  NONE = 0,
  RE3 = 1,
  RT4 = 2,
  RT14 = 3,
  RT5 = 4
} Chip;

typedef enum mode {
  WAIT,
  Read,
  Write,
  VOLTAGE,
  TEMPERATURE
} Modes;

//---prototipes---
void init_power5959();
void increase_power();
void decrease_power();
void select_chip (chipType new_chip);
void cs_set(chipType chip, bool state);
float get_voltage (void);
void load_shift();
byte read_byte(uint16_t in);
byte write_byte(uint16_t addr, byte in);

//---var---
unsigned char data_array[512];
unsigned char uart_read_temp = 0;

byte power = 0;
word shift_data = 0;
chipType chip = NONE;
Modes mode = WAIT;
uint8_t log_enable = false;
uint16_t start_address = 0x0000;
uint16_t end_address = 0x0000;

uint8_t buf[BUF_LEN];

uint16_t number_of_impulses = 1000;
uint16_t length_of_impulse = 40;
uint8_t count = 0, r_data = 0;
byte out = 0;
byte temp = 0;
uint16_t i = 0, j = 0;

void setup() {
  //инициализация сдвигового регистра повыщающего преобразователя
  init_power5959();
  
  pinMode(ST, OUTPUT);
  pinMode(SH, OUTPUT);
  pinMode(DS, OUTPUT);
  pinMode(WRITE, OUTPUT);
  digitalWrite(WRITE,LOW);
  pinMode(CS, OUTPUT);
  digitalWrite(CS,HIGH);
  pinMode(DS_POWER, OUTPUT);
  digitalWrite(DS_POWER,HIGH);
  pinMode(READ, INPUT);
  pinMode(AR0, OUTPUT);
  pinMode(AR1, OUTPUT);
  pinMode(AR2, OUTPUT);
  digitalWrite(AR0,LOW);
  digitalWrite(AR1,LOW);
  digitalWrite(AR2,LOW);

  Serial.begin(115200);
  Serial.println("ARDUINO PROGRAMMER DIDUINO VER1.0");

}

void loop() {
  switch (mode) {
    case Read:
      if (chip == NONE) {
        mode = WAIT;
        break;
      }
      for (i = start_address; i <= end_address; i++) {
        uint8_t data = read_byte(i);
        Serial.write(&data, sizeof(data));
        if (i == end_address) break; // Защита от переполнения uint16
      }
      delay(100);
      mode = WAIT;
      break;
      
    case Write:
      if (chip == NONE) {
        mode = WAIT;
        break;
      }
      for (i = start_address; i <= end_address; i++) {
        while(Serial.available()==0);
        r_data = Serial.read();
        count++;
        r_data = write_byte(i, r_data);
        Serial.write(r_data);
        if (i == end_address) break;
      }
      Serial.print("Write success.");
      mode = WAIT;
      break;
      
    case VOLTAGE:
      Serial.println(get_voltage(), 1);
      mode = WAIT;
      break;

    case TEMPERATURE:
      digitalWrite(DS_POWER,LOW);
      delay(100);
      digitalWrite(DS_POWER,HIGH);
      delay(100);
      Serial.print("Temperature: ");
      byte data[2];
      ds.reset();
      ds.write(0xCC);
      ds.write(0x44);
      delay(100); 
      ds.reset();
      ds.write(0xCC); 
      ds.write(0xBE);

      data[0] = ds.read(); // Читаем младший байт значения температуры
      data[1] = ds.read(); // А теперь ст``арший
      digitalWrite(DS_POWER,LOW);
      Serial.println(((data[1] << 8) | data[0]) * 0.0625);
      mode = WAIT;
      break;
      
    default:
      if (chip == NONE) Serial.println("Chip not selected!");
      Serial.println("Wait commands...");
      while (Serial.available()) Serial.read();
      do {} while (Serial.available() == 0);
      char incomingByte = Serial.read();
      while (Serial.available()) Serial.read();
      switch (incomingByte) {
        case 'r': mode = Read; break;
        case 'w': mode = Write; break;
        case 'v': mode = VOLTAGE; break;
        case 't': mode = TEMPERATURE; break;
        case 'g': select_chip(RE3); break;
        case 'h': select_chip(RT4); break;
        case 'i': select_chip(RT14); break;
        case 'j': select_chip(RT5); break;
      }
  }
}

void select_chip (chipType new_chip) {
  switch (new_chip) {
    case RE3:
      chip = new_chip;
      end_address = 0x001f;
      break;
    case RT4:
      chip = new_chip;
      end_address = 0x00ff;
      break;
    case RT14:
      chip = new_chip;
      end_address = 0x07cf;
      break;
    case RT5:
      chip = new_chip;
      end_address = 0x01ff;
      break;
    default:
      chip = NONE;
      end_address = 0x0000;
  }
}
void init_power5959(){
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(A0, OUTPUT);
  digitalWrite(A0,HIGH);  
}

//увеличить напряжение программирования
void increase_power(){
  if(power==0)      power = 1;
  else{
    if(power!=128)  power = power>>1;
  }
  digitalWrite(11, LOW);
  shiftOut(10, 12, MSBFIRST, power); 
  digitalWrite(11, HIGH);
  digitalWrite(A0,LOW);
}

//уменьшить напряжение программирования
void decrease_power(){
  if(power==1){
    power = 0;
    digitalWrite(A0,HIGH);
  }
  else{ power = power<<1;}
  digitalWrite(11, LOW);
  shiftOut(10, 12, MSBFIRST, power); 
  digitalWrite(11, HIGH);
  digitalWrite(A0,LOW);
}

//загрузка данных в сдвиговые регистры
void load_shift(){
  digitalWrite(SH, LOW);
  shiftOut(DS, ST, LSBFIRST, (shift_data>>8)&0xFF);
  shiftOut(DS, ST, LSBFIRST, shift_data&0xFF);   
  digitalWrite(SH, HIGH);
}

byte read_byte(uint16_t in){
  digitalWrite(WRITE,LOW);
  
  shift_data = in;
  cs_set(chip,true);
  load_shift();

  out = 0;
  temp = 0;
  for(j=0;j<8;j++){
    if((j&0x01)==1)     {digitalWrite(AR0,HIGH);}
    else                {digitalWrite(AR0,LOW);}

    if(((j>>1)&0x01)==1){digitalWrite(AR1,HIGH);}
    else                {digitalWrite(AR1,LOW);}

    if(((j>>2)&0x01)==1){digitalWrite(AR2,HIGH);}
    else                {digitalWrite(AR2,LOW);}

    delay(1);
    if(((chip==RT4)||(chip == RT14))&&(j>3)){
      return out;
    }
    else{
      temp = !digitalRead(READ);
      out |= temp<<j;
    }
    
  }
  return out;
}

void cs_set(chipType chip, bool state){
  switch(chip){
    case NONE:
    break;
    case RE3:
      digitalWrite(CS,state);
    break;
    case RT4:
      digitalWrite(CS,state);
    break;
    case RT14:
      digitalWrite(CS,state);
    break;
    case RT5:
      if(state){
        digitalWrite(CS,HIGH);
        shift_data |= (1<<9)|(1<<12)|(1<<11);
        shift_data &= ~(1<<10);
      }
      else{
        digitalWrite(CS,LOW);
      }
      
    break; 
  }
}

byte write_byte(uint16_t addr, byte in){
  //на всякий случай перед манипуляциями опускаем ножку записи, мало ли она была чем то поднята
  digitalWrite(WRITE,LOW);
  
  //линия(ии) cs на чтение
  cs_set(chip,true);
  
  //выставляем адрес ячейки
  shift_data = addr;
  load_shift();
  
  out = 0;
  for(j=0;j<8;j++){
    //выставляем бит в ячейке
    if((j&0x01)==1)     digitalWrite(AR0,HIGH);
    else                digitalWrite(AR0,LOW);
    if(((j>>1)&0x01)==1)digitalWrite(AR1,HIGH);
    else                digitalWrite(AR1,LOW);
    if(((j>>2)&0x01)==1)digitalWrite(AR2,HIGH);
    else                digitalWrite(AR2,LOW);
    delay(1);
    if(((chip==RT4)||(chip == RT14))&&(j>3)){
      return out;
    }
    else{  
  
      if((((in>>j)&0x01)>(!digitalRead(READ))) && chip!= RT5){        
        for(int16_t k=0;k<number_of_impulses;k++){
          cs_set(chip,false); 
          digitalWrite(WRITE,HIGH);
          if(length_of_impulse<1000){delayMicroseconds(length_of_impulse);}
          else                      {delay(length_of_impulse/1000);}
          digitalWrite(WRITE,LOW);
          cs_set(chip,true);
          
          if((length_of_impulse*5)<1000){delayMicroseconds(length_of_impulse*5);}
          else                          {delay(length_of_impulse*5/1000);}
          
          if(((in>>j)&0x01) == (!digitalRead(READ))) break;
        }
      }
      
      if((((in>>j)&0x01)<(!digitalRead(READ))) && chip == RT5){
        for(int16_t k=0;k<number_of_impulses;k++){
          cs_set(chip,false); 
          digitalWrite(WRITE,HIGH);
          if(length_of_impulse<1000){delayMicroseconds(length_of_impulse);}
          else                      {delay(length_of_impulse/1000);}
          digitalWrite(WRITE,LOW);
          cs_set(chip,true);
          
          if((length_of_impulse*5)<1000){delayMicroseconds(length_of_impulse*5);}
          else                          {delay(length_of_impulse*5/1000);}
          
          if(((in>>j)&0x01) == (digitalRead(READ))) break;
        }
      } 
    }
    out |= (!digitalRead(READ))<<j;
  }
  return out;
}

float get_voltage (void) {
  float vADC = (analogRead(voltageControl) / 1024.) * 4.85;
  float current = vADC / rBottom;
  return (current * (rTop + rBottom));
}
