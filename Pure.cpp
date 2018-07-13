
#include "Pure.h"

void Oscillator__ctx_type_0_init(Oscillator__ctx_type_0 &_output_){
   Oscillator__ctx_type_0 _ctx;
   _ctx.pre_x = 0x0 /* 0.000000 */;
   _output_ = _ctx;
   return ;
}

void Oscillator_change_init(Oscillator__ctx_type_0 &_output_){
   Oscillator__ctx_type_0_init(_output_);
   return ;
}

uint8_t Oscillator_change(Oscillator__ctx_type_0 &_ctx, fix16_t x){
   uint8_t v;
   v = (_ctx.pre_x != x);
   _ctx.pre_x = x;
   return v;
}

void Oscillator__ctx_type_1_init(Oscillator__ctx_type_1 &_output_){
   Oscillator__ctx_type_1 _ctx;
   _ctx.pre = 0;
   _output_ = _ctx;
   return ;
}

void Oscillator_edge_init(Oscillator__ctx_type_1 &_output_){
   Oscillator__ctx_type_1_init(_output_);
   return ;
}

uint8_t Oscillator_edge(Oscillator__ctx_type_1 &_ctx, uint8_t x){
   uint8_t ret;
   ret = (x && bool_not(_ctx.pre));
   _ctx.pre = x;
   return ret;
}

fix16_t Oscillator_pitchToRate(fix16_t d){
   return fix_mul(0xc /* 0.000185 */,fix_exp(fix_mul(0xec9 /* 0.057762 */,d)));
}

fix16_t Oscillator_pitchToRateLFO(fix16_t d){
   return fix_mul(0x0 /* 0.000003 */,fix_exp(fix_mul(0xec9 /* 0.057762 */,d)));
}

fix16_t Oscillator_foldWave(fix16_t wave, fix16_t softeningRatio, fix16_t sine){
   fix16_t cubeWave;
   cubeWave = fix_mul(fix_mul(sine,fix_abs(sine)),fix_abs(sine));
   fix16_t shapedWave;
   shapedWave = 0x0 /* 0.000000 */;
   uint8_t _cond_73;
   _cond_73 = (wave > 0x0 /* 0.000000 */);
   if(_cond_73){
      shapedWave = (wave + (- fix_mul(cubeWave,softeningRatio)));
   }
   else
   {
      uint8_t _cond_72;
      _cond_72 = (wave <= 0x0 /* 0.000000 */);
      if(_cond_72){
         shapedWave = (wave + (- fix_mul(cubeWave,softeningRatio)));
      }
   }
   return shapedWave;
}

fix16_t Oscillator_waveMorph(fix16_t firstWave, fix16_t secondWave, fix16_t morphInt){
   fix16_t shapedWave;
   shapedWave = 0x0 /* 0.000000 */;
   uint8_t _cond_75;
   _cond_75 = (firstWave > secondWave);
   if(_cond_75){
      shapedWave = (firstWave + (- fix_mul((firstWave + (- secondWave)),morphInt)));
   }
   else
   {
      uint8_t _cond_74;
      _cond_74 = (firstWave <= secondWave);
      if(_cond_74){
         shapedWave = (firstWave + fix_mul((secondWave + (- firstWave)),morphInt));
      }
   }
   return shapedWave;
}

void Oscillator__ctx_type_6_init(Oscillator__ctx_type_6 &_output_){
   Oscillator__ctx_type_6 _ctx;
   _ctx.shapedWave4thStage = 0x0 /* 0.000000 */;
   _ctx.shapedWave3rdStage = 0x0 /* 0.000000 */;
   _ctx.shapedWave2ndStage = 0x0 /* 0.000000 */;
   _ctx.rate = 0x0 /* 0.000000 */;
   _ctx.phase = 0x0 /* 0.000000 */;
   _ctx.lastTri = 0x0 /* 0.000000 */;
   Oscillator__ctx_type_0_init(_ctx._inst15);
   Oscillator__ctx_type_1_init(_ctx._inst13);
   _output_ = _ctx;
   return ;
}

void Oscillator_osc_init(Oscillator__ctx_type_6 &_output_){
   Oscillator__ctx_type_6_init(_output_);
   return ;
}

void Oscillator_osc(Oscillator__ctx_type_6 &_ctx, fix16_t tune, uint8_t sync, fix16_t softening, fix16_t morph, fix16_t multiply, uint8_t mode, fix16_t audioIn, uint8_t fxMode, uint8_t desymModeIn, _tuple___real_real__ &_output_){
   uint8_t reset;
   reset = 0;
   uint8_t dec;
   dec = 0;
   fix16_t audioInput;
   audioInput = audioIn;
   uint8_t _cond_76;
   _cond_76 = Oscillator_edge(_ctx._inst13,sync);
   if(_cond_76){
      reset = 1;
   }
   uint8_t _cond_78;
   _cond_78 = Oscillator_change(_ctx._inst15,tune);
   if(_cond_78){
      uint8_t _cond_77;
      _cond_77 = (mode == 1);
      if(_cond_77){
         _ctx.rate = Oscillator_pitchToRate(fix_mul(tune,0xc0000 /* 12.000000 */));
         _ctx.rate = (_ctx.rate >> 2);
      }
      else
      {
         _ctx.rate = Oscillator_pitchToRateLFO(tune);
         _ctx.rate = (_ctx.rate >> 2);
      }
   }
   if(reset){ _ctx.phase = 0x0 /* 0.000000 */; }
   else
   { _ctx.phase = ((_ctx.phase + _ctx.rate) % 0x10000 /* 1.000000 */); }
   fix16_t sine;
   sine = fix_sin(fix_mul(0x6487e /* 6.283185 */,_ctx.phase));
   fix16_t polyBlep;
   polyBlep = 0x0 /* 0.000000 */;
   uint8_t _cond_80;
   _cond_80 = (_ctx.phase < _ctx.rate);
   if(_cond_80){
      fix16_t t;
      t = fix_div(_ctx.phase,_ctx.rate);
      polyBlep = (t + t + (- fix_mul(t,t)) + -0x10000 /* -1.000000 */);
   }
   else
   {
      uint8_t _cond_79;
      _cond_79 = (_ctx.phase > (0x10000 /* 1.000000 */ + (- _ctx.rate)));
      if(_cond_79){
         fix16_t t2;
         t2 = fix_div((_ctx.phase + -0x10000 /* -1.000000 */),_ctx.rate);
         polyBlep = (fix_mul(t2,t2) + t2 + t2 + 0x10000 /* 1.000000 */);
      }
      else
      {
         polyBlep = 0x0 /* 0.000000 */;
      }
   }
   fix16_t fModPhase;
   fModPhase = ((_ctx.phase + 0x8000 /* 0.500000 */) % 0x10000 /* 1.000000 */);
   fix16_t polyBlepHP;
   polyBlepHP = 0x0 /* 0.000000 */;
   uint8_t _cond_82;
   _cond_82 = (fModPhase < _ctx.rate);
   if(_cond_82){
      fix16_t t;
      t = fix_div(fModPhase,_ctx.rate);
      polyBlepHP = (t + t + (- fix_mul(t,t)) + -0x10000 /* -1.000000 */);
   }
   else
   {
      uint8_t _cond_81;
      _cond_81 = (fModPhase > (0x10000 /* 1.000000 */ + (- _ctx.rate)));
      if(_cond_81){
         fix16_t t2;
         t2 = fix_div((fModPhase + -0x10000 /* -1.000000 */),_ctx.rate);
         polyBlepHP = (fix_mul(t2,t2) + t2 + t2 + 0x10000 /* 1.000000 */);
      }
      else
      {
         polyBlepHP = 0x0 /* 0.000000 */;
      }
   }
   fix16_t tri;
   tri = 0x0 /* 0.000000 */;
   fix16_t square;
   square = 0x0 /* 0.000000 */;
   uint8_t _cond_83;
   _cond_83 = (_ctx.phase < 0x8000 /* 0.500000 */);
   if(_cond_83){
      square = 0x10000 /* 1.000000 */;
   }
   else
   {
      square = -0x10000 /* -1.000000 */;
   }
   square = (square + polyBlep);
   square = (square + (- polyBlepHP));
   tri = (fix_mul(_ctx.rate,square) + fix_mul((0x10000 /* 1.000000 */ + (- _ctx.rate)),_ctx.lastTri));
   _ctx.lastTri = tri;
   tri = fix_mul(tri,0x18000 /* 1.500000 */);
   fix16_t triToSine;
   triToSine = Oscillator_waveMorph(tri,(sine >> 1),morph);
   uint8_t _cond_84;
   _cond_84 = (dec == 1);
   if(_cond_84){
      triToSine = (triToSine >> 1);
   }
   uint8_t _cond_86;
   _cond_86 = (multiply == 0x40000 /* 4.000000 */);
   if(_cond_86){
      uint8_t _cond_85;
      _cond_85 = ((tune > 0x80000 /* 8.000000 */) && (softening >= 0x851e /* 0.520000 */));
      if(_cond_85){
         multiply = 0x20000 /* 2.000000 */;
      }
   }
   fix16_t shapedWave1stStage;
   shapedWave1stStage = 0x0 /* 0.000000 */;
   uint8_t _cond_90;
   _cond_90 = (fxMode == 0);
   if(_cond_90){
      uint8_t _cond_88;
      _cond_88 = (desymModeIn == 0);
      if(_cond_88){
         shapedWave1stStage = Oscillator_foldWave(triToSine,fix_mul(softening,0x50000 /* 5.000000 */),triToSine);
      }
      else
      {
         uint8_t _cond_87;
         _cond_87 = (desymModeIn == 1);
         if(_cond_87){
            shapedWave1stStage = Oscillator_foldWave(triToSine,fix_mul(softening,0x50000 /* 5.000000 */),(sine >> 1));
         }
      }
   }
   else
   {
      uint8_t _cond_89;
      _cond_89 = (fxMode == 1);
      if(_cond_89){
         shapedWave1stStage = Oscillator_foldWave(audioInput,fix_mul(softening,0x50000 /* 5.000000 */),audioInput);
      }
   }
   _ctx.shapedWave2ndStage = Oscillator_foldWave(fix_mul(shapedWave1stStage,((softening << 1) + 0x10000 /* 1.000000 */)),fix_mul(softening,0x50000 /* 5.000000 */),fix_mul(shapedWave1stStage,((softening << 1) + 0x10000 /* 1.000000 */)));
   _ctx.shapedWave3rdStage = Oscillator_foldWave(fix_mul(_ctx.shapedWave2ndStage,((softening << 1) + 0x10000 /* 1.000000 */)),fix_mul(softening,0x50000 /* 5.000000 */),fix_mul(_ctx.shapedWave2ndStage,((softening << 1) + 0x10000 /* 1.000000 */)));
   _ctx.shapedWave4thStage = Oscillator_foldWave(fix_mul(_ctx.shapedWave3rdStage,((softening << 1) + 0x10000 /* 1.000000 */)),fix_mul(softening,0x50000 /* 5.000000 */),fix_mul(_ctx.shapedWave3rdStage,((softening << 1) + 0x10000 /* 1.000000 */)));
   fix16_t complexOut;
   complexOut = 0x0 /* 0.000000 */;
   fix16_t limitedMultiply;
   limitedMultiply = 0x0 /* 0.000000 */;
   fix16_t limit0;
   limit0 = 0xb8000 /* 11.500000 */;
   fix16_t limit1;
   limit1 = 0xb0000 /* 11.000000 */;
   fix16_t limit2;
   limit2 = 0xa0000 /* 10.000000 */;
   fix16_t limit3;
   limit3 = 0xb9999 /* 11.600000 */;
   uint8_t _cond_96;
   _cond_96 = (tune > limit0);
   if(_cond_96){
      limitedMultiply = 0x0 /* 0.000000 */;
   }
   else
   {
      uint8_t _cond_95;
      _cond_95 = (tune > limit1);
      if(_cond_95){
         limitedMultiply = 0x10000 /* 1.000000 */;
      }
      else
      {
         uint8_t _cond_94;
         _cond_94 = (tune > limit2);
         if(_cond_94){
            limitedMultiply = multiply;
            uint8_t _cond_91;
            _cond_91 = (limitedMultiply > 0x20000 /* 2.000000 */);
            if(_cond_91){
               limitedMultiply = 0x20000 /* 2.000000 */;
            }
         }
         else
         {
            uint8_t _cond_93;
            _cond_93 = (tune > limit3);
            if(_cond_93){
               limitedMultiply = multiply;
               uint8_t _cond_92;
               _cond_92 = (limitedMultiply > 0x30000 /* 3.000000 */);
               if(_cond_92){
                  limitedMultiply = 0x30000 /* 3.000000 */;
               }
            }
            else
            {
               limitedMultiply = multiply;
            }
         }
      }
   }
   uint8_t _cond_100;
   _cond_100 = (limitedMultiply >= 0x40000 /* 4.000000 */);
   if(_cond_100){
      complexOut = fix_mul(_ctx.shapedWave4thStage,((softening << 1) + 0x10000 /* 1.000000 */));
   }
   else
   {
      uint8_t _cond_99;
      _cond_99 = (limitedMultiply >= 0x30000 /* 3.000000 */);
      if(_cond_99){
         complexOut = fix_mul(_ctx.shapedWave3rdStage,((softening << 1) + 0x10000 /* 1.000000 */));
      }
      else
      {
         uint8_t _cond_98;
         _cond_98 = (limitedMultiply >= 0x20000 /* 2.000000 */);
         if(_cond_98){
            complexOut = fix_mul(_ctx.shapedWave2ndStage,((softening << 1) + 0x10000 /* 1.000000 */));
         }
         else
         {
            uint8_t _cond_97;
            _cond_97 = (limitedMultiply >= 0x10000 /* 1.000000 */);
            if(_cond_97){
               complexOut = fix_mul(shapedWave1stStage,((softening << 1) + 0x10000 /* 1.000000 */));
            }
            else
            {
               complexOut = triToSine;
            }
         }
      }
   }
   _tuple___real_real__ _tuple_101;
   {
      _tuple_101.field_0 = complexOut;
      _tuple_101.field_1 = _ctx.phase;
   }
   _output_ = _tuple_101;
   return ;
}

void Oscillator__ctx_type_7_init(Oscillator__ctx_type_7 &_output_){
   Oscillator__ctx_type_7 _ctx;
   _ctx.syncBool = 0;
   _ctx.sync = 0x0 /* 0.000000 */;
   _ctx.softening = 0x0 /* 0.000000 */;
   _ctx.pitch = 0x0 /* 0.000000 */;
   _ctx.phase = 0x0 /* 0.000000 */;
   _ctx.multiply = 0x0 /* 0.000000 */;
   _ctx.morph = 0x0 /* 0.000000 */;
   _ctx.modeBool = 0;
   _ctx.fxMode = 0;
   _ctx.desymMode = 0;
   _ctx.complex = 0x0 /* 0.000000 */;
   Oscillator__ctx_type_6_init(_ctx._inst59);
   _output_ = _ctx;
   return ;
}

void Oscillator_process_init(Oscillator__ctx_type_7 &_output_){
   Oscillator__ctx_type_7_init(_output_);
   return ;
}

fix16_t Oscillator_process(Oscillator__ctx_type_7 &_ctx, fix16_t input){
   _ctx.modeBool = 1;
   _ctx.fxMode = 0;
   uint8_t _cond_103;
   _cond_103 = (_ctx.sync > 0x8000 /* 0.500000 */);
   if(_cond_103){
      _ctx.syncBool = 1;
   }
   else
   {
      _ctx.syncBool = 0;
   }
   _tuple___real_real__ _call_104;
   Oscillator_osc(_ctx._inst59,_ctx.pitch,_ctx.syncBool,fix_mul(_ctx.softening,0xca3d /* 0.790000 */),_ctx.morph,_ctx.multiply,_ctx.modeBool,0x0 /* 0.000000 */,_ctx.fxMode,_ctx.desymMode,_call_104);
   _ctx.complex = _call_104.field_0;_ctx.phase = _call_104.field_1;
   return _ctx.complex;
}

void Oscillator_noteOn_init(Oscillator__ctx_type_7 &_output_){
   Oscillator__ctx_type_7_init(_output_);
   return ;
}

void Oscillator_noteOn(Oscillator__ctx_type_7 &_ctx, int note, int velocity, int channel){
}

void Oscillator_noteOff_init(Oscillator__ctx_type_7 &_output_){
   Oscillator__ctx_type_7_init(_output_);
   return ;
}

void Oscillator_noteOff(Oscillator__ctx_type_7 &_ctx, int note, int channel){
}

void Oscillator_controlChange_init(Oscillator__ctx_type_7 &_output_){
   Oscillator__ctx_type_7_init(_output_);
   return ;
}

void Oscillator_controlChange(Oscillator__ctx_type_7 &_ctx, int control, int value, int channel){
   uint8_t _cond_106;
   _cond_106 = (control == 1);
   if(_cond_106){
      _ctx.pitch = fix_mul(0x1a /* 0.000406 */,int_to_fix(value));
   }
   uint8_t _cond_107;
   _cond_107 = (control == 2);
   if(_cond_107){
      _ctx.softening = (int_to_fix(value) >> 13);
   }
   uint8_t _cond_108;
   _cond_108 = (control == 3);
   if(_cond_108){
      _ctx.multiply = int_to_fix(value);
   }
   uint8_t _cond_109;
   _cond_109 = (control == 4);
   if(_cond_109){
      _ctx.morph = fix_mul(0x6 /* 0.000092 */,int_to_fix(value));
   }
   uint8_t _cond_112;
   _cond_112 = (control == 5);
   if(_cond_112){
      uint8_t _cond_110;
      _cond_110 = (value == 0);
      if(_cond_110){
         _ctx.desymMode = 0;
      }
      uint8_t _cond_111;
      _cond_111 = (value == 1);
      if(_cond_111){
         _ctx.desymMode = 1;
      }
   }
   uint8_t _cond_113;
   _cond_113 = (control == 6);
   if(_cond_113){
      _ctx.sync = int_to_fix(value);
   }
}

void Oscillator_default_init(Oscillator__ctx_type_7 &_output_){
   Oscillator__ctx_type_7_init(_output_);
   return ;
}

void Oscillator_default(Oscillator__ctx_type_7 &_ctx){
}



void Pure::update(void)
{
  audio_block_t *block;
  short *bp;

  block = allocate();
  if (block) {
    bp = block->data;
      for(int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
        fix16_t v = Oscillator_process(data, 0);
        *bp++ = (int16_t)(v / 2);
      }

    transmit(block, 0);
    release(block);
  }
}

