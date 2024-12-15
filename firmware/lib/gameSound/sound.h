#pragma once
#include <Arduino.h>


#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523


extern const int melody[];
extern const int noteDurations[];

extern const int gameOverMelody[];
extern const int gameOverNoteDurations[];


void backgroundMusic(uint8_t SPKR_PIN);
void playGameOverTune(uint8_t SPKR_PIN);
