// Portas Digitais utilizadas
#define GND 6
#define RED 9
#define GRE 5
#define BLU 3

#define ledSensor 7

#define buzzer A2

SparkFun_APDS9960 apds = SparkFun_APDS9960();
SparkFun_APDS9960 apds2 = SparkFun_APDS9960();

//Variaveis cores
uint16_t luzAmbiente = 0;
uint16_t red = 0;
uint16_t green = 0;
uint16_t blue = 0;

uint8_t proximity_data = -1;

unsigned long current_time, this_time, current_time_colors, this_time_colors;

int myTimeout = 150;

bool ledActivated = false;

bool flagLoopReadColor = false;

String key, KeyFunc, SRed, SGreen, SBlue, SLedTimeOn;
int VRed, VGreen, VBlue;
double LedTimeOn;

// Notas buzzer
#define NOTE_E4 330
#define NOTE_G4 392
#define NOTE_B4 494
#define NOTE_DS5 622
#define NOTE_FS5 740
#define NOTE_B5 988
#define NOTE_D4 294
#define REST 0

int tempo = 160;

// this calculates the duration of a whole note in ms
int wholenote = (60000 * 4) / tempo;

int divider = 0, noteDuration = 0;

int melody_connected[8] = {
    REST, 1,
    NOTE_E4, 4, NOTE_G4, 4,
    REST, 1

};
int melody_desconnected[8] = {
    REST, 1,
    NOTE_G4, 4, NOTE_E4, 4,
    REST, 1};

int melody_ok[8] = {
    NOTE_B4,
    16,
    NOTE_B5,
    16,
    NOTE_FS5,
    16,
    NOTE_DS5,
    16};

int melody_erro[4] = {
    NOTE_D4,
    8,
    NOTE_D4,
    8,
};
