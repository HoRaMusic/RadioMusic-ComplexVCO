
void getKnobsAndCVinputs(){
    int param1Pot = analogRead(CHORD_POT_PIN); 
    int param1CVI = analogRead(CHORD_CV_PIN); 
    int param2Pot = analogRead(ROOT_POT_PIN); 
    int param2CV = analogRead(ROOT_CV_PIN); 
    int param1Raw;
    int param2Raw;
    if ( lastPotValue < param2Pot + 70.0 && lastPotValue > param2Pot -70.0)
    {
        lockCounter ++;
    }
    if (lockCounter > 20000)
    {
        blockKnob = true;
    } 
    if ( param2Pot > lastPotValue +60.0 || param2Pot < lastPotValue - 60.0)
    {
        blockKnob = false;
        lockCounter = 0;
    }
    if ( blockKnob == false )
    {
        lastUnlockedParam = param2Pot;
    }
    else
    {
        param2Pot = lastUnlockedParam;
    }
    lastPotValue = param2Pot;
    param2Raw = param2Pot;
    param1 = param1Pot;
    param1CV = param1CVI;
    param2 = param2Raw;
    pitchCV = param2CV;
    param2PotRaw = param2Raw; 
}

void checkButton(){
    buttonState = digitalRead(RESET_BUTTON);
    if (pushbutton1.update())
    {
        if (pushbutton1.risingEdge() ) 
        {
            shiftTimer  = 0;
            startCounter = true;
        }
        else if (pushbutton1.fallingEdge() ) 
        {
            startCounter = false;
            if ( shiftTimer < 3000 )
            {
                foldIndex++;
            }
            shiftTimer  = 0;
            modeChanged = false;
            EEPROM_Mode_Frame = 0;
            hasBeenSaved = false;
        }
    }
    if (buttonState == 1 && shiftTimer > 4500 && modeChanged == false)
    {   
        if (controlPage2 == true)
        {
           controlPage2 = false;
        }
        else
        {
            controlPage2 = true;
        }
        modeChanged = true;
    }
    if (foldIndex >= 4)
    {
        foldIndex = 0;
    }
    if (startCounter == true)
    {
        shiftTimer ++;
    }
    
   frame++;
   if (frame%FRAME_DIVIDER == 0)
   {
      dividedFrame ++;
   }
   if (frame > 10000)
   {
      frame = 0;
   }
   if (dividedFrame > 1000)
   {
      dividedFrame = 0;
   }
  
   if (controlPage2 == true)
   {
      if (dividedFrame%2 == 0)
      {
         digitalWrite(RESET_LED, HIGH);
      }
      else
      {
         digitalWrite (RESET_LED, LOW);
      }
   }
   else
   {
      digitalWrite (RESET_LED, LOW);
   }

   if ( modeChanged == true)
   {
      EEPROM_Mode_Frame ++;
      if (EEPROM_Mode_Frame > 15000)
      {
          if (hasBeenSaved == false)
          {
              EEPROM.write(0, lastPitch / 33);
              Serial.println("PITCH SAVED: ");
              EEPROM.write(1, lastParam1Fold / 33);
              EEPROM.write(2, lastParam1Morph / 33);
              EEPROM.write(3, desym);
              EEPROM.write(4, fineTune / 8);
              EEPROM.write(5, foldIndex);
              hasBeenSaved = true;
          }
          if (EEPROM_Mode_Frame%(FRAME_DIVIDER / 4) == 0)
          {
              DIVIDED_EEPROM_Mode_Frame ++;
          }
          if (EEPROM_Mode_Frame > 1000)
          {
              DIVIDED_EEPROM_Mode_Frame = 0;
          }
          if (DIVIDED_EEPROM_Mode_Frame%2 == 0)
          {
             digitalWrite(RESET_LED, HIGH);
          }
          else
          {
             digitalWrite (RESET_LED, LOW);
          }
      }
   }
}

void controlComplexVCOParams(){
    // 1 pitch, 2 softening, 3 multiply, 4 morph, 5 desym, 6 sync, 
    int pitch;
    int numberOfFolding = foldIndex + 1;
    int sync;
    
    if (digitalRead (RESET_CV) == 1)
    {
        sync = 1;
    }
    else
    {
        sync = 0;
    }
    
    if (controlPage2 == false)
    {
        if (param2 < lastPitch + POT_TOLERANCE && param2 > lastPitch - POT_TOLERANCE && canControl == true)
        {
            pitch = (pitchCV + param2 * 3) + fineTune;
            lastPitch = param2;
        }
        else
        {
          pitch = (pitchCV +  lastPitch * 3) + fineTune;
        }
        if (param1 < lastParam1Fold + POT_TOLERANCE && param1 > lastParam1Fold - POT_TOLERANCE)
        {
            folding = param1 + param1CV;
            lastParam1Fold = param1;
        }
        else
        {
            folding = lastParam1Fold + param1CV;
        }
    }
    else
    {
         if (8192 - param1 < lastParam1Morph + POT_TOLERANCE && 8192 - param1 > lastParam1Morph - POT_TOLERANCE)
        {
            morphing = (8192 - param1) - param1CV;
            lastParam1Morph = 8192 - param1;
        }
        else
        {
           morphing = lastParam1Morph - param1CV;
        }
        pitch = (pitchCV +  lastPitch * 3) + fineTune;
        if ( (param2PotRaw < lastDesym + POT_TOLERANCE && param2PotRaw > lastDesym - POT_TOLERANCE) && canControl == true)
        {
            if ( param2PotRaw > 4000)
            {
                desym = 1; 
            }
            else 
            {
                desym = 0;
            }
            lastDesym = param2PotRaw;
        }
    }
    if (modeChanged == true)
    {
        if ((buttonState == 1) && (param2 < lastFineTuneParam + POT_TOLERANCE && param2 > lastFineTuneParam - POT_TOLERANCE))
        {
            canControl = false;
            fineTune = param2/5;
            lastFineTuneParam = param2;
        }
    }
    else
    {
        canControl = true;
    }
    ComplexVCO.controlChange(1, pitch, 1);
    ComplexVCO.controlChange(2, folding, 1);
    ComplexVCO.controlChange(3, numberOfFolding, 1);
    ComplexVCO.controlChange(4, morphing, 1);
    ComplexVCO.controlChange(5, desym, 1);
    ComplexVCO.controlChange(6, sync, 1);
}


void selectFoldingIndex(){
    if (foldIndex == FOLD2)
    {
         digitalWrite(LED3, HIGH); 
    }
    else 
    {
        digitalWrite(LED3, LOW);
    }
    if (foldIndex == FOLD4)
    {
         digitalWrite(LED2, HIGH);  
    }
    else
    {
         digitalWrite(LED2, LOW);
    }
    if (foldIndex == FOLD8)
    {
         digitalWrite(LED1, HIGH);  
    }
    else
    {
         digitalWrite(LED1, LOW);
    }
    if (foldIndex == FOLD16)
    {
         digitalWrite(LED0, HIGH); 
    }
    else
    {
        digitalWrite(LED0, LOW);
    }
}


