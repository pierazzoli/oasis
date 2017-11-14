
/*
    Trabalho de Microcontroladores
      Projeto OASIS - Sistema de Reaproveitamento de Agua (SRA)

            Versão 03

   \--------------------------------------------------------------------
        Autors
   \--------------------------------------------------------------------

          Eugênio Pierazzoli  - pierazzoli@gmail.com
          Meurer Goncalves    - meurersg@gmail.com
          Rodrigo Ferronato   - ferronatto32@gmail.com

   \--------------------------------------------------------------------
        Changelog
   \--------------------------------------------------------------------

         V1 - Teste básico com LDR e contole do motor
         V2 - CLasificação por tipo de Água
         V3 - Adição do controle de reservatório, motores e atuadores.

   \--------------------------------------------------------------------
        Capacidade das Portas Arduino UNO
   \--------------------------------------------------------------------

        Portas Digitais 0 - 13
            Portas pwm 3, 5, 6, 9, 10, 11
        Portas Analógicas A0, A1, A2, A3, A4, A5, A6

   \-------------------------------------------------------------------
       Uso das Portas
   \--------------------------------------------------------------------

        LDR1                          Porta A0
        LDR2                          Porta A1
        Boia 1                        Porta A2
        Boia 2                        Porta A3
        Boia 3                        Porta A4

        Motor                         Porta 4
        Valvula                       Porta 7
        SensorPeso                    Porta 8
        Seleção dos Reservatorios     Porta 12

*/

//---------------------------------------------------------------------
//      Bibliotecas
//---------------------------------------------------------------------

#include <Servo.h>              //  Carrega a biblioteca do ServoMotor


//---------------------------------------------------------------------
//      Variáveis Globais
//---------------------------------------------------------------------

Servo selecReservatorio;
int vluz_1;
int vluz_2;

int tempo_atualizaReservatorio = 15;//milisegundos

int anguloReservatorio_1 = 0;     //Posição do Servo para o reservatório 01
int anguloReservatorio_2 = 90;    //Posição do Servo para o reservatório 02
int anguloReservatorio_3 = 180;   //Posição do Servo para o reservatório 03

int classificaAgua_1 = 60;      //Qualidade da Agua 1
int classificaAgua_2 = 120;     //Qualidade da Agua 2

int boia_1 = 0;                    //Nível da Agua no reservatório 1
int boia_2 = 0;                    //Nível da Agua no reservatório 2
int boia_3 = 0;                    //Nível da Agua no reservatório 3

boolean motor_1 = false;            //Acionamento do Motor1
boolean motor_2 = false;            //Acionamento do Motor1
boolean motor_3 = false;            //Acionamento do Motor1

boolean valvula_1 = false;         //Acionamento da Válvula1



//---------------------------------------------------------------------
//      Função Setup
//---------------------------------------------------------------------
void setup()
{
  selecReservatorio.attach(12); // Porta analógica 12 onde está ligado o Servo Motor
  Serial.begin(9600);      // open the serial port at 9600 bps
  Serial.println("Inicio do Projeto OASIS");
}


//---------------------------------------------------------------------
//      Função Loop
//---------------------------------------------------------------------

void loop()
{

  analiseDeAgua();

  // Move Reservatorio baseado no LDR1
  selecReservatorio.write(vluz_1);
  Serial.println('LDR1 =' + vluz_1);

  //Delay do sistema
  delay(tempo_atualizaReservatorio );

  autoTeste();

}



//---------------------------------------------------------------------
//      Função analiseDeAgua()
//---------------------------------------------------------------------

void analiseDeAgua() {
  vluz_1 = analogRead(0);                 //Lê o LDR 1
  vluz_1 = map(vluz_1, 0, 1023, 0, 179);  //Ajusta entre 0 e 180

  vluz_2 = analogRead(1);                 //Lê o LDR 2
  vluz_2 = map(vluz_2, 0, 1023, 0, 179);  //Ajusta entre 0 e 180

  boia_1 = analogRead(3);                 //Lê a Boia 1


  if (vluz_1 < classificaAgua_1 ) {
    vluz_1 = anguloReservatorio_1;
  }
  else {
    if (vluz_1 < classificaAgua_2 ) {
      vluz_1 = anguloReservatorio_2;
    }
    else {
      vluz_1 = anguloReservatorio_3;
    }
  }
}

//---------------------------------------------------------------------
//      Função autoTeste()
//---------------------------------------------------------------------

void autoTeste() {

  if (vluz_1 = 0)
    Serial.println('Erro no sensor vluz 1 =' + vluz_1);
  else if (vluz_2 = 0)
    Serial.println('Erro no sensor vluz 2 =' + vluz_2);
  else
    return -1 ;

}

