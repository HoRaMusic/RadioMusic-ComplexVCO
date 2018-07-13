
/*///////////////////////////////////////////////////////////////////////////// Licence ////////////////////////////////////////////

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

Also add information on how to contact you by electronic and paper mail.

If the program is interactive, make it output a short notice like this
when it starts in an interactive mode:

    Gnomovision version 69, Copyright (C) year name of author
    Gnomovision comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
    This is free software, and you are welcome to redistribute it
under certain conditions; type `show c' for details.

/////////////////////////////////////////////////////////////////////////////// Vult licence ///////////////////////////////////////////

The Vult transcompiler used to develop the complex oscillator core is work of Leonardo Laguna Ruiz.
https://modlfo.github.io/vult/

MIT License

Copyright (c) 2017 Leonardo Laguna Ruiz

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

#include <Wire.h>
#include <SPI.h>
#include <Audio.h>
#include <Bounce.h>
#include <EEPROM.h>
#include "Pure.h"

#define ADC_BITS 13
#define ADC_MAX_VAL 8192
#define POT_TOLERANCE 100
#define FOLD2 0
#define FOLD4 1
#define FOLD8 2
#define FOLD16 3
#define CHORD_POT_PIN 9 // pin for Chord pot
#define CHORD_CV_PIN 6 // pin for Chord CV 
#define ROOT_POT_PIN 7 // pin for Root Note pot
#define ROOT_CV_PIN 8 // pin for Root Note CV
#define RESET_BUTTON 8 // Reset button 
#define RESET_LED 11 // Reset LED indicator 
#define RESET_CV 9 // Reset pulse in / out
#define BANK_BUTTON 2 // Bank Button 
#define LED0 6
#define LED1 5
#define LED2 4
#define LED3 3
#define FRAME_DIVIDER 1000
#define SHORT_PRESS_DURATION 10
#define LONG_PRESS_DURATION 500
#define shiftTime 1000

Bounce pushbutton1 = Bounce(RESET_BUTTON, 40);  // 10 ms debounce
int lastParam2 = 400;
int lastPitch = 400; 
int lastParam1Fold = 0; 
int lastParam1Morph = 0; 
int morphing = 1;
int folding = 0;
int lastMorphing = 1;
int lastFolding = 1;
int numberOfFolding = 1;
int desym = 0; 
int param2PotRaw;
int lastDesym = 4000;
int param1CV = 0;
int fineTune = 800;
int lastFineTuneParam = 4000;
boolean hasBeenReleased = false;
boolean startCounter = false;
boolean canControl = true;
boolean hasBeenSaved = false;
boolean hasBeenLoad = false;
byte mode = 0;
int param1 = 64;
int param2 = 64;
int previousInstrumentsParams[4][4]; // [instrument][paramNumber]
int frame;
int dividedFrame;
//byte bassDrumParams[4];
int shiftTimer = 0;
boolean activeTrig = false;
boolean activeOpenHatTrig = false;
boolean blockKnob = false;
int lastPotValue = 800;
int lastUnlockedParam = 800;
boolean delock = true;
boolean delock2 = true;
int lockCounter = 0;
elapsedMillis buttonTimer = 0;
elapsedMillis lockOut = 0;
boolean shortPress = false;
boolean longPress = false;
elapsedMillis pulseOutTimer = 0;
uint32_t flashTime = 10;
int reverbKnobParam = 0;
int reverbKnobParam2 = 0;
int sampleNumber1 = 0;
int sampleNumber2 = 0;
int pitchCV = 0;
int foldIndex = 1;
boolean flashing = false;
boolean modeChanged = false; 
byte instrument;
int buttonState = 0;
boolean controlPage2 = false;
int pitchParam = 0;
int EEPROM_Mode_Frame = 0;
int DIVIDED_EEPROM_Mode_Frame = 0;
Pure                ComplexVCO;

AudioMixer4              mixer1;         //xy=489,362
AudioOutputAnalog        dac1;           //xy=655,361
AudioConnection          patchCord1(ComplexVCO, 0, mixer1, 0);
AudioConnection          patchCord5(mixer1, dac1);

void setup() {
  mixer1.gain(0, 2.00);
  mixer1.gain(1, 0.0);
  mixer1.gain(2, 3.0);
  mixer1.gain(3, 3.0);
  AudioMemory(8); 
  ComplexVCO.begin();
  pinMode(BANK_BUTTON,INPUT);
  pinMode(RESET_BUTTON, INPUT);
  pinMode(RESET_CV, INPUT); 
  pinMode(RESET_LED, OUTPUT);
  pinMode(LED0,OUTPUT);
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  analogReadRes(ADC_BITS); 
}

void loop() {
  
  if (hasBeenLoad == false)
  {
        if (EEPROM.read(0) * 33 <= 8192 && EEPROM.read(0) * 33 >= 0)
      {
          lastPitch = EEPROM.read(0) * 33;
          Serial.println("PITCH LOADED: ");
      }
      else
      {
          lastPitch = 800;
      }
      if (EEPROM.read(1) * 33 <= 8192 && EEPROM.read(1) * 33 >= 0)
      {
          lastParam1Fold = EEPROM.read(1) * 33;
          folding = lastParam1Fold; 
      }
      else
      {
          lastParam1Fold = 800;
      }
      if (EEPROM.read(2) * 33 <= 8192 && EEPROM.read(2) * 33 >= 0)
      {
          lastParam1Morph = EEPROM.read(2) * 33;
          morphing = lastParam1Morph;
      }
      else
      {
          lastParam1Morph = 800;
      }
      if (EEPROM.read(3) <= 1 && EEPROM.read(3) >= 0)
      {
          desym = EEPROM.read(3);
      }
      else
      {
          desym = 0;
      }
      if (EEPROM.read(4) * 8 <= 8192 && EEPROM.read(4) * 8 >= 0)
      {
          lastFineTuneParam = EEPROM.read(4) * 8;
          fineTune = lastFineTuneParam;
      }
      else
      {
          lastFineTuneParam = 800;
      }
      if (EEPROM.read(5) <= 3 && EEPROM.read(5) >= 0)
      {
          foldIndex = EEPROM.read(5);
          numberOfFolding = foldIndex + 1;
      }
      else
      {
          foldIndex = 0;
          numberOfFolding = 1;
      }
      hasBeenLoad = true;
  }
  checkButton(); // get button state and determine short or long press to increment foldingIndex, select page 1-2, save setting or access fine tune   
  getKnobsAndCVinputs(); // get pot and cv values, mix these if needed, set the lock for frequency param to avoid unstable pitch after a short time after turning the knob and attribute the values to variables.
  selectFoldingIndex(); // select the current folding index and light up the corresponding led
  controlComplexVCOParams(); // use the cv and pot value to control the ComplexVCO parameters 
  /*Serial.print(AudioProcessorUsage());
  Serial.print(",");
  Serial.print(AudioProcessorUsageMax());
  Serial.print("    ");
  Serial.print("Memory: ");
  Serial.print(AudioMemoryUsage());
  Serial.print(",");*/
}


