#include <Arduino.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <max6675.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <sensor.h>
#include <config.h>

// Configuração do Max6675 Leitor de temperatura do sensor tipo K da mufla
int thermoSO = 4;
int thermoCS = 5;
int thermoCLK = 6;

//Configuração do transdutor de pressão usado (Operação de 0-5V)
int transdutor_pin = A0;
int transdutor_alarm_pin = 5;
int transdutor_mim_value = 0;
int transdutor_max_value = 60;

// Configuração do módulo Bluetooth que faz a comunicação com o computador
int bluetooth_rx = 10; //função da porta, conecta ao inverso no módulo bluetooth
int bluetooth_tx = 11; //função da porta, conecta ao inverso no módulo bluetooth

// Configuração do LCD

int display_address = 0x27;
int display_columns = 16;
int display_rows = 2;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoSO);
Transdutor transdutor(transdutor_pin, transdutor_mim_value, transdutor_max_value, transdutor_alarm_pin);
LiquidCrystal_I2C lcd(display_address, display_columns, display_rows);
SoftwareSerial bluetooth(bluetooth_rx, bluetooth_tx);
RunConfig run_config;

// put function declarations here:.
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:

  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Pres: ");
  lcd.setCursor(0,1);
  lcd.print("Temp: ");

  Serial.begin(9600);
  bluetooth.begin(9600);
}

void loop() {
  // Obtém os dados 
  long time = millis()/1000;
  float acumulo_preassure = 0.0;
  float acumulo_temperature = 0.0;

  for (int i = 0; i < run_config.acumulations; i++)
  {
    acumulo_preassure += transdutor.read_preassure();
    acumulo_temperature += thermocouple.readCelsius();
    delay(run_config.acumulation_time);
    /* code */
  };
  
  double preassure = acumulo_preassure/float(run_config.acumulations);
  float temperature = acumulo_temperature/float(run_config.acumulations);

  // Verifica a segurança
  if (preassure >= run_config.preassure_alarme){
    // APITA O BUZZER
    transdutor.alarm_on();
  }
  else {
    transdutor.alarm_off();
  };

  // Cria o objeto a ser enviado  
  StaticJsonDocument<512> result;
  result["Tempo"] = time;
  result["Pressao"] = preassure;
  result["Temperatura"] = temperature;


  //MANDA VIA BLUETOOTH E/OU VIA CABO

  serializeJson(result, bluetooth);
  serializeJson(result, Serial);

  temperature = thermocouple.readCelsius();

  // DISPLAY LCD
  lcd.setCursor(7,0);
  lcd.print(preassure, 2);
  lcd.print("  ");
  lcd.setCursor(7,1);
  lcd.print(temperature, 2);
  lcd.print("   ");
  delay(run_config.response_time);
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}