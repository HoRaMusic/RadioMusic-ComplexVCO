Hora Music "Complex VCO V0.1" 

Licence and versions: 

This software is under GNU licence, it use the teensy audio library, and use the vult transcompiler for high performance DSP (see the code or Gnu licence).
This is a work in progress (V0.1), a lot can be improved in the code but all seems to be working and doesn't use too much CPU or memory.


What is Complex VCO V0.1?

It is an alternative firmware for the music thing modular "radio music" or "chord organ" module.
This used a teensy 3.1 and the complex oscillator code is made with the vult transcompiler just like our complex oscillator developed for VCV rack: hora-music.com


Concerning the 1V/oct CV input:

Due to some hardware limites the pitch CV input can received 3.3V, then the input range is 3.3 octaves and the 1v/oct response isn't perfect but enough to be usable in musical pieces to create melodies on a range of about 3 octaves. 
The frequency pot is locked about 1 sec after turning it to avoid pitch unstablity caused by
the teensy adc unstability.


Load the firmware: 

Put this files in a folder named "teensy-vult-osc".
Place this folder in your sketch depositary, install the teensy audio library if needed.
Open teensy-vult-osc.ino (with the ARDUINO IDE) and upload the sketch with this setting: 
card: teensy 3.1-3.2    
CPU speed: 96 MHZ (overclock)    
USB type: serial.


Use the module : 

Here is a video showing how to use module:
https://www.youtube.com/watch?v=IRLR-bwYAhg&t=32s
Two features has been added:
- A long press and hold the button allows to set the fine tune of the VCO by turning the frequency knob.
- A very long press allow to record the current VCO setting, the recorded setting is automatically loaded when starting(powering) the module.  
(Anti aliasing has been improved since the video release)

TODO: 

Maybe scale the pitch for exact note frequencies and use the frequency knob to select octave.

