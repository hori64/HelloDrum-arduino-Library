/*
  EXAMPLE - 2 Zone Hi-Hat with TCRT5000 Controller

  This sample code tesed with YAMAHA PCY135/PCY155.
  https://open-e-drums.tumblr.com/
*/

/* NOTICE

  You have to install the MIDI library.
  MIDI : https://playground.arduino.cc/Main/MIDILibrary

*/

//////////////////////////////////////////   SETTING VALUE   ////////////////////////////////////////////

//Determine the setting value.
//By changing the number in this array you can set sensitivity, threshold and so on.

int HIHAT[8] = {
    100, //sensitivity
    10,  //threshold
    30,  //scan time
    10,  //mask time
    46,  //note of open
    42,  //note of close
    26,  //note of open edge
    22   //note of close edge
};

int HIHAT_CONTROL[5] = {
    90, //sensitivity
    12, //threshold1
    80, //threshold2
    10, //scan time
    44  //note of pedal
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <MIDI.h>
#include <hellodrum.h>
MIDI_CREATE_DEFAULT_INSTANCE();

//Please name your piezo and sensor.
//So, you need the same number of lines as the number of pads.
//The piezo named "hihat" is connected to the A0 and A1 pin.
//The TCRT5000 named "hihatcontrol" is connected to the A2 pin.
HelloDrum hihat(0, 1);
HelloDrum hihatControl(2);

void setup()
{
  //If you use Hairless MIDI, you have to comment out the next line.
  //MIDI.begin(10);

  //And uncomment the next two lines.
  MIDI.begin();
  Serial.begin(38400);
}

void loop()
{
  //Piezo sensing is done in this line. And it is returned as a velocity of 127 stages.
  //For each pad, one line is required.
  //So, you need the same number of lines as the number of pads or controller.
  hihat.HH(HIHAT[0], HIHAT[1], HIHAT[2], HIHAT[3]);
  hihatControl.TCRT5000(HIHAT_CONTROL[0], HIHAT_CONTROL[1], HIHAT_CONTROL[2], HIHAT_CONTROL[3]);

  //MIDI signals are transmitted with this IF statement.
  //bow
  if (hihat.hit == true)
  {
    //check open or close
    //1.open
    if (hihatControl.openHH == true)
    {
      MIDI.sendNoteOn(HIHAT[4], hihat.velocity, 10); //(note, velocity, channel)
      MIDI.sendNoteOff(HIHAT[4], 0, 10);
    }
    //2.close
    else
    {
      MIDI.sendNoteOn(HIHAT[5], hihat.velocity, 10); //(note, velocity, channel)
      MIDI.sendNoteOff(HIHAT[5], 0, 10);
    }
  }

  //edge
  else if (hihat.hitRim == true)
  {
    //check open or close
    //1.open
    if (hihatControl.openHH == true)
    {
      MIDI.sendNoteOn(HIHAT[6], hihat.velocity, 10); //(note, velocity, channel)
      MIDI.sendNoteOff(HIHAT[6], 0, 10);
    }
    //2.close
    else
    {
      MIDI.sendNoteOn(HIHAT[7], hihat.velocity, 10); //(note, velocity, channel)
      MIDI.sendNoteOff(HIHAT[7], 0, 10);
    }
  }

  //when pedal is closed
  if (hihatControl.closeHH == true)
  {
    MIDI.sendNoteOn(HIHAT_CONTROL[4], hihatControl.velocity, 10); //(note, velocity, channel)
    MIDI.sendNoteOff(HIHAT_CONTROL[4], 0, 10);
  }

  //sending state of pedal with controll change
  if (hihatControl.moving == true)
  {
    MIDI.sendControlChange(4, hihatControl.pedalCC, 10);
  }
}
