Hora Music "Complex VCO V0.1" 

Licence and versions: 

This is a work in progress (V0.1), a lot can be improved in the code but all seems to be working and doesn't use too much CPU or memory.
This software is under GNU licence (see teensy-vult-osc.ino or GNU licence for more informations), it is developed with the teensy audio library and the "vult" "transcompiler for high performance DSP". 
https://modlfo.github.io/vult/


What is Complex VCO V0.1?

It is an alternative firmware for the music thing modular "radio music" or "chord organ" module.
This used a teensy 3.1 and the complex oscillator code is made with the vult transcompiler just like the complex oscillator developed for VCV rack (named pure) by "hora music". https://www.hora-music.com
This said the sound is pretty different because of the hardware limites and a different way to avoid aliasing.
The using is a bit limited compare to the VCV module, there is less controllers then it isn't possible to use CV input for both folding and morphing at the same time, there isn't FM input there isn't audio input to use the module as a folder.  


Main features:

- 1V/oct input over 3.3 octaves (see "Concerning the 1V/oct CV input" for more informations).
- sync input
- cv controllable (or settable with knob) progressive morphing from sinus to triangle wave (core wave)
- core wave folding by 2, 4, 8, or 16
- cv controllable (or settable with knob) folding intensity
- fine tune
- 1 preset saving
- fantasy noisy mode

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
- A very long press until the led is upligthed (not flashing) allow to record the current VCO setting, the recorded setting is automatically loaded when starting(powering) the module.  
(Anti aliasing has been improved since the video release)


TODO: 

Maybe scale the pitch for exact note frequencies and use the frequency knob to select octave.

