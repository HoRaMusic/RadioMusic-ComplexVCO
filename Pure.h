
#ifndef PURE_H
#define PURE_H

#include <stdint.h>
#include <math.h>
#include "vultin.h"
#include "AudioStream.h"

typedef struct _tuple___real_real__ {
   fix16_t field_0;
   fix16_t field_1;
} _tuple___real_real__;

typedef struct Oscillator__ctx_type_0 {
   fix16_t pre_x;
} Oscillator__ctx_type_0;

typedef Oscillator__ctx_type_0 Oscillator_change_type;

void Oscillator__ctx_type_0_init(Oscillator__ctx_type_0 &_output_);

void Oscillator_change_init(Oscillator__ctx_type_0 &_output_);

uint8_t Oscillator_change(Oscillator__ctx_type_0 &_ctx, fix16_t x);

typedef struct Oscillator__ctx_type_1 {
   uint8_t pre;
} Oscillator__ctx_type_1;

typedef Oscillator__ctx_type_1 Oscillator_edge_type;

void Oscillator__ctx_type_1_init(Oscillator__ctx_type_1 &_output_);

void Oscillator_edge_init(Oscillator__ctx_type_1 &_output_);

uint8_t Oscillator_edge(Oscillator__ctx_type_1 &_ctx, uint8_t x);

fix16_t Oscillator_pitchToRate(fix16_t d);

fix16_t Oscillator_pitchToRateLFO(fix16_t d);

fix16_t Oscillator_foldWave(fix16_t wave, fix16_t softeningRatio, fix16_t sine);

fix16_t Oscillator_waveMorph(fix16_t firstWave, fix16_t secondWave, fix16_t morphInt);

typedef struct Oscillator__ctx_type_6 {
   fix16_t shapedWave4thStage;
   fix16_t shapedWave3rdStage;
   fix16_t shapedWave2ndStage;
   fix16_t rate;
   fix16_t phase;
   fix16_t lastTri;
   Oscillator__ctx_type_0 _inst15;
   Oscillator__ctx_type_1 _inst13;
} Oscillator__ctx_type_6;

typedef Oscillator__ctx_type_6 Oscillator_osc_type;

void Oscillator__ctx_type_6_init(Oscillator__ctx_type_6 &_output_);

void Oscillator_osc_init(Oscillator__ctx_type_6 &_output_);

void Oscillator_osc(Oscillator__ctx_type_6 &_ctx, fix16_t tune, uint8_t sync, fix16_t softening, fix16_t morph, fix16_t multiply, uint8_t mode, fix16_t audioIn, uint8_t fxMode, uint8_t desymModeIn, _tuple___real_real__ &_output_);

typedef struct Oscillator__ctx_type_7 {
   uint8_t syncBool;
   fix16_t sync;
   fix16_t softening;
   fix16_t pitch;
   fix16_t phase;
   fix16_t multiply;
   fix16_t morph;
   uint8_t modeBool;
   uint8_t fxMode;
   uint8_t desymMode;
   fix16_t complex;
   Oscillator__ctx_type_6 _inst59;
} Oscillator__ctx_type_7;

typedef Oscillator__ctx_type_7 Oscillator_process_type;

void Oscillator__ctx_type_7_init(Oscillator__ctx_type_7 &_output_);

void Oscillator_process_init(Oscillator__ctx_type_7 &_output_);

fix16_t Oscillator_process(Oscillator__ctx_type_7 &_ctx, fix16_t input);

typedef Oscillator__ctx_type_7 Oscillator_noteOn_type;

void Oscillator_noteOn_init(Oscillator__ctx_type_7 &_output_);

void Oscillator_noteOn(Oscillator__ctx_type_7 &_ctx, int note, int velocity, int channel);

typedef Oscillator__ctx_type_7 Oscillator_noteOff_type;

void Oscillator_noteOff_init(Oscillator__ctx_type_7 &_output_);

void Oscillator_noteOff(Oscillator__ctx_type_7 &_ctx, int note, int channel);

typedef Oscillator__ctx_type_7 Oscillator_controlChange_type;

void Oscillator_controlChange_init(Oscillator__ctx_type_7 &_output_);

void Oscillator_controlChange(Oscillator__ctx_type_7 &_ctx, int control, int value, int channel);

typedef Oscillator__ctx_type_7 Oscillator_default_type;

void Oscillator_default_init(Oscillator__ctx_type_7 &_output_);

void Oscillator_default(Oscillator__ctx_type_7 &_ctx);



class Pure : public AudioStream
{
public:
  Pure(void) : AudioStream(0, NULL)
  {
     Oscillator_process_init(data);
  }

  void begin() {
    Oscillator_default(data);
  }

  // Handles note on events
  void noteOn(int note, int velocity, int channel){
    // If the velocity is larger than zero, means that is turning on
    if(velocity) Oscillator_noteOn(data, note, velocity, channel);
    else         Oscillator_noteOff(data, note, channel);
  }

  // Handles note off events
  void noteOff(int note, int velocity, int channel) {
    Oscillator_noteOff(data, note, channel);

  }

  // Handles control change events
  void controlChange(int control, int value, int channel) {
    Oscillator_controlChange(data, control, value, channel);
  }

  virtual void update(void);

private:
  Oscillator_process_type data;

};

#endif // PURE_H
