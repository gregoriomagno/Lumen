
#include <Arduino.h>
#include "variaveis/variaveis.h"

void AcenderCor(int R, int G, int B)
{
    analogWrite(GND, 0); // GND.
    analogWrite(RED, R); // Red.
    analogWrite(GRE, G); // Green.
    analogWrite(BLU, B); // Blue.
    ledActivated = true;
}
void ApagarLed()
{
    digitalWrite(GND, 0); // GND.
    digitalWrite(RED, 0); // Red.
    digitalWrite(GRE, 0); // Green.
    digitalWrite(BLU, 0); // Blue.
    ledActivated = false;
}


void StractDataLed(String command)
{
    SRed = command.substring(command.indexOf(":") + 1, command.indexOf("/"));
    SGreen = command.substring(command.indexOf("/") + 1, command.lastIndexOf("/"));
    SBlue = command.substring(command.lastIndexOf("/")+1, command.indexOf("*"));

    
    SLedTimeOn = (command.substring(command.indexOf("*") + 1, command.indexOf("t")));

    LedTimeOn = SLedTimeOn.toDouble();
    VRed = atoi(SRed.c_str());
    VGreen = SGreen.toInt();
    VBlue = SBlue.toInt();
}
void ShowCores()
{
    Serial.print("Time: ");
    Serial.print(LedTimeOn);
    Serial.print("  (");
    Serial.print(SRed);
    Serial.print(",");
    Serial.print(SGreen);
    Serial.print(",");
    Serial.print(SBlue);
    Serial.println(")");
}
String getFunction(String command)
{
    return command.substring(0, command.indexOf(":"));
}
bool calcColor()
{
    if (red > green and red > blue)
    {
        Serial.print("**R**");
        return false;
    }
    else if (green > red and green > blue)
    {
        Serial.print("**G**");
        return false;
    }
    else if (blue > red and blue > green)
    {
        Serial.print("**B**");
        return false;
    }
    else
    {
        return true;
    }
}

void iniColor()
{
    if (apds2.init())
    {
        F("APDS-9960 initialization complete");
    }
    else
    {
        F("Something went wrong during APDS-9960 init!");
    }

    if (apds2.enableLightSensor(false))
    {
        F("Light sensor is now running");
    }
    else
    {
        F("Something went wrong during light sensor init!");
    }
    delay(100);
}
void readSensorColor()
{
    iniColor();
    delay(50);
    // Read the light levels (ambient, red, green, blue)
    if (!apds2.readAmbientLight(luzAmbiente) ||
        !apds2.readRedLight(red) ||
        !apds2.readGreenLight(green) ||
        !apds2.readBlueLight(blue))
    {
        Serial.println("Error reading light values");
    }
    else
    {
        //            media =(red_light+green_light+blue_light)/3;
        // Serial.print("Ambient: ");
        // Serial.print(luzAmbiente);
        // Serial.print(" Red: ");
        // Serial.print(red);
        // Serial.print(" Green: ");
        // Serial.print(green);
        // Serial.print(" Blue: ");
        // Serial.println(blue);
    }
    //
}
void iniProximity()
{
    //  Serial.println("init Proximity");
    // Initialize APDS-9960 (configure I2C and initial values)
    if (apds.init())
    {
        //Serial.println(F("APDS-9960 initialization complete"));
        F("APDS-9960 initialization complete");
    }
    else
    {
        //Serial.println(F("Something went wrong during APDS-9960 init!"));
        F("Something went wrong during APDS-9960 init!");
    }

    // Start running the APDS-9960 proximity sensor (no interrupts)
    // Settings to defaults
    if (apds.enableProximitySensor(false))
    {
        //Serial.println(F("Proximity sensor is now running"));
        F("Proximity sensor is now running");
    }
    else
    {
        //Serial.println(F("Something went wrong during sensor init!"));
        F("Something went wrong during sensor init!");
    }

    // Adjust the Proximity sensor gain
    if (!apds.setProximityGain(PGAIN_2X))
    {
        //Serial.println(F("Something went wrong trying to set PGAIN"));
        F("Something went wrong trying to set PGAIN");
    }
}
void readSensorProxi()
{
    iniProximity();
    delay(50);
    if (!apds.readProximity(proximity_data))
    {
        Serial.println("Error reading proximity value");
    }
    else
    {
        // Serial.print("Proximity: ");
        // Serial.println(proximity_data);
    }

    // Wait 250 ms before next reading
    delay(50);
}

void TocarBuzzer(int melody[], int tamanho)
{
    int notes = tamanho;

    for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2)
    {

        // calculates the duration of each note
        divider = melody[thisNote + 1];

        if (divider > 0)
        {
            // regular note, just proceed
            noteDuration = (wholenote) / divider;
        }
        else if (divider < 0)
        {
            // dotted notes are represented with negative durations!!
            noteDuration = (wholenote) / abs(divider);
            noteDuration *= 1.5; // increases the duration in half for dotted notes
        }

        // we only play the note for 90% of the duration, leaving 10% as a pause
        tone(buzzer, melody[thisNote], noteDuration * 0.9);

        // Wait for the specief duration before playing the next note.
        delay(noteDuration);

        // stop the waveform generation before the next note.
        noTone(buzzer);
    }
}