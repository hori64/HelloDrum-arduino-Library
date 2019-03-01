#ifndef HelloDrum_h
#define HelloDrum_h

#include "Arduino.h"
#include "LiquidCrystal.h"
#include "EEPROM.h"

static char* item[] = {
    "SENSITIVITY",
    "THRESHOLD1",
    "THRESHOLD2",
    "RETRIGGER",
    "NOTE",
    "NOTE RIM",
    "NOTE CUP",
    };

static char* showInstrument[] = {
    "Pad 1",
    "Pad 2",
    "Pad 3",
    "Pad 4",
    "Pad 5",
    "Pad 6",
    "Pad 7",
    "Pad 8",
    "Pad 9",
    "Pad 10",
    "Pad 11",
    "Pad 12",
    "Pad 13",
    "Pad 14",
    "Pad 15",
    "Pad 16",

};

//static char* showInstrument;
static bool push;
static bool showLCD;
static int showVelocity;
static int nameIndex;
static int nameIndexMax;
static int showValue = 0;
static int padIndex = 0;
static bool edit;
static bool editCheck;
static bool editdone;
static bool change;
static int itemNumber;
static bool buttonState;
static bool buttonState_set;
static int button_set;
static int button_up;
static int button_down;
static int button_next;
static int button_back;
static int UP[7] = {5, 10, 10, 1, 1, 1, 1};  //{sensitivity, threshold1, sensitivity2, retrigger, note}
static int UP_ADVANCE[4] = {1, 50, 1, 1};  //{scantime, rim / head, pedal velocity ,masktime}


class HelloDrum
{
  public:
    HelloDrum(int pin1, int pin2);
    HelloDrum(int pin1);

    void singlePiezo(int sens, int thre1, int thre2, int retri);
    void singlePiezo();
    void dualPiezo(int sens, int thre1, int thre2, int retri);
    void dualPiezo();
    void cymbal3zone(int sens, int thre1, int thre2, int retri);
    void cymbal3zone();
    void cymbal2zone(int sens, int thre1, int thre2, int retri);
    void cymbal2zone();
    void TCRT5000(int sens, int thre1, int thre2);
    void TCRT5000();
    void FSR(int sens, int thre1, int thre2);
    void FSR();

    void settingName(char *instrumentName);
    void settingEnable();

    void loadMemory();
    void initMemory();

    int velocity;
    int pedalCC;

    int exValue;
    int exTCRT = 0;
    int exFSR = 0;
    bool hit;
    bool openHH = false;
    bool closeHH = false;
    bool hitRim;
    bool hitCup;
    bool choke;
    bool sensorFlag;
    bool moving;
    bool flag;
    bool pedalVelocityFlag = false;
    bool pedalFlag = false;
    bool chokeFlag;
    unsigned long time_hit;
    unsigned long time_end;
    unsigned long time_choke;
    unsigned long time_hit_pedal_1;
    unsigned long time_hit_pedal_2;

    char* GetItem(int i);

    int value;
    int padNum;

    int note;
    int noteRim;
    int noteCup;
    int threshold1;
    int threshold2;
    int retrigger;
    int sensitivity;

    //int initialValue[5];

  private:
    int pin_1;
    int pin_2;
    int piezoValue;
    int RimPiezoValue;
    int sensorValue;
};

class HelloDrumButton
{
  public:
    HelloDrumButton(int pin1, int pin2, int pin3, int pin4, int pin5);

    void readButtonState();

    int GetItemNumber();
    int GetEditState();
    int GetEditdoneState();
    int GetPushState();
    int GetChangeState();

    int UPDOWN;
    int NEXTBACK;

  private:
    int pin_1;
    int pin_2;
    int pin_3;
    int pin_4;
    int pin_5;

};

class HelloDrumLCD
{
  public:
    HelloDrumLCD(int pin1, int pin2, int pin3, int pin4, int pin5, int pin6);

    void show();

    LiquidCrystal lcd;

  private:
    int pin_1;
    int pin_2;
    int pin_3;
    int pin_4;
    int pin_5;
    int pin_6;

};


#endif
