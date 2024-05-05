#ifndef config_h
#define config_h
#include "Arduino.h"

class RunConfig{
  public:
    int preassure_alarme;
    long response_time;
    int acumulations;
    long acumulation_time;
    RunConfig();
};

// // Configuração do Max6675 Leitor de temperatura do sensor tipo K da mufla
// int thermoDO = 4;
// int thermoCS = 5;
// int thermoCLK = 6;

// //Configuração do transdutor de pressão usado (Operação de 0-5V)
// int transdutor_pin = A0;
// int transdutor_mim_value = 0;
// int transdutor_max_value = 60;

// // Configuração do módulo Bluetooth que faz a comunicação com o computador
// int bluetooth_rx = 10; //função da porta, conecta ao inverso no módulo bluetooth
// int bluetooth_tx = 11; //função da porta, conecta ao inverso no módulo bluetooth

// // Configuração do LCD

// int display_address = 0x27;
// int display_columns = 16;
// int display_rows = 2;

#endif