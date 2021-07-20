#include <Arduino.h>
#include <time.h>
#include <Wire.h>
#include <SparkFun_APDS9960.h>
#include "Funcoes/funcoes.h"

void setup()
{

  //Inicializando Porta Serial com a taxa de 9600
  Serial.begin(9600);

  pinMode(GND, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(GRE, OUTPUT);
  pinMode(BLU, OUTPUT);
  pinMode(ledSensor, OUTPUT);
}

void loop()
{
  current_time = millis() / 1000;
  current_time_colors = millis() / 1000;
  Serial.setTimeout(myTimeout);

  while (Serial.available() > 0)
  {
    key = Serial.readStringUntil('\n');

    KeyFunc = getFunction(key);

    Serial.println(key);
    Serial.print("KeyFunc ");
    Serial.println(KeyFunc);

    // sons buzzer
    if (key == "connected")
    {
      TocarBuzzer(melody_connected, 4);
    }
    else if (key == "OK")
    {
      Serial.println("acerto0");
      TocarBuzzer(melody_ok, 4);
    }
    else if (key == "ER")
    {
      Serial.println("erro0");
      TocarBuzzer(melody_erro, 2);
    }

    // funcoes atividades
    else if (KeyFunc == "c")
    {

      StractDataLed(key);
      AcenderCor(VRed, VGreen, VBlue);
      this_time_colors = millis() / 1000;
    }

    else if (KeyFunc == "l")
    {
      flagLoopReadColor = true;
    }
  }

  if (flagLoopReadColor)
  {
    readSensorProxi();
    if (proximity_data == 255)
    {
      digitalWrite(ledSensor, 1);
      readSensorColor();

      if (luzAmbiente > 125)
      {
        flagLoopReadColor = calcColor();
      }
      if (!flagLoopReadColor)
      {
        digitalWrite(ledSensor, 0);
      }
    }
  }

  if (ledActivated)
  {

    double time = current_time_colors - this_time_colors;
    // Serial.print(current_time_colors);
    // Serial.print("-");
    // Serial.print(this_time_colors);
    // Serial.print(" = ");
    // Serial.print(time);
    // Serial.print("  (");
    // Serial.print(LedTimeOn);
    // Serial.println("  )");

    if (time == LedTimeOn)
    {
      ApagarLed();
    }
  }
}
