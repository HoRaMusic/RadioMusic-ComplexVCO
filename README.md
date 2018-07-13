Hora Music "Complex VCO V0.1" 

This software is under GNU licence and use the vult transcompiler for high performance DSP (see the code or Gnu licence).
This is a work in progress, a lot can be improved in the code but all seems to be working.

It is a alternative firmware for the music thing modular "radio music" or "chord organ" module.
This used a teensy 3.1 and the complex oscillator code is made with the vult transcompiler just like our complex oscillator developed for VCV rack: hora-music.com

Concerning the 1V/oct CV input:
Due to some hardware limitations the pitch CV input can received 3.3V, then the input range is 3.3 octaves and the 1v/oct response isn't perfect but enough to be usable in musical pieces to create melodies on a range of about 3 octaves. 
The frequency pot is locked about 1 sec after turning it to avoid pitch unstablity caused by
the teensy adc unstability.

Here is a video showing how to use module:

https://www.youtube.com/watch?v=IRLR-bwYAhg&t=32s

Anti aliasing has been improved since the video release and two features has been add:

- A long press and hold the button allow to set the fine tune of the VCO by turning the frequency knob.
- A very long press allow to record the current VCO setting, the recorded setting is automatically loaded when starting(powering) the module.  


